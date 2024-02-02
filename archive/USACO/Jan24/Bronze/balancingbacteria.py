n = int(input())
arr = list(map(int, input().split()))
ans, tot, cur = 0, 0, 0
for i in range(n):
    dist = n - i
    arr[i] += tot + dist * cur
    ans += abs(arr[i])
    cur += arr[i]
    tot -= (dist + 1) * arr[i]
print(ans)