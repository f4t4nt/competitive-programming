MOD = 10**9 + 7

def gcd(a, b):
    return b if a == 0 else gcd(b % a, a)

def lcm(a, b):
    return a // gcd(a, b) * b

n = int(input())
p = list(map(int, input().split()))

for i in range(n):
    p[i] -= 1

ans = 1
vis = [False] * n

for i in range(n):
    if vis[i]:
        continue
    j = i
    c = 0
    while not vis[j]:
        vis[j] = True
        j = p[j]
        c += 1
    ans = lcm(ans, c)

print(ans % MOD)