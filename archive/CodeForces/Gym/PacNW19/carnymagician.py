n, m, k = map(int, input().split())
fact = [1] * (n + 1)
for i in range(1, n + 1):
    fact[i] = fact[i - 1] * i
choose = [[0] * (n + 1) for _ in range(n + 1)]
for i in range(n + 1):
    for j in range(i + 1):
        choose[i][j] = fact[i] // (fact[j] * fact[i - j])
mem = {}
def eval(n, m, x):
    if not (n, m, x) in mem:
        if n < 0 or m < 0 or x < 0:
            mem[(n, m, x)] = 0
        elif m > 0:
            mem[(n, m, x)] = choose[x][m] * eval(n - m, 0, x - m)
        elif x == 0:
            mem[(n, m, x)] = fact[n]
        else:
            mem[(n, m, x)] = (x - 1) * eval(n - 1, 0, x - 2) + (n - x) * eval(n - 1, 0, x - 1)
    return mem[(n, m, x)]
ans = [0] * n
vis = [False] * n
for i in range(n):
    for j in range(n):
        if vis[j]:
            continue
        ans[i] = j + 1
        vis[j] = True
        if i == j:
            m -= 1
        rem = sum(not vis[j] for j in range(i + 1, n))
        tmp = eval(n - i - 1, m, rem)
        if tmp >= k:
            break
        k -= tmp
        ans[i] = 0
        vis[j] = False
        if i == j:
            m += 1
    if ans[i] == 0:
        print(-1)
        exit()
print(*ans)