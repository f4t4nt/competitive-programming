N = int(input())

composite = [False] * 2_000
primes = []
for i in range(2, 2_000):
    if not composite[i]:
        primes.append(i)
        for j in range(i, 2_000, i):
            composite[j] = True


adj_list = [[] for _ in range(N)]
for _ in range(N-1):
    a,b = map(int, input().split())
    a -= 1
    b -= 1
    adj_list[a].append(b)
    adj_list[b].append(a)

bfs_order = []
visited = [False] * N
q = [(0,0)]
parents = [0] * N
while q:
    new_q = []
    for item, p in q:
        if visited[item]:
            continue
        visited[item] = True
        parents[item] = p
        bfs_order.append(item)
        for n in adj_list[item]:
            new_q.append([n, item])
    q = new_q

def get_leaf(factor, p):
    global parents, N, bfs_order
    f2 = factor[:]
    for i in range(1,N):
        if f2[i] == 1:
            f2[i] = p
    ans = [1] * N
    largest_index = -1
    largest = 0
    for i in bfs_order:
        if i == 0:
            continue
        cand = ans[parents[i]] * f2[i]
        ans[i] = cand
        if f2[i] == p and cand > largest:
            largest = cand
            largest_index = i
    return largest_index

factor = [1] * N
factor[0] = 0
ans = [1] * N
for p in primes:
    i = get_leaf(factor, p)
    # print(f'{i=}')
    if i == -1:
        break
    while i != 0:
        if factor[i] != 1:
            break
        factor[i] = p
        i = parents[i]

factor[0] = 1
for i in bfs_order:
    ans[i] = ans[parents[i]] * factor[i]

if max(ans) >= 10 ** 18:
    assert False

print(*ans)