def eval(v):
    n = len(v)
    ans = 0
    for i in range(n):
        ans += v[i] * (2 * i - n + 1)
    return ans

n = int(input())
xs = []
ys = []
for _ in range(n):
    x, y = map(int, input().split())
    xs.append(x)
    ys.append(y)

xs.sort()
ys.sort()

ans = eval(xs) + eval(ys)
print(ans)
