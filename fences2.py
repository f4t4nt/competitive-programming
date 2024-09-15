import matplotlib.pyplot as plt
import numpy as np
import itertools

# bounds = 3
# side_length = 5
# posts = {
#     (0, 0): 4,
#     (-3, 3): 4,
#     (2, 1): 5,
#     (3, -3): 2,
#     (-2, -1): 2
# }

bounds = 9
side_length = 9
posts = {
    (-9, 3): 1,
    (-2, 2): 8,
    (-4, 8): 7,
    (0, 6): 3,
    (1, 1): 4,
    (3, 4): 6,
    (5, 0): 3,
    (9, -3): 11,
    (2, -2): 6,
    (4, -8): 6,
    (0, -6): 19,
    (-1, -1): 38,
    (-3, -4): 6,
    (-5, 0): 6
}

max_lens = {}
# right, top-right, top-left, left, bottom-left, bottom-right
directions = [(1, 0), (0, 1), (-1, 1), (-1, 0), (0, -1), (1, -1)]

def out_of_bounds(q, r):
    return (abs(q) > bounds or abs(r) > bounds or (abs(q + r) > bounds and q * r > 0))

class Hexagon:
    def __init__(self, q, r, side_length):
        self.q = q
        self.r = r
        self.side_length = side_length
        self.post = posts.get((q, r), 0)
        self.neighbors = self.calculate_neighbors()
        self.color = self.get_color()

    def calculate_neighbors(self):
        return [(self.q + dq, self.r + dr) for dq, dr in directions if not out_of_bounds(self.q + dq, self.r + dr)]
    
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
        self.get_max_lens()

    def create_grid(self):
        for q in range(-self.side_length, self.side_length + 1):
            for r in range(max(-self.side_length, -q - self.side_length), min(self.side_length, -q + self.side_length) + 1):
                self.hexagons[(q, r)] = Hexagon(q, r, side_length)

    def draw(self, show_coords=False, dot_posts=False, draw=True, save_to=None):
        plt.figure(figsize=(10, 10))
        for (q, r), hexagon in self.hexagons.items():
            x = np.sqrt(3) * (q + r/2)
            y = 3/2 * r
            hex_color = self.colors[hexagon.color]
            hex_x = x + np.array([np.cos(np.pi/3 * i + np.pi/6) for i in range(6)])
            hex_y = y + np.array([np.sin(np.pi/3 * i + np.pi/6) for i in range(6)])
            if hex_color != self.colors['black']:
                if hexagon.post:
                    if dot_posts:
                        plt.plot(x, y, 'ko', markersize=5)
                    else:
                        plt.text(x, y, hexagon.post, ha='center', va='center', fontsize=12)
                elif show_coords:
                    plt.text(x, y, f'{q}, {r}', ha='center', va='center', fontsize=8)
            plt.fill(hex_x, hex_y, color=hex_color, edgecolor='k')
        plt.axis('equal')
        plt.axis('off')
        if save_to:
            plt.savefig(save_to, bbox_inches='tight', pad_inches=0)
        if draw:
            plt.show()
    
    def draw_fences(self, fences):
        self.draw(draw=False)
        cnts = {}
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
            plt.fill(hex_x, hex_y, color=color, edgecolor='k')
        for (q, r), hexagon in self.hexagons.items():
            if (q, r) not in cnts:
                x = np.sqrt(3) * (q + r/2)
                y = 3/2 * r
                plt.text(x, y, f'{q}, {r}', ha='center', va='center', fontsize=8, color=(0, 0, 0, 0.5))
        for (q, r), lens in fences.items():
            x = np.sqrt(3) * (q + r/2)
            y = 3/2 * r
            for i, (dq, dr) in enumerate(directions):
                nq = q + dq * lens[i]
                nr = r + dr * lens[i]
                x_end = np.sqrt(3) * (nq + nr/2)
                y_end = 3/2 * nr
                color = 'r' if out_of_bounds(nq, nr) else 'k'
                plt.plot([x, x_end], [y, y_end], color, linewidth=2)
        plt.show()
    
    def get_max_lens(self):
        for (q, r), post in posts.items():
            max_lens[(q, r)] = []
            for i, (dq, dr) in enumerate(directions):
                nq = q + dq
                nr = r + dr
                length = 0
                while not out_of_bounds(nq, nr) and (nq, nr) not in posts and length < post:
                    length += 1
                    nq += dq
                    nr += dr
                max_lens[(q, r)].append(length)
            
    def check_connected(self, occupied):
        visited = occupied.copy()
        for q, r in self.hexagons.keys():
            if (q, r) in visited:
                continue
            if self.hexagons[(q, r)].color == 'black':
                continue
            color_set = set()
            queue = [(q, r)]
            while queue:
                q, r = queue.pop(0)
                visited.add((q, r))
                color_set.add(self.hexagons[(q, r)].color)
                for nq, nr in self.hexagons[(q, r)].neighbors:
                    if  (nq, nr) not in visited:
                        queue.append((nq, nr))
            if len(color_set) == 6:
                return True
        return False
    
    def check_fences(self, fences, raise_err=False, draw=True, ret_early=True, check_connected=True):
        # if set(fences.keys()) != set(posts.keys()):
        #     if raise_err:
        #         raise ValueError("Set of lengths keys does not match set of posts keys")
        #     else:
        #         return False
        res = True
        occupied = set(fences.keys())
        for (q, r), lens in fences.items():
            if len(lens) != 6:
                if raise_err:
                    raise ValueError("Invalid number of fences")
                elif ret_early:
                    return False
                else:
                    res = False
            if sum(lens) != posts[(q, r)]:
                if raise_err:
                    raise ValueError("Sum of fences does not match post value")
                elif ret_early:
                    return False
                else:
                    res = False
            for i, (dq, dr) in enumerate(directions):
                nq = q + dq
                nr = r + dr
                for _ in range(lens[i]):
                    if out_of_bounds(nq, nr) or (nq, nr) in occupied:
                        # if raise_err:
                        #     raise ValueError("Invalid fence placement")
                        # else:
                        #     return False
                        if ret_early:
                            return False
                        else:
                            res = False
                    occupied.add((nq, nr))
                    nq += dq
                    nr += dr
        if check_connected:
            res = self.check_connected(occupied)
        if draw:
            self.draw(dot_posts=True, draw=False)
            for q, r in occupied:
                x = np.sqrt(3) * (q + r/2)
                y = 3/2 * r
                hex_x = x + np.array([np.cos(np.pi/3 * i + np.pi/6) for i in range(6)])
                hex_y = y + np.array([np.sin(np.pi/3 * i + np.pi/6) for i in range(6)])
                plt.fill(hex_x, hex_y, color=(0, 0, 0, 0.5), edgecolor='k')
            for (q, r), lens in fences.items():
                x = np.sqrt(3) * (q + r/2)
                y = 3/2 * r
                for i, (dq, dr) in enumerate(directions):
                    nq = q + dq * lens[i]
                    nr = r + dr * lens[i]
                    x_end = np.sqrt(3) * (nq + nr/2)
                    y_end = 3/2 * nr
                    plt.plot([x, x_end], [y, y_end], 'k', linewidth=2)
            plt.show()
        return res

hex_grid = HexGrid(side_length)
# hex_grid.draw(show_coords=True, save_to='hex_grid.png')
# hex_grid.check_fences({
#     (0, 0): [0, 1, 1, 0, 2, 0],
#     (-3, 3): [2, 0, 0, 0, 2, 0],
#     (2, 1): [0, 0, 2, 0, 2, 1],
#     (3, -3): [0, 2, 0, 0, 0, 0],
#     (-2, -1): [0, 1, 1, 0, 0, 0]
# }, raise_err=True, draw=True)

def cpp():
    results = []

    def generate_valid_fences(post, target_sum, max_lengths):
        valid_fences = []
        for fence_config in itertools.product(range(max(max_lengths) + 1), repeat=6):
            if sum(fence_config) == target_sum and all(fence_config[i] <= max_lengths[i] for i in range(6)):
                valid_fences.append(tuple(fence_config))
        return valid_fences

    def solve_fences():
        global results
        
        all_valid_fences = {}
        for post in posts:
            target_sum = posts[post]
            max_lengths = max_lens[post]
            all_valid_fences[post] = set(generate_valid_fences(post, target_sum, max_lengths))
        
        bad_pairs = {}
        for post0 in posts:
            bad_pairs[post0] = {}
            for fence_config0 in all_valid_fences[post0]:
                bad_pairs[post0][fence_config0] = {}
                for post1 in posts:
                    bad_pairs[post0][fence_config0][post1] = set()
        
        for post0 in posts:
            for fence_config0 in all_valid_fences[post0]:
                for post1 in posts:
                    if post1 <= post0:
                        continue
                    for fence_config1 in all_valid_fences[post1]:
                        tmp_fences = {post0: fence_config0, post1: fence_config1}
                        if not hex_grid.check_fences(tmp_fences, raise_err=False, draw=False):
                            bad_pairs[post0][fence_config0][post1].add(fence_config1)
                            bad_pairs[post1][fence_config1][post0].add(fence_config0)
        
        def backtrack(index, fences, valid_fences):
            if index == len(posts):
                if hex_grid.check_fences(fences, raise_err=False, draw=False):
                    with open('fences2.txt', 'a') as f:
                        f.write(str(fences) + '\n')
                    results.append(fences.copy())
                return
            
            min_post = min(valid_fences, key=lambda x: len(valid_fences[x]))
            
            for fence_config in valid_fences[min_post]:
                fences[min_post] = fence_config
                new_valid_fences = valid_fences.copy()
                del new_valid_fences[min_post]
                for post in bad_pairs[min_post][fence_config]:
                    new_valid_fences[post] = new_valid_fences[post] - bad_pairs[min_post][fence_config][post]
                backtrack(index + 1, fences, new_valid_fences)
                del fences[min_post]            
            
        backtrack(0, {}, all_valid_fences)

    solve_fences()
    print(f"Found {len(results)} valid fence configurations.")

    with open('fences2.txt', 'w') as f:
        for result in results:
            f.write(str(result) + '\n')

    for i, fence_config in enumerate(results):
        hex_grid.check_fences(fence_config, draw=True)
        print(f"Configuration {i + 1}")
        print(fence_config)
        print()

configs = [
    {
        (-9, 3): [0, 0, 0, 0, 0, 1],
        (-5, 0): [2, 1, 1, 2, 0, 0],
        (-4, 8): [0, 1, 0, 1, 3, 2],
        (-3, -4): [0, 0, 2, 2, 1, 1],
        (-2, 2): [0, 2, 6, 0, 0, 0],
        (-1, -1): [3, 9, 8, 7, 3, 8],
        (0, -6): [3, 3, 4, 3, 3, 3],
        (0, 6): [0, 0, 0, 0, 0, 3],
        (1, 1): [0, 0, 1, 0, 1, 2],
        (2, -2): [0, 0, 0, 0, 0, 6],
        (3, 4): [0, 0, 0, 0, 0, 6],
        (4, -8): [1, 1, 1, 1, 1, 1],
        (5, 0): [0, 0, 0, 0, 1, 2],
        (9, -3): [0, 0, 0, 5, 6, 0]
    },
    {
        (-9, 3): [0, 0, 0, 0, 0, 1],
        (-5, 0): [1, 0, 3, 2, 0, 0],
        (-4, 8): [1, 1, 0, 4, 1, 0],
        (-3, -4): [0, 0, 2, 2, 1, 1],
        (-2, 2): [0, 4, 2, 1, 1, 0],
        (-1, -1): [3, 9, 8, 7, 3, 8],
        (0, -6): [3, 3, 4, 3, 3, 3],
        (0, 6): [0, 0, 0, 0, 0, 3],
        (1, 1): [0, 0, 1, 0, 1, 2],
        (2, -2): [0, 0, 0, 0, 0, 6],
        (3, 4): [0, 0, 0, 0, 0, 6],
        (4, -8): [1, 1, 1, 1, 1, 1],
        (5, 0): [0, 0, 0, 0, 1, 2],
        (9, -3): [0, 0, 0, 5, 6, 0]
    },
    {
        (-9, 3): [0, 0, 0, 0, 0, 1],
        (-5, 0): [0, 0, 2, 4, 0, 0],
        (-4, 8): [0, 0, 0, 2, 3, 2],
        (-3, -4): [0, 0, 2, 2, 1, 1],
        (-2, 2): [0, 0, 6, 1, 1, 0],
        (-1, -1): [3, 9, 8, 7, 3, 8],
        (0, -6): [3, 3, 4, 3, 3, 3],
        (0, 6): [0, 0, 0, 0, 0, 3],
        (1, 1): [0, 0, 1, 0, 1, 2],
        (2, -2): [0, 0, 0, 0, 0, 6],
        (3, 4): [0, 0, 0, 0, 0, 6],
        (4, -8): [1, 1, 1, 1, 1, 1],
        (5, 0): [0, 0, 0, 0, 1, 2],
        (9, -3): [0, 0, 0, 5, 6, 0]
    },
    {
        (-9, 3): [0, 0, 0, 0, 0, 1],
        (-5, 0): [0, 1, 4, 1, 0, 0],
        (-4, 8): [2, 0, 0, 3, 0, 2],
        (-3, -4): [0, 0, 2, 2, 1, 1],
        (-2, 2): [0, 1, 6, 0, 1, 0],
        (-1, -1): [3, 9, 8, 7, 3, 8],
        (0, -6): [3, 3, 4, 3, 3, 3],
        (0, 6): [0, 0, 0, 0, 0, 3],
        (1, 1): [0, 0, 1, 0, 1, 2],
        (2, -2): [0, 0, 0, 0, 0, 6],
        (3, 4): [0, 0, 0, 0, 0, 6],
        (4, -8): [1, 1, 1, 1, 1, 1],
        (5, 0): [0, 0, 0, 0, 1, 2],
        (9, -3): [0, 0, 0, 5, 6, 0]
    }
    # {
    #     (-9, 3): [0, 0, 0, 0, 0, 1],
    #     (-5, 0): [2, 0, 4, 0, 0, 0],
    #     (-4, 8): [2, 1, 0, 1, 3, 0],
    #     (-3, -4): [0, 0, 2, 2, 1, 1],
    #     (-2, 2): [0, 5, 1, 1, 1, 0],
    #     (-1, -1): [2, 10, 8, 7, 3, 8],
    #     (0, -6): [3, 3, 4, 3, 3, 3],
    #     (0, 6): [0, 0, 0, 0, 0, 3],
    #     (1, 1): [0, 0, 0, 0, 1, 3],
    #     (2, -2): [0, 0, 0, 0, 0, 6],
    #     (3, 4): [0, 0, 0, 0, 0, 6],
    #     (4, -8): [1, 1, 1, 1, 1, 1],
    #     (5, 0): [0, 0, 0, 0, 1, 2],
    #     (9, -3): [0, 0, 0, 5, 6, 0]
    # },
    # {
    #     (-9, 3): [0, 0, 0, 0, 0, 1],
    #     (-5, 0): [0, 0, 2, 4, 0, 0],
    #     (-4, 8): [0, 0, 0, 2, 3, 2],
    #     (-3, -4): [0, 0, 2, 2, 1, 1],
    #     (-2, 2): [0, 0, 6, 1, 1, 0],
    #     (-1, -1): [2, 10, 8, 7, 3, 8],
    #     (0, -6): [3, 3, 4, 3, 3, 3],
    #     (0, 6): [0, 0, 0, 0, 0, 3],
    #     (1, 1): [0, 0, 0, 0, 1, 3],
    #     (2, -2): [0, 0, 0, 0, 0, 6],
    #     (3, 4): [0, 0, 0, 0, 0, 6],
    #     (4, -8): [1, 1, 1, 1, 1, 1],
    #     (5, 0): [0, 0, 0, 0, 1, 2],
    #     (9, -3): [0, 0, 0, 5, 6, 0]
    # },
    # {
    #     (-9, 3): [0, 0, 0, 0, 0, 1],
    #     (-5, 0): [0, 2, 0, 4, 0, 0],
    #     (-4, 8): [0, 1, 1, 2, 2, 1],
    #     (-3, -4): [0, 0, 2, 2, 1, 1],
    #     (-2, 2): [0, 5, 3, 0, 0, 0],
    #     (-1, -1): [3, 9, 8, 7, 3, 8],
    #     (0, -6): [3, 3, 4, 3, 3, 3],
    #     (0, 6): [0, 0, 0, 0, 0, 3],
    #     (1, 1): [0, 0, 0, 0, 1, 3],
    #     (2, -2): [0, 0, 0, 0, 0, 6],
    #     (3, 4): [0, 0, 0, 0, 0, 6],
    #     (4, -8): [1, 1, 1, 1, 1, 1],
    #     (5, 0): [0, 0, 0, 0, 1, 2],
    #     (9, -3): [0, 0, 0, 5, 6, 0]
    # }
]

for config in configs:
    hex_grid.check_fences(config, raise_err=True, draw=True)