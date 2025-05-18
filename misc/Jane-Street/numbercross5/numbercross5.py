import tkinter as tk
import tkinter.simpledialog as simpledialog
import tkinter.messagebox as messagebox
import tkinter.filedialog as filedialog
import json, copy, math
from collections import defaultdict

# -----------------------------------------------------------------------------
#  Static puzzle definition
# -----------------------------------------------------------------------------
_raw_map = [
    "A A A A A A A A A A A",
    "A B A A* A* A A A A A A",
    "B B C C C* C D D D A* D",
    "B C C B C E D D D* D* D",
    "B C C B C E E D D E D",
    "B B B B B E* E E E E D",
    "B F* G* G B B* E* E G E E",
    "B F* G G G G* G G G H H",
    "F F F F G* F* G H H H H",
    "F F F F F* F F F F F F",
    "F F I I I I I I F F F",
]

ROW_LABELS = [
    "square", "prod = 20", "multiple of 13", "multiple of 32",
    "divisible by digits", "prod = 25", "divisible by digits",
    "odd palindrome", "Fibonacci", "prod = 2025", "prime",
]

# -----------------------------------------------------------------------------
#  Build maps
# -----------------------------------------------------------------------------
GRID, YELLOW, regions = [], set(), set()
for r, line in enumerate(_raw_map):
    row = []
    for c, tok in enumerate(line.split()):
        if tok.endswith('*'):
            row.append(tok[0])
            YELLOW.add((r, c))
        else:
            row.append(tok)
        regions.add(tok[0])
    GRID.append(row)

N = len(GRID)  # 11

# -----------------------------------------------------------------------------
#  Row-clue helpers
# -----------------------------------------------------------------------------
_fib_cache = None

def is_square(n):
    r = int(math.isqrt(n))
    return r * r == n

def prod_digits(n):
    p = 1
    for d in str(n):
        p *= int(d)
    return p

def divisible_by_digits(n):
    for d in str(n):
        d = int(d)
        if d == 0 or n % d != 0:
            return False
    return True

def is_fibonacci(n):
    global _fib_cache
    if _fib_cache is None or max(_fib_cache) < n:
        _fib_cache = set()
        a, b = 0, 1
        while b <= max(n, 4000000000):
            _fib_cache.add(b)
            a, b = b, a + b
    return n in _fib_cache

def is_prime(n):
    if n < 2:
        return False
    if n % 2 == 0:
        return n == 2
    r = int(math.isqrt(n))
    f = 3
    while f <= r:
        if n % f == 0:
            return False
        f += 2
    return True

CLUE_FUNCS = {
    0: lambda ns: all(is_square(n) for n in ns),
    1: lambda ns: all(prod_digits(n) == 20 for n in ns),
    2: lambda ns: all(n % 13 == 0 for n in ns),
    3: lambda ns: all(n % 32 == 0 for n in ns),
    4: lambda ns: all(divisible_by_digits(n) for n in ns),
    5: lambda ns: all(prod_digits(n) == 25 for n in ns),
    6: lambda ns: all(divisible_by_digits(n) for n in ns),
    7: lambda ns: all(n % 2 == 1 and str(n) == str(n)[::-1] for n in ns),
    8: lambda ns: all(is_fibonacci(n) for n in ns),
    9: lambda ns: all(prod_digits(n) == 2025 for n in ns),
    10: lambda ns: all(is_prime(n) for n in ns),
}

# -----------------------------------------------------------------------------
class PuzzleState:
    """Encapsulate mutable state so we can snapshot / restore easily."""
    def __init__(self):
        self.region_digit = {reg: 0 for reg in regions}
        self.tiles = set()                     # {(r,c)}
        self.tile_distrib = {}                # (r,c) -> { (nr,nc): amt }
        self.increments = defaultdict(int)    # (r,c) -> amt

    def snapshot(self):
        return copy.deepcopy(self)

    # rebuild increments from tile_distrib
    def recompute_increments(self):
        self.increments = defaultdict(int)
        for dist in self.tile_distrib.values():
            for cell, amt in dist.items():
                self.increments[cell] += amt

    # serialise to json-able dict
    def to_dict(self):
        return {
            "region_digit": self.region_digit,
            "tiles": list(self.tiles),
            "tile_distrib": {str(k): {str(cell): amt for cell, amt in v.items()} for k, v in self.tile_distrib.items()}
        }

    @staticmethod
    def from_dict(d):
        ps = PuzzleState()
        ps.region_digit = {k: int(v) for k, v in d.get("region_digit", {}).items()}
        ps.tiles = {tuple(t) for t in d.get("tiles", [])}
        ps.tile_distrib = {eval(k): {eval(cell): amt for cell, amt in v.items()} for k, v in d.get("tile_distrib", {}).items()}
        ps.recompute_increments()
        return ps

# -----------------------------------------------------------------------------
class RegionVisualizer(tk.Frame):
    DOUBLE_MS = 250
    LABEL_PAD = 170
    DIRS = [(-1, 0), (0, -1), (1, 0), (0, 1)]  # up, left, down, right

    def __init__(self, master):
        super().__init__(master)
        self.pack(fill=tk.BOTH, expand=True)
        self.master = master

        # state & history
        self.state = PuzzleState()
        self.history = [self.state.snapshot()]
        self.hist_idx = 0

        # UI widgets
        self._build_toolbar()
        self.canvas = tk.Canvas(self, bg="white")
        self.canvas.pack(fill=tk.BOTH, expand=True)

        # bindings
        self.canvas.bind("<Configure>", self._on_resize)
        self.canvas.bind("<Button-1>", self._on_single_click)
        self.canvas.bind("<Double-Button-1>", self._on_double_click)

        self._pending_single = None
        self.scale = 60
        self.margin_x = self.LABEL_PAD + 20
        self.margin_y = 40

    # ------------------------------------------------ UI helpers
    def _build_toolbar(self):
        bar = tk.Frame(self)
        bar.pack(fill=tk.X)
        tk.Button(bar, text="Save", command=self._save).pack(side=tk.LEFT)
        tk.Button(bar, text="Load", command=self._load).pack(side=tk.LEFT)
        tk.Button(bar, text="Clear", command=self._clear).pack(side=tk.LEFT)
        tk.Button(bar, text="Undo", command=self._undo).pack(side=tk.LEFT)
        tk.Button(bar, text="Redo", command=self._redo).pack(side=tk.LEFT)

    # ------------------------------------------------ history helpers
    def _commit(self):
        # truncate future states then append snapshot
        self.history = self.history[:self.hist_idx + 1]
        self.history.append(self.state.snapshot())
        self.hist_idx += 1

    def _undo(self):
        if self.hist_idx == 0:
            return
        self.hist_idx -= 1
        self.state = copy.deepcopy(self.history[self.hist_idx])
        self._draw()

    def _redo(self):
        if self.hist_idx >= len(self.history) - 1:
            return
        self.hist_idx += 1
        self.state = copy.deepcopy(self.history[self.hist_idx])
        self._draw()

    # ------------------------------------------------ persistence
    def _save(self):
        fn = filedialog.asksaveasfilename(defaultextension=".json", filetypes=[("JSON", "*.json")])
        if not fn:
            return
        with open(fn, "w") as f:
            json.dump(self.state.to_dict(), f, indent=2)

    def _load(self):
        fn = filedialog.askopenfilename(filetypes=[("JSON", "*.json")])
        if not fn:
            return
        try:
            with open(fn, "r") as f:
                data = json.load(f)
            self.state = PuzzleState.from_dict(data)
            self.history = [self.state.snapshot()]
            self.hist_idx = 0
            self._draw()
        except Exception as e:
            messagebox.showerror("Load failed", str(e))

    def _clear(self):
        if messagebox.askyesno("Clear", "Reset all digits and tiles?"):
            self.state = PuzzleState()
            self.history = [self.state.snapshot()]
            self.hist_idx = 0
            self._draw()

    # ------------------------------------------------ geometry helpers
    def _logic_to_canvas(self, r, c):
        return self.margin_x + (c + 0.5) * self.scale, self.margin_y + (r + 0.5) * self.scale

    def _inside_grid(self, r, c):
        return 0 <= r < N and 0 <= c < N

    def _canvas_to_rc(self, x, y):
        if not (self.margin_x <= x <= self.margin_x + N * self.scale and
                self.margin_y <= y <= self.margin_y + N * self.scale):
            return None
        c = int((x - self.margin_x) // self.scale)
        r = int((y - self.margin_y) // self.scale)
        return r, c

    def _get_region_cells(self, region_id):
        cells = []
        for r in range(N):
            for c in range(N):
                if GRID[r][c] == region_id:
                    cells.append((r, c))
        return cells

    # ------------------------------------------------ evaluation helpers
    def _row_numbers(self, r):
        nums, cur = [], []
        for c in range(N):
            if (r, c) in self.state.tiles:
                if len(cur) >= 2:
                    nums.append(int("".join(map(str, cur))))
                cur = []
                continue
            val = self.state.region_digit[GRID[r][c]] + self.state.increments[(r, c)]
            if val == 0:
                return None
            cur.append(val)
        if len(cur) >= 2:
            nums.append(int("".join(map(str, cur))))
        return nums if nums else None

    def _validate(self):
        """Return (row_ok list, grand_sum or None, list_of_violation_strings)."""
        row_ok, violations, all_nums = [], [], []

        # row / clue validation ------------------------------------------------
        for r in range(N):
            ns = self._row_numbers(r)
            if not ns:
                violations.append(f"Row {r+1}: unable to form any number >=2 digits")
                row_ok.append(False)
                continue
            if not CLUE_FUNCS[r](ns):
                violations.append(f"Row {r+1}: numbers {ns} violate clue '{ROW_LABELS[r]}'")
                row_ok.append(False)
            else:
                row_ok.append(True)
                all_nums.extend(ns)

        # duplicate numbers ----------------------------------------------------
        dup_nums = {n for n in all_nums if all_nums.count(n) > 1}
        for n in sorted(dup_nums):
            violations.append(f"Number {n} appears more than once in the grid")

        # adjacent regions with same digit ------------------------------------
        seen_pairs = set()
        for r in range(N):
            for c in range(N):
                if (r, c) in self.state.tiles:
                    continue
                digit = self.state.region_digit[GRID[r][c]] + self.state.increments[(r, c)]
                if digit == 0:
                    continue
                for dr, dc in ((1, 0), (0, 1)):  # check right & down only to avoid double-count
                    nr, nc = r + dr, c + dc
                    if not self._inside_grid(nr, nc) or GRID[nr][nc] == GRID[r][c] or (nr, nc) in self.state.tiles:
                        continue
                    ndigit = self.state.region_digit[GRID[nr][nc]] + self.state.increments[(nr, nc)]
                    if ndigit == digit and ndigit != 0:
                        pair = tuple(sorted({GRID[r][c], GRID[nr][nc]}))
                        if pair not in seen_pairs:
                            seen_pairs.add(pair)
                            violations.append(
                                f"Adjacent regions {pair[0]} and {pair[1]} both show digit {digit}")

        grand = sum(all_nums) if not violations else None
        return row_ok, grand, violations

    # ------------------------------------------------ drawing
    def _draw(self):
        self.canvas.delete("all")
        reg_w, bold_w = 4, 8

        row_ok, grand, violations = self._validate()

        # yellow & tiles -------------------------------------------------------
        for (r, c) in YELLOW:
            x0 = self.margin_x + c * self.scale
            y0 = self.margin_y + r * self.scale
            self.canvas.create_rectangle(x0, y0, x0 + self.scale, y0 + self.scale, fill="yellow", outline="")
        for (r, c) in self.state.tiles:
            x0 = self.margin_x + c * self.scale
            y0 = self.margin_y + r * self.scale
            self.canvas.create_rectangle(x0, y0, x0 + self.scale, y0 + self.scale, fill="black", outline="")

        # grid lines -----------------------------------------------------------
        for i in range(N + 1):
            x = self.margin_x + i * self.scale
            self.canvas.create_line(x, self.margin_y, x, self.margin_y + N * self.scale, width=reg_w)
        for j in range(N + 1):
            y = self.margin_y + j * self.scale
            self.canvas.create_line(self.margin_x, y, self.margin_x + N * self.scale, y, width=reg_w)

        # bold region borders --------------------------------------------------
        for r in range(N):
            for c in range(N):
                reg = GRID[r][c]
                x0, y0 = self.margin_x + c * self.scale, self.margin_y + r * self.scale
                x1, y1 = x0 + self.scale, y0 + self.scale
                if c == N - 1 or GRID[r][c + 1] != reg:
                    self.canvas.create_line(x1, y0, x1, y1, width=bold_w)
                if r == N - 1 or GRID[r + 1][c] != reg:
                    self.canvas.create_line(x0, y1, x1, y1, width=bold_w)
                if r == 0 or GRID[r - 1][c] != reg:
                    self.canvas.create_line(x0, y0, x1, y0, width=bold_w)
                if c == 0 or GRID[r][c - 1] != reg:
                    self.canvas.create_line(x0, y0, x0, y1, width=bold_w)

        # digits ---------------------------------------------------------------
        for r in range(N):
            for c in range(N):
                if (r, c) in self.state.tiles:
                    continue
                val = self.state.region_digit[GRID[r][c]] + self.state.increments[(r, c)]
                if val:
                    x, y = self._logic_to_canvas(r, c)
                    self.canvas.create_text(x, y, text=str(val), font=("Helvetica", int(self.scale * 0.5)))

        # row labels -----------------------------------------------------------
        for r, label in enumerate(ROW_LABELS):
            color = "red" if not row_ok[r] else "black"
            x = self.margin_x - 10
            y = self.margin_y + (r + 0.5) * self.scale
            self.canvas.create_text(x, y, text=label, anchor="e", fill=color,
                                     font=("Helvetica", int(self.scale * 0.35), "bold"))

        # grand sum ------------------------------------------------------------
        txt = "Sum: " + (str(grand) if grand is not None else "-")
        col = "forestgreen" if grand is not None else "red"
        self.canvas.create_text(self.margin_x + N * self.scale / 2, self.margin_y - 25,
                                text=txt, fill=col, anchor="n", font=("Helvetica", 16, "bold"))

        # violation list -------------------------------------------------------
        if violations:
            vx = self.margin_x + N * self.scale + 15
            vy = self.margin_y
            self.canvas.create_text(vx, vy, text="Violations:", anchor="nw", fill="red",
                                     font=("Helvetica", 14, "bold"))
            for i, v in enumerate(violations, start=1):
                self.canvas.create_text(vx, vy + i * 18, text=f"• {v}", anchor="nw", fill="red",
                                         font=("Helvetica", 10))

    # ------------------------------------------------ event handling
    def _on_resize(self, event):
        grid_w = min(event.width - self.LABEL_PAD - 40, event.height - 100)
        self.scale = grid_w / N
        self.margin_x = (event.width - self.LABEL_PAD - N * self.scale) / 2 + self.LABEL_PAD
        self.margin_y = (event.height - N * self.scale) / 2 + 30
        self._draw()

    def _on_single_click(self, event):
        if self._pending_single is not None:
            self.after_cancel(self._pending_single)
        x, y = event.x, event.y
        self._pending_single = self.after(self.DOUBLE_MS, lambda: self._single_action(x, y))

    def _on_double_click(self, event):
        if self._pending_single is not None:
            self.after_cancel(self._pending_single)
            self._pending_single = None
        self._double_action(event.x, event.y)

    def _single_action(self, x, y):
        self._pending_single = None
        rc = self._canvas_to_rc(x, y)
        if rc is None:
            return
        r, c = rc
        if (r, c) in YELLOW:
            return
        if (r, c) in self.state.tiles:
            self._remove_tile(r, c)
        else:
            self._add_tile(r, c)
        self._commit()
        self._draw()

    def _double_action(self, x, y):
        rc = self._canvas_to_rc(x, y)
        if rc is None:
            return
        r, c = rc
        reg = GRID[r][c]
        val = simpledialog.askinteger("Region digit", f"Digit for region {reg} (0-clear):", minvalue=0, maxvalue=9)
        if val is None:
            return
        self.state.region_digit[reg] = val
        self._commit()
        self._draw()

    # ---------------- tile helpers ----------------
    def _add_tile(self, r, c):
        # check for adjacent tiles
        for dr, dc in self.DIRS:
            nr, nc = r + dr, c + dc
            if self._inside_grid(nr, nc) and (nr, nc) in self.state.tiles:
                messagebox.showerror("Invalid Tile Placement", "Tiles cannot be orthogonally adjacent.")
                return

        base = self.state.region_digit[GRID[r][c]]
        if base == 0:
            messagebox.showinfo("Unset digit", "Set the region digit first.")
            return
        prompt = f"Distribute {base} (up,left,down,right):"
        while True:
            s = simpledialog.askstring("Distribution", prompt)
            if s is None:
                return
            try:
                nums = list(map(int, s.split(',')))
                if len(nums) != 4 or sum(nums) != base:
                    raise ValueError
            except ValueError:
                messagebox.showerror("Input error", "Enter four integers summing to the digit.")
                continue
            # validate neighbours and max increment
            ok, dist = True, {}
            for (dr, dc), amt in zip(self.DIRS, nums):
                if amt == 0:
                    continue
                nr, nc = r + dr, c + dc
                if not self._inside_grid(nr, nc) or (nr, nc) in YELLOW:
                    ok = False
                    messagebox.showerror("Invalid", "Cannot push outside grid or into yellow.")
                    break
                neighbor_val = self.state.region_digit.get(GRID[nr][nc], 0) + self.state.increments.get((nr, nc), 0) + amt
                if neighbor_val > 9:
                    ok = False
                    messagebox.showerror("Invalid", f"Increment causes cell ({nr},{nc}) to exceed 9.")
                    break
                dist[(nr, nc)] = amt
            if not ok:
                continue
            break
        # apply
        for cell, amt in dist.items():
            self.state.increments[cell] += amt
        self.state.tiles.add((r, c))
        self.state.tile_distrib[(r, c)] = dist

    def _remove_tile(self, r, c):
        dist = self.state.tile_distrib.pop((r, c), {})
        for cell, amt in dist.items():
            self.state.increments[cell] -= amt
            if self.state.increments[cell] == 0:
                del self.state.increments[cell]
        self.state.tiles.remove((r, c))

# -----------------------------------------------------------------------------
if __name__ == "__main__":
    root = tk.Tk()
    root.title("Region Visualizer - assign digits (double-click) / place tiles (click)")
    try:
        root.state('zoomed')
    except tk.TclError:
        root.attributes('-zoomed', True)
    RegionVisualizer(root)
    root.mainloop()
