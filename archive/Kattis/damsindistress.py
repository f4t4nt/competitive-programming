n,w = map(int, input().split())
ans = [0] * (n+1)
ans[0] = w
for i in range(1, n+1):
    d,cap,u = map(int, input().split())
    ans[i] = max(cap, ans[d]) - u
print(min(ans))