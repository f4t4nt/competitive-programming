l, m = map(int, input().split())
class Lawnmower:
    def __init__(self, n, p, c, t, r):
        self.n = n
        self.p = p
        self.c = c
        self.t = t
        self.r = r
    def is_valid(self):
        return 10080 * self.c * self.t / (self.t + self.r) >= l
best_p = 1e18
best_lawnmower = None
for _ in range(m):
    n, *rest = input().split(',')
    p, c, t, r = map(int, rest)
    lawnmower = Lawnmower(n, p, c, t, r)
    if lawnmower.is_valid():
        if p < best_p:
            best_p = p
            best_lawnmower = [lawnmower]
        elif p == best_p:
            best_lawnmower.append(lawnmower)
if best_lawnmower is None:
    print("no such mower")
else:
    print('\n'.join(map(lambda x: x.n, best_lawnmower)))