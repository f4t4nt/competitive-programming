import tkinter as tk
from tkinter import ttk, messagebox
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np
import json
import os

def are_adjacent(hex1, hex2):
    return abs(hex1[0] - hex2[0]) <= 1 and abs(hex1[1] - hex2[1]) <= 1 and abs((hex1[0] - hex2[0]) + (hex1[1] - hex2[1])) <= 1

class HexGridApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Hex Grid Fence Adjuster")
        self.master.geometry("1200x800")
        self.bounds = 9
        self.side_length = 9
        self.directions = ["right", "top-right", "top-left", "left", "bottom-left", "bottom-right"]
        self.show_coordinates = tk.BooleanVar(value=True)
        self.show_post_sizes = tk.BooleanVar(value=True)
        self.minimalist_mode = tk.BooleanVar(value=False)
        self.black_out = tk.BooleanVar(value=False)
        self.path = []
        self.directions = [(1, 0), (0, 1), (-1, 1), (-1, 0), (0, -1), (1, -1)]
        self.load_fences()
        self.create_widgets()
        self.update_grid()

    def load_fences(self):
        if os.path.exists('fences2.json'):
            with open('fences2.json', 'r') as f:
                data = json.load(f)
                self.fences = {eval(k): v for k, v in data['fences'].items()}
                self.path = data.get('path', [])
        else:
            self.fences = {coord: [0, 0, 0, 0, 0, 0] for coord in posts.keys()}
            self.path = []

    def save_fences(self):
        fences_to_save = {str(k): v for k, v in self.fences.items()}
        data = {
            'fences': fences_to_save,
            'path': self.path
        }
        with open('fences2.json', 'w') as f:
            json.dump(data, f, indent=4)

    def create_widgets(self):
        left_frame = ttk.Frame(self.master)
        left_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=10, pady=10)

        canvas = tk.Canvas(left_frame)
        scrollbar = ttk.Scrollbar(left_frame, orient="vertical", command=canvas.yview)
        scrollable_frame = ttk.Frame(canvas)

        scrollable_frame.bind(
            "<Configure>",
            lambda e: canvas.configure(
                scrollregion=canvas.bbox("all")
            )
        )

        canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)

        self.entries = {}
        for (q, r), post_value in posts.items():
            frame = ttk.Frame(scrollable_frame)
            frame.pack(fill=tk.X, expand=True, pady=2)
            label = ttk.Label(frame, text=f"({q}, {r}): {post_value}", width=15)
            label.pack(side=tk.LEFT)
            self.entries[(q, r)] = {}
            for i, direction in enumerate(self.directions):
                dir_frame = ttk.Frame(frame)
                dir_frame.pack(side=tk.LEFT, padx=5)
                dir_label = ttk.Label(dir_frame, text=direction, width=10)
                dir_label.pack(side=tk.LEFT)
                entry = ttk.Entry(dir_frame, width=5)
                entry.insert(0, str(self.fences[(q, r)][i]))
                entry.pack(side=tk.LEFT)
                self.entries[(q, r)][direction] = entry

        canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        right_frame = ttk.Frame(self.master)
        right_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=10, pady=10)

        self.fig, self.ax = plt.subplots(figsize=(8, 8))
        self.canvas = FigureCanvasTkAgg(self.fig, master=right_frame)
        self.canvas_widget = self.canvas.get_tk_widget()
        self.canvas_widget.pack(fill=tk.BOTH, expand=True)

        update_button = ttk.Button(left_frame, text="Update", command=self.update_grid)
        update_button.pack(pady=10)

        save_button = ttk.Button(left_frame, text="Save Plot", command=self.save_plot)
        save_button.pack(pady=10)

        coord_check = ttk.Checkbutton(left_frame, text="Show Coordinates", variable=self.show_coordinates, command=self.update_grid)
        coord_check.pack(pady=5)

        post_check = ttk.Checkbutton(left_frame, text="Show Post Sizes", variable=self.show_post_sizes, command=self.update_grid)
        post_check.pack(pady=5)

        minimalist_check = ttk.Checkbutton(left_frame, text="Minimalist Mode", variable=self.minimalist_mode, command=self.update_grid)
        minimalist_check.pack(pady=5)

        black_out_check = ttk.Checkbutton(left_frame, text="Black Out", variable=self.black_out, command=self.update_grid)
        black_out_check.pack(pady=5)

        path_frame = ttk.Frame(left_frame)
        path_frame.pack(fill=tk.X, expand=True, pady=10)
        path_label = ttk.Label(path_frame, text="Add to path (q,r) or direction (0-5):")
        path_label.pack(side=tk.LEFT)
        self.path_entry = ttk.Entry(path_frame, width=10)
        self.path_entry.pack(side=tk.LEFT)
        add_path_button = ttk.Button(path_frame, text="Add", command=self.add_path_vertex_or_direction)
        add_path_button.pack(side=tk.LEFT, padx=5)
        clear_path_button = ttk.Button(path_frame, text="Clear Path", command=self.clear_path)
        clear_path_button.pack(side=tk.LEFT)
        pop_path_button = ttk.Button(path_frame, text="Pop Last", command=self.pop_last_path_vertex)
        pop_path_button.pack(side=tk.LEFT, padx=5)

    def update_grid(self):
        for (q, r), directions in self.entries.items():
            self.fences[(q, r)] = []
            for direction in self.directions:
                try:
                    length = int(directions[direction].get())
                    self.fences[(q, r)].append(length)
                except ValueError:
                    self.fences[(q, r)].append(0)

        self.save_fences()

        self.ax.clear()
        hex_grid = HexGrid(self.side_length)
        hex_grid.draw_fences(self.ax, self.fences, self.path, self.show_coordinates.get(), self.show_post_sizes.get(), self.minimalist_mode.get(), self.black_out.get())
        self.canvas.draw()

    def save_plot(self):
        fig, ax = plt.subplots(figsize=(8, 8))
        hex_grid = HexGrid(self.side_length)
        hex_grid.draw_fences(ax, self.fences, self.path, show_coordinates=False, show_post_sizes=False, minimalist_mode=self.minimalist_mode.get(), black_out=self.black_out.get())
        plt.savefig('fences2.png', dpi=300, bbox_inches='tight')
        plt.close(fig)

    def add_to_path(self, q, r):
        if (q, r) not in self.path and [q, r] not in self.path:
            if not self.path or are_adjacent(self.path[-1], (q, r)):
                self.path.append((q, r))
                self.save_fences()
                self.update_grid()
            else:
                messagebox.showinfo("Non-adjacent Vertex", f"Vertex ({q}, {r}) is not adjacent to the last vertex in the path.")
        else:
            messagebox.showinfo("Duplicate Vertex", f"Vertex ({q}, {r}) is already in the path.")
            
    def add_path_vertex_direction(self, direction):
        if not self.path:
            messagebox.showinfo("Empty Path", "The path is currently empty. Please add a starting vertex first.")
            return

        last_q, last_r = self.path[-1]
        dq, dr = directions[direction]
        new_q, new_r = last_q + dq, last_r + dr

        self.add_to_path(new_q, new_r)

    def add_path_vertex(self):
        try:
            q, r = map(int, self.path_entry.get().split(','))
            self.add_to_path(q, r)
            self.path_entry.delete(0, tk.END)
        except ValueError:
            messagebox.showerror("Invalid Input", "Invalid input. Use format: q,r")

    def add_path_vertex_or_direction(self):
        input_value = self.path_entry.get().strip()
        try:
            if ',' in input_value:
                q, r = map(int, input_value.split(','))
                self.add_to_path(q, r)
            else:
                direction = int(input_value)
                if 0 <= direction <= 5:
                    self.add_path_vertex_direction(direction)
                else:
                    raise ValueError
            self.path_entry.delete(0, tk.END)
        except ValueError:
            messagebox.showerror("Invalid Input", "Invalid input. Use format: q,r or a number 0-5")

    def pop_last_path_vertex(self):
        if self.path:
            self.path.pop()
            self.save_fences()
            self.update_grid()

    def clear_path(self):
        self.path = []
        self.save_fences()
        self.update_grid()

class Hexagon:
    def __init__(self, q, r):
        self.q = q
        self.r = r
        self.post = posts.get((q, r), 0)
        self.color = self.get_color()

    def get_color(self):
        if out_of_bounds(self.q, self.r):
            return 'black'
        if self.q == 0 and self.r == 0:
            return 'white'
        elif self.q < 0 and self.r > 0 and self.q + self.r <= 0:
            return 'blue'
        elif self.q > 0 and self.r >= 0:
            return 'yellow'
        elif self.q > 0 and self.r < 0 and self.q + self.r >= 0:
            return 'orange'
        elif self.q >= 0 and self.r < 0 and self.q + self.r < 0:
            return 'red'
        elif self.q < 0 and self.r <= 0:
            return 'purple'
        elif self.q <= 0 and self.r >= 0 and self.q + self.r > 0:
            return 'green'
        else:
            raise ValueError("Invalid coordinates")

class HexGrid:
    def __init__(self, side_length):
        self.side_length = side_length
        self.hexagons = {}
        self.colors = {
            'blue': (0.6, 0.8, 1),
            'green': (0.6, 1, 0.6),
            'yellow': (1, 1, 0.6),
            'orange': (1, 0.8, 0.6),
            'red': (1, 0.6, 0.6),
            'purple': (0.7, 0.5, 0.9),
            'white': (1, 1, 1),
            'black': (0, 0, 0)
        }
        self.minimalist_colors = {
            'white': (1, 1, 1),
            'black': (0, 0, 0)
        }
        self.create_grid()

    def create_grid(self):
        for q in range(-self.side_length, self.side_length + 1):
            for r in range(max(-self.side_length, -q - self.side_length), min(self.side_length, -q + self.side_length) + 1):
                self.hexagons[(q, r)] = Hexagon(q, r)

    def draw_fences(self, ax, fences, path, show_coordinates=True, show_post_sizes=True, minimalist_mode=False, black_out=False):
        ax.clear()
        cnts = {}

        for (q, r), hexagon in self.hexagons.items():
            x = np.sqrt(3) * (q + r/2)
            y = 3/2 * r

            if minimalist_mode:
                hex_color = self.minimalist_colors['white']
            else:
                hex_color = self.colors[hexagon.color]

            hex_x = x + np.array([np.cos(np.pi/3 * i + np.pi/6) for i in range(6)])
            hex_y = y + np.array([np.sin(np.pi/3 * i + np.pi/6) for i in range(6)])
            ax.fill(hex_x, hex_y, color=hex_color, edgecolor='k')

            if hexagon.post:
                cur_sum = sum([fences[(q, r)][i] for i in range(6)])
                if show_coordinates and not minimalist_mode:
                    ax.text(x, y, f'{q}, {r}', ha='center', va='top', fontsize=8, color='k')
                if show_post_sizes and not minimalist_mode:
                    ax.text(x, y, f'{cur_sum}/{hexagon.post}', ha='center', va='bottom', fontsize=16, color='k')
                if cur_sum != hexagon.post:
                    cnts[(q, r)] = float('inf')
            elif show_coordinates and not minimalist_mode:
                ax.text(x, y, f'{q}, {r}', ha='center', va='center', fontsize=8, color='k')

        for (q, r), lens in fences.items():
            if (q, r) not in cnts:
                cnts[(q, r)] = 0
            cnts[(q, r)] += 1
            for i, (dq, dr) in enumerate(directions):
                nq = q + dq
                nr = r + dr
                for _ in range(lens[i]):
                    if (nq, nr) not in cnts:
                        cnts[(nq, nr)] = 0
                    cnts[(nq, nr)] += 1
                    nq += dq
                    nr += dr

        for (q, r), cnt in cnts.items():
            if cnt == 0:
                continue
            x = np.sqrt(3) * (q + r/2)
            y = 3/2 * r
            hex_x = x + np.array([np.cos(np.pi/3 * i + np.pi/6) for i in range(6)])
            hex_y = y + np.array([np.sin(np.pi/3 * i + np.pi/6) for i in range(6)])
            color = self.minimalist_colors['black'] if minimalist_mode or black_out else ((0, 0, 0, 0.5) if cnt == 1 else (1, 0, 0))
            ax.fill(hex_x, hex_y, color=color, edgecolor='k')

        if not minimalist_mode:
            for (q, r), lens in fences.items():
                x = np.sqrt(3) * (q + r/2)
                y = 3/2 * r
                for i, (dq, dr) in enumerate(directions):
                    nq = q + dq * lens[i]
                    nr = r + dr * lens[i]
                    x_end = np.sqrt(3) * (nq + nr/2)
                    y_end = 3/2 * nr
                    color = 'r' if out_of_bounds(nq, nr) else 'k'
                    ax.plot([x, x_end], [y, y_end], color, linewidth=2)

        if path:
            path_x = []
            path_y = []
            for q, r in path:
                x = np.sqrt(3) * (q + r/2)
                y = 3/2 * r
                path_x.append(x)
                path_y.append(y)
                ax.plot(x, y, 'o', color='magenta', markersize=8)

            path_x.append(path_x[0])
            path_y.append(path_y[0])
            ax.plot(path_x, path_y, color='magenta', linewidth=2, linestyle='--')

        color_counts = {color: 0 for color in self.colors}
        for q, r in path:
            if (q, r) in self.hexagons:
                color_counts[self.hexagons[(q, r)].color] += 1

        count_product = 1
        for count in color_counts.values():
            if count > 0:
                count_product *= count

        count_text = "\n".join([f"{color}: {count}" for color, count in color_counts.items()])
        count_text += f"\nProduct: {count_product}"

        ax.text(0.02, 0.98, count_text, transform=ax.transAxes, verticalalignment='top', fontsize=8)

        is_adjacent = True
        for i in range(len(path) - 1):
            if not are_adjacent(path[i], path[i+1]):
                is_adjacent = False
                break

        first_last_adjacent = are_adjacent(path[0], path[-1]) if len(path) > 1 else True

        adjacency_text = "Path: "
        if is_adjacent:
            if first_last_adjacent:
                adjacency_text += "All adjacent (including first-last)"
            else:
                adjacency_text += "All adjacent (except first-last)"
        else:
            adjacency_text += "Not all adjacent"

        ax.text(0.98, 0.98, adjacency_text, transform=ax.transAxes, 
                verticalalignment='top', horizontalalignment='right', fontsize=8)

        ax.set_aspect('equal')
        ax.axis('off')

def out_of_bounds(q, r):
    return (abs(q) > bounds or abs(r) > bounds or (abs(q + r) > bounds and q * r > 0))

bounds = 9

posts = {
    (-9, 3): 1, (-2, 2): 8, (-4, 8): 7, (0, 6): 3, (1, 1): 4,
    (3, 4): 6, (5, 0): 3, (9, -3): 11, (2, -2): 6, (4, -8): 6,
    (0, -6): 19, (-1, -1): 38, (-3, -4): 6, (-5, 0): 6
}

directions = [(1, 0), (0, 1), (-1, 1), (-1, 0), (0, -1), (1, -1)]

if __name__ == "__main__":
    root = tk.Tk()
    app = HexGridApp(root)
    root.mainloop()
