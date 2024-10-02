grid = [
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 1],
    [0, 0, 1, 1, 1, 1],
    [1, 1, 1, 1, 2, 2],
    [1, 1, 2, 2, 2, 2],
    [2, 2, 2, 2, 2, 2]
]

knight_moves = [
    (2, 1), (1, 2), (-1, 2), (-2, 1),
    (-2, -1), (-1, -2), (1, -2), (2, -1)
]

def precompute_neighbors(N):
    neighbors = {}
    for x in range(N):
        for y in range(N):
            moves = []
            for dx, dy in knight_moves:
                nx, ny = x + dx, y + dy
                if 0 <= nx < N and 0 <= ny < N:
                    moves.append((nx, ny))
            neighbors[(x, y)] = moves
    return neighbors

def stringify(path):
    return [chr(x + ord('a')) + str(y + 1) for x, y in path]

def mirror(path):
    return [(x, 5 - y) for x, y in path]

class F:
    def __init__(self, path, idx):
        x, y = path[idx]
        self.val = grid[x][y]
        self.type = "."
        if idx > 0:
            px, py = path[idx - 1]
            prv = grid[px][py]
            if prv == self.val:
                self.type = "+"
            else:
                self.type = "*"
            self.child = F(path, idx - 1)

    def eval(self, abc):
        if self.type == ".":
            res = abc[self.val]
        elif self.type == "+":
            res = self.child.eval(abc) + abc[self.val]
        elif self.type == "*":
            res = self.child.eval(abc) * abc[self.val]
        return res

def find_paths(x, y, end_x, end_y, visited, path, paths_a1f6, paths_a6f1, neighbors, MAX_LEN, EXACT_LEN=None):
    if len(path) > MAX_LEN or (EXACT_LEN is not None and len(path) > EXACT_LEN):
        return
    if (x, y) == (end_x, end_y):
        if EXACT_LEN is not None and len(path) != EXACT_LEN:
            return
        path_ = stringify(path)
        path_f = F(path, len(path) - 1)
        paths_a1f6.append((path_, path_f))
        mirror_ = mirror(path)
        mirror_f = F(mirror_, len(path) - 1)
        mirror_ = stringify(mirror_)
        paths_a6f1.append((mirror_, mirror_f))
        return
    for nx, ny in neighbors[(x, y)]:
        if not visited[nx][ny]:
            visited[nx][ny] = True
            path.append((nx, ny))
            find_paths(nx, ny, end_x, end_y, visited, path, paths_a1f6, paths_a6f1, neighbors, MAX_LEN)
            path.pop()
            visited[nx][ny] = False

def main():
    N = 6
    MAX_LEN = 13
    EXACT_LEN = 9

    neighbors = precompute_neighbors(N)

    visited = [[False]*N for _ in range(N)]
    visited[0][0] = True
    path = [(0, 0)]
    paths_a1f6 = []
    paths_a6f1 = []

    find_paths(0, 0, 5, 5, visited, path, paths_a1f6, paths_a6f1, neighbors, MAX_LEN, EXACT_LEN)

    abcs = []
    for A in range(1, 51):
        for B in range(1, 51 - A):
            if A == B:
                continue
            for C in range(1, 51 - A - B):
                if A == C or B == C:
                    continue
                abcs.append((A, B, C))
    abcs.sort(key=lambda x: x[0] + x[1] + x[2])
    
    for abc in abcs:
        ok = False
        for path, f in paths_a1f6:
            if f.eval(abc) == 2024:
                ok = True
                f.eval(abc)
                cur = ','.join(map(str, abc)) + ',' + ','.join(path) + ','
                break
        if not ok:
            continue
        ok = False
        for path, f in paths_a6f1:
            if f.eval(abc) == 2024:
                ok = True
                cur += ','.join(path)
                break
        if ok:
            print(cur)

if __name__ == "__main__":
    main()