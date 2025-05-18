import tkinter as tk
import tkinter.simpledialog as simpledialog
import tkinter.messagebox as messagebox
import math
import json
import os

class HallOfMirrors3:
    """
    A 10x10 laser-mirror puzzle. Mirrors go in grid cells, lasers enter from perimeter dots.
    """

    def __init__(self, master):
        """
        Set up the puzzle, load saved state if present, and draw everything.
        """
        self.master = master
        self.master.title("Hall of Mirrors 3")

        # Top toolbar for Save/Load/Save & Clear
        self.top_frame = tk.Frame(self.master)
        self.top_frame.pack(side=tk.TOP, fill=tk.X, pady=5)

        self.save_button = tk.Button(self.top_frame, text="Save", command=self.save_puzzle_state)
        self.save_button.pack(side=tk.LEFT, padx=5)

        self.load_button = tk.Button(self.top_frame, text="Load", command=lambda: self.load_puzzle_state(prompt=True))
        self.load_button.pack(side=tk.LEFT, padx=5)

        self.save_clear_button = tk.Button(self.top_frame, text="Save & Clear", command=self.save_and_clear)
        self.save_clear_button.pack(side=tk.LEFT, padx=5)

        # Main canvas
        self.canvas = tk.Canvas(self.master, bg="white")
        self.canvas.pack(fill=tk.BOTH, expand=True)

        self.canvas.bind("<Configure>", self.on_resize)
        self.canvas.bind("<Button-1>", self.on_click)

        self.ncells = 10
        self.mirrors = {(i, j): 0 for i in range(self.ncells) for j in range(self.ncells)}
        self.labels_bottom = [2025, 0, 0, 12, 64, 5, 0, 405, 0, 0]
        self.labels_top = [0, 0, 112, 0, 48, 3087, 9, 0, 0, 1]
        self.labels_left = [0, 225, 12, 0, 0, 0, 27, 0, 0, 0]
        self.labels_right = [0, 0, 0, 16, 0, 0, 0, 27, 4, 0]

        # Track which perimeter lasers are "on" for path display
        self.active_lasers = set()

        self.logical_size = 11
        self.scale = 50
        self.margin_x = 50
        self.margin_y = 50

        # Load from the base file (if it exists) without prompting.
        self.load_puzzle_state()
        self.redraw()

    def on_resize(self, event):
        """
        Adjust scale and margins when the window is resized.
        """
        w = event.width
        h = event.height
        self.scale = min(w, h) * 0.8 / self.logical_size
        self.margin_x = (w - self.logical_size * self.scale) / 2
        self.margin_y = (h - self.logical_size * self.scale) / 2
        self.redraw()

    def grid_to_canvas(self, x, y):
        """
        Convert logical (x,y) to canvas coordinates.
        """
        cx = self.margin_x + (x + 0.5) * self.scale
        cy = self.margin_y + (self.logical_size - (y + 0.5)) * self.scale
        return cx, cy

    def redraw(self):
        """
        Clear and redraw the puzzle.
        """
        self.canvas.delete("all")
        self.draw_mirrors()
        self.draw_grid()
        self.draw_dots()
        self.draw_active_lasers()
        self.draw_side_sums_and_final_answer()

    def draw_grid(self):
        """
        Draw the 10x10 grid lines.
        """
        for i in range(self.ncells + 1):
            x0, y0 = self.grid_to_canvas(i, 0)
            x1, y1 = self.grid_to_canvas(i, self.ncells)
            self.canvas.create_line(x0, y0, x1, y1, fill="black", width=4)
        for j in range(self.ncells + 1):
            x0, y0 = self.grid_to_canvas(0, j)
            x1, y1 = self.grid_to_canvas(self.ncells, j)
            self.canvas.create_line(x0, y0, x1, y1, fill="black", width=4)

    def draw_mirrors(self):
        """
        Draw mirrors in each cell. 1 -> "\" and 2 -> "/".
        """
        mirror_color = "orchid"
        for i in range(self.ncells):
            for j in range(self.ncells):
                s = self.mirrors[(i, j)]
                if s == 0:
                    continue
                bl = self.grid_to_canvas(i, j)
                br = self.grid_to_canvas(i+1, j)
                tl = self.grid_to_canvas(i, j+1)
                tr = self.grid_to_canvas(i+1, j+1)
                if s == 1:
                    self.canvas.create_line(br[0], br[1], tl[0], tl[1],
                                            fill=mirror_color, width=4)
                elif s == 2:
                    self.canvas.create_line(bl[0], bl[1], tr[0], tr[1],
                                            fill=mirror_color, width=4)

    def simulate_laser_from_dot(self, x, y, side):
        """
        Return a list of segment lengths for the laser path from perimeter dot (x,y).
        """
        if side == "bottom":
            ci, cj = int(x - 0.5), 0
            d = (0, 1)
        elif side == "top":
            ci, cj = int(x - 0.5), self.ncells - 1
            d = (0, -1)
        elif side == "left":
            ci, cj = 0, int(y - 0.5)
            d = (1, 0)
        else:
            ci, cj = self.ncells - 1, int(y - 0.5)
            d = (-1, 0)

        segs = []
        seg_len = 1
        if self.mirrors[(ci, cj)] != 0:
            segs.append(seg_len)
            if self.mirrors[(ci, cj)] == 1:
                d = (-d[1], -d[0])
            else:
                d = (d[1], d[0])
            seg_len = 0

        while True:
            ni, nj = ci + d[0], cj + d[1]
            if 0 <= ni < self.ncells and 0 <= nj < self.ncells:
                ci, cj = ni, nj
                seg_len += 1
                if self.mirrors[(ci, cj)] != 0:
                    segs.append(seg_len)
                    if self.mirrors[(ci, cj)] == 1:
                        d = (-d[1], -d[0])
                    else:
                        d = (d[1], d[0])
                    seg_len = 0
            else:
                segs.append(seg_len + 1)
                break
        return segs

    def get_laser_path(self, side, index):
        """
        Return the list of logical coordinates along the laser path for (side, index).
        """
        if side == "bottom":
            x, y = index + 0.5, -0.5
            d = (0, 1)
            ci, cj = index, 0
        elif side == "top":
            x, y = index + 0.5, self.ncells + 0.5
            d = (0, -1)
            ci, cj = index, self.ncells - 1
        elif side == "left":
            x, y = -0.5, index + 0.5
            d = (1, 0)
            ci, cj = 0, index
        else:
            x, y = self.ncells + 0.5, index + 0.5
            d = (-1, 0)
            ci, cj = self.ncells - 1, index

        path_points = [(x, y)]
        first_center = (ci + 0.5, cj + 0.5)
        path_points.append(first_center)

        if self.mirrors[(ci, cj)] == 1:
            d = (-d[1], -d[0])
        elif self.mirrors[(ci, cj)] == 2:
            d = (d[1], d[0])

        while True:
            ni, nj = ci + d[0], cj + d[1]
            if 0 <= ni < self.ncells and 0 <= nj < self.ncells:
                ci, cj = ni, nj
                center = (ci + 0.5, cj + 0.5)
                path_points.append(center)
                if self.mirrors[(ci, cj)] == 1:
                    d = (-d[1], -d[0])
                elif self.mirrors[(ci, cj)] == 2:
                    d = (d[1], d[0])
            else:
                exit_x = ci + 0.5 + d[0]*0.5
                exit_y = cj + 0.5 + d[1]*0.5
                path_points.append((exit_x, exit_y))
                break
        return path_points

    def draw_active_lasers(self):
        """
        Draw laser paths for all active lasers in a cheerful color.
        """
        laser_color = "turquoise"
        for (side, index) in self.active_lasers:
            path = self.get_laser_path(side, index)
            coords = [self.grid_to_canvas(px, py) for (px, py) in path]
            for k in range(len(coords) - 1):
                x0, y0 = coords[k]
                x1, y1 = coords[k+1]
                self.canvas.create_line(x0, y0, x1, y1, fill=laser_color, width=3)

    def draw_dots(self):
        """
        Draw perimeter dots and label them with either a clue or the product.
        """
        for i in range(self.ncells):
            self.draw_dot_with_label(i + 0.5, -0.5, "bottom")
            self.draw_dot_with_label(i + 0.5, self.ncells + 0.5, "top")
        for j in range(self.ncells):
            self.draw_dot_with_label(-0.5, j + 0.5, "left")
            self.draw_dot_with_label(self.ncells + 0.5, j + 0.5, "right")

    def draw_dot_with_label(self, x, y, side):
        """
        Compute the product for the laser from this dot. If labeled, use green/red if correct/wrong.
        Unlabeled => black text. The dot's fill color matches the text color.
        """
        segs = self.simulate_laser_from_dot(x, y, side)
        p = math.prod(segs)

        if side == "bottom":
            idx = int(x - 0.5)
            c = self.labels_bottom[idx]
        elif side == "top":
            idx = int(x - 0.5)
            c = self.labels_top[idx]
        elif side == "left":
            idx = int(y - 0.5)
            c = self.labels_left[idx]
        else:
            idx = int(y - 0.5)
            c = self.labels_right[idx]

        if c != 0:
            txt = f"{c}\n{p}"
            color = "forestgreen" if c == p else "red"
        else:
            txt = str(p)
            color = "black"

        cx, cy = self.grid_to_canvas(x, y)
        r = 3
        self.canvas.create_oval(cx - r, cy - r, cx + r, cy + r, fill=color)  # dot color = text color

        off = 25
        if side == "bottom":
            tx, ty = cx, cy + off
        elif side == "top":
            tx, ty = cx, cy - off
        elif side == "left":
            tx, ty = cx - off, cy
        else:
            tx, ty = cx + off, cy

        self.canvas.create_text(tx, ty, text=txt, fill=color)

    def draw_side_sums_and_final_answer(self):
        """
        Sum unlabeled dots on each side, check labeled correctness, and draw sums/final product.
        """
        sums = {"bottom": 0, "top": 0, "left": 0, "right": 0}
        lists = {"bottom": [], "top": [], "left": [], "right": []}
        correct = {"bottom": True, "top": True, "left": True, "right": True}

        for i in range(self.ncells):
            segs = self.simulate_laser_from_dot(i + 0.5, -0.5, "bottom")
            p = math.prod(segs)
            if self.labels_bottom[i] != 0:
                if self.labels_bottom[i] != p:
                    correct["bottom"] = False
            else:
                sums["bottom"] += p
                lists["bottom"].append(p)

        for i in range(self.ncells):
            segs = self.simulate_laser_from_dot(i + 0.5, self.ncells + 0.5, "top")
            p = math.prod(segs)
            if self.labels_top[i] != 0:
                if self.labels_top[i] != p:
                    correct["top"] = False
            else:
                sums["top"] += p
                lists["top"].append(p)

        for j in range(self.ncells):
            segs = self.simulate_laser_from_dot(-0.5, j + 0.5, "left")
            p = math.prod(segs)
            if self.labels_left[j] != 0:
                if self.labels_left[j] != p:
                    correct["left"] = False
            else:
                sums["left"] += p
                lists["left"].append(p)

        for j in range(self.ncells):
            segs = self.simulate_laser_from_dot(self.ncells + 0.5, j + 0.5, "right")
            p = math.prod(segs)
            if self.labels_right[j] != 0:
                if self.labels_right[j] != p:
                    correct["right"] = False
            else:
                sums["right"] += p
                lists["right"].append(p)

        def build_expr(vals):
            if not vals:
                return "No unlabeled = 0"
            total = sum(vals)
            return " + ".join(map(str, vals)) + f" = {total}"

        def center_coords(side):
            if side == "bottom":
                x, y = self.grid_to_canvas(self.ncells / 2, -0.5)
                return (x, y + 70)
            elif side == "top":
                x, y = self.grid_to_canvas(self.ncells / 2, self.ncells + 0.5)
                return (x, y - 70)
            elif side == "left":
                x, y = self.grid_to_canvas(-0.5, self.ncells / 2)
                return (x - 70, y)
            else:
                x, y = self.grid_to_canvas(self.ncells + 0.5, self.ncells / 2)
                return (x + 70, y)

        for side in ["bottom", "top", "left", "right"]:
            expr = build_expr(lists[side])
            c = "forestgreen" if correct[side] else "red"
            cx, cy = center_coords(side)
            a = 90 if side == "left" else (-90 if side == "right" else 0)
            self.canvas.create_text(cx, cy, text=expr, fill=c, angle=a)

        fb = sums["bottom"]
        ft = sums["top"]
        fl = sums["left"]
        fr = sums["right"]
        final = fb * ft * fl * fr
        expr = f"{fb} * {ft} * {fl} * {fr} = {final}"
        c = "forestgreen" if all(correct.values()) else "red"
        self.canvas.create_text(20, 20, text=f"Final Answer:\n{expr}", fill=c, anchor="nw")

    def on_click(self, event):
        """
        Cycle a mirror if click is inside the grid. Toggle a laser path if click is on a perimeter dot.
        """
        x_log = (event.x - self.margin_x) / self.scale - 0.5
        y_log = self.logical_size - ((event.y - self.margin_y) / self.scale) - 0.5

        side_index = self.get_perimeter_side_index(x_log, y_log)
        if side_index:
            side, idx = side_index
            if (side, idx) in self.active_lasers:
                self.active_lasers.remove((side, idx))
            else:
                self.active_lasers.add((side, idx))
            self.redraw()
            return

        if 0 <= x_log < self.ncells and 0 <= y_log < self.ncells:
            i = int(x_log)
            j = int(y_log)
            self.mirrors[(i, j)] = (self.mirrors[(i, j)] + 1) % 3
            self.redraw()

    def get_perimeter_side_index(self, x, y):
        """
        Identify which perimeter dot was clicked, if any, as (side, index).
        """
        eps = 0.4
        if abs(y + 0.5) < eps and 0 <= x < self.ncells:
            return ("bottom", int(x))
        if abs(y - (self.ncells + 0.5)) < eps and 0 <= x < self.ncells:
            return ("top", int(x))
        if abs(x + 0.5) < eps and 0 <= y < self.ncells:
            return ("left", int(y))
        if abs(x - (self.ncells + 0.5)) < eps and 0 <= y < self.ncells:
            return ("right", int(y))
        return None

    def save_puzzle_state(self):
        """
        Save the current puzzle state to the base JSON file: hallofmirrors3.json.
        """
        data = {
            "mirrors": {str(k): v for k, v in self.mirrors.items()},
            "labels_bottom": self.labels_bottom,
            "labels_top": self.labels_top,
            "labels_left": self.labels_left,
            "labels_right": self.labels_right
        }
        with open("hallofmirrors3.json", "w") as f:
            json.dump(data, f, indent=4)

    def load_puzzle_state(self, prompt=False):
        """
        Load puzzle state from a JSON file.
        If prompt is True, ask the user for the copy ID:
          0 -> hallofmirrors3.json
          1 -> hallofmirrors3 copy.json
          2 -> hallofmirrors3 copy 2.json, etc.
        Otherwise, load from the base file.
        """
        if prompt:
            copy_id = simpledialog.askinteger("Load Puzzle", 
                                               "Enter puzzle copy ID (0 for base, 1 for copy, 2 for copy 2, etc):",
                                               initialvalue=0, minvalue=0)
            if copy_id is None:
                return  # cancelled
        else:
            copy_id = 0

        # Determine filename based on copy_id
        if copy_id == 0:
            filename = "hallofmirrors3.json"
        elif copy_id == 1:
            filename = "hallofmirrors3 copy.json"
        else:
            filename = f"hallofmirrors3 copy {copy_id}.json"

        if not os.path.exists(filename):
            messagebox.showerror("Error", f"File '{filename}' does not exist.")
            return

        with open(filename, "r") as f:
            data = json.load(f)
        if "mirrors" in data:
            # Reset all mirrors first
            self.mirrors = {(i, j): 0 for i in range(self.ncells) for j in range(self.ncells)}
            for k_str, v in data["mirrors"].items():
                t = eval(k_str)
                self.mirrors[t] = v
        self.labels_bottom = data.get("labels_bottom", self.labels_bottom)
        self.labels_top = data.get("labels_top", self.labels_top)
        self.labels_left = data.get("labels_left", self.labels_left)
        self.labels_right = data.get("labels_right", self.labels_right)
        self.redraw()

    def save_and_clear(self):
        """
        Save the current state to the lowest available backup file and then clear the puzzle.
        The backup files are named:
            hallofmirrors3 copy.json (ID 1),
            hallofmirrors3 copy 2.json (ID 2), etc.
        After saving, reset mirrors to 0 and update the base file.
        """
        backup_id = 1
        while True:
            if backup_id == 1:
                filename = "hallofmirrors3 copy.json"
            else:
                filename = f"hallofmirrors3 copy {backup_id}.json"
            if not os.path.exists(filename):
                break
            backup_id += 1

        data = {
            "mirrors": {str(k): v for k, v in self.mirrors.items()},
            "labels_bottom": self.labels_bottom,
            "labels_top": self.labels_top,
            "labels_left": self.labels_left,
            "labels_right": self.labels_right
        }
        with open(filename, "w") as f:
            json.dump(data, f, indent=4)

        self.mirrors = {(i, j): 0 for i in range(self.ncells) for j in range(self.ncells)}
        self.active_lasers.clear()

        self.save_puzzle_state()
        self.redraw()

if __name__ == '__main__':
    root = tk.Tk()
    app = HallOfMirrors3(root)
    root.mainloop()
