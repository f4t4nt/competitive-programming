import sys
xs, ys = map(int, input().split())
xt, yt = map(int, input().split())
xp, yp = map(int, input().split())

BOUND = 10 ** 5

def get_valid_corner(x, y):
    global xp, yp
    if xp >= x:
        if yp >= y:
            return - BOUND, -BOUND
        return - BOUND, BOUND
    if yp >= y:
        return BOUND, -BOUND
    return BOUND, BOUND

x1, y1 = get_valid_corner(xs, ys)
xn, yn = get_valid_corner(xt, yt)

if x1 == xn and y1 == yn:
    print(1)
    print(x1, y1)
    sys.exit()
if x1 == xn or y1 == yn:
    print(2)
    print(x1, y1)
    print(xn, yn)
    sys.exit()
print(3)
print(x1, y1)
print(xn, y1)
print(xn, yn)
