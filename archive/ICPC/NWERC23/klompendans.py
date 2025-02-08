n = int(input())

a,b = map(int,input().split())
c,d = map(int, input().split())
moves1 = []
moves2 = []
moves = [moves1, moves2]
for xs in [-1,1]:
    for ys in [-1,1]:
        moves1.append([a*xs, b*ys])
        moves2.append([c*xs, d*ys])
        moves1.append([b*xs, a*ys])
        moves2.append([d*xs, c*ys])

def pos(i):
    return (i // n), i % n

visited1 = [False] * (n * n)
visited2 = visited1[:]
visited = [visited1, visited2]

stack = [(0,0), (0,1)]

while stack:
    curr, parity = stack.pop()
    if visited[parity][curr]:
        continue
    visited[parity][curr] = True
    x,y = pos(curr)
    for dx,dy in moves[parity]:
        xn,yn = x + dx, y + dy
        if min(xn,yn) < 0 or max(xn,yn) >= n:
            continue
        stack.append([n * xn + yn, 1-parity])

ans = 0
for i in range(n*n):
    ans += visited[0][i] or visited[1][i]
print(ans)