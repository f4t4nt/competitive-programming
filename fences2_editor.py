import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np
import json
import os

class HexGridApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Hex Grid Fence Adjuster")
        self.master.geometry("1200x800")

        self.bounds = 9
        self.side_length = 9
        self.directions = ["right", "top-right", "top-left", "left", "bottom-left", "bottom-right"]
        
        self.load_fences()
        self.create_widgets()
        self.update_grid()

    def load_fences(self):
        if os.path.exists('fences2.json'):
            with open('fences2.json', 'r') as f:
                loaded_fences = json.load(f)
                self.fences = {eval(k): v for k, v in loaded_fences.items()}
        else:
            self.fences = {coord: [0, 0, 0, 0, 0, 0] for coord in posts.keys()}
        
    def save_fences(self):
        fences_to_save = {str(k): v for k, v in self.fences.items()}
        with open('fences2.json', 'w') as f:
            json.dump(fences_to_save, f, indent=4)

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
        hex_grid.draw_fences(self.ax, self.fences)
        self.canvas.draw()
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
        self.create_grid()

    def create_grid(self):
        for q in range(-self.side_length, self.side_length + 1):
            for r in range(max(-self.side_length, -q - self.side_length), min(self.side_length, -q + self.side_length) + 1):
                self.hexagons[(q, r)] = Hexagon(q, r)

    def draw_fences(self, ax, fences):
        ax.clear()

        cnts = {}

        for (q, r), hexagon in self.hexagons.items():
            x = np.sqrt(3) * (q + r/2)
            y = 3/2 * r
            hex_color = self.colors[hexagon.color]
            hex_x = x + np.array([np.cos(np.pi/3 * i + np.pi/6) for i in range(6)])
            hex_y = y + np.array([np.sin(np.pi/3 * i + np.pi/6) for i in range(6)])
            ax.fill(hex_x, hex_y, color=hex_color, edgecolor='k')
            if hexagon.post:
                cur_sum = sum([fences[(q, r)][i] for i in range(6)])
                ax.text(x, y, f'{q}, {r}', ha='center', va='top', fontsize=8, color='k')
                ax.text(x, y, f'{cur_sum}/{hexagon.post}', ha='center', va='bottom', fontsize=16, color='k')
                if cur_sum != hexagon.post:
                    cnts[(q, r)] = float('inf')
            else:
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
            color = (0, 0, 0, 0.5) if cnt == 1 else (1, 0, 0)
            ax.fill(hex_x, hex_y, color=color, edgecolor='k')

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
