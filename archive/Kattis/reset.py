def valid(mid, n, c, tasks):
    times = [0] * n
    work = [0] * n
    total = 0
    last = 0
    for i in range(n):
        times[i] = min(mid + 1, (tasks[i][0] + tasks[i][1] - 1) // tasks[i][1])
        work[i] = max(0, tasks[i][0] - times[i] * tasks[i][1])
        total += times[i] + work[i]
        if times[i] == mid + 1:
            last += work[i] + 1
    if total > (mid + 1) * c or last > c:
        return False
    return True

n, c = map(int, input().split())
tasks = []
for i in range(n):
    tasks.append(list(map(int, input().split())))
lo, hi = 0, int(2e14)
while lo < hi:
    mid = (lo + hi) // 2
    if valid(mid, n, c, tasks):
        hi = mid
    else:
        lo = mid + 1
print(lo)