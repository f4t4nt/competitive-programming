n, k = [int(i) for i in input().split()]
a = [float(i) for i in input().split()]
 
binom = []
for i in range(1, 505):
    binom.append([])
    for j in range(0, i):
        if j == 0 or j == i - 1:
            binom[i - 1].append(1)
        else:
            binom[i - 1].append(binom[i - 2][j] + binom[i - 2][j - 1])
 
rv = ''
 
for i in range(0, n):
    ans = 0
    for j in range(0, n - k + 1):
        chance = (binom[n - 1 - j][k - 1] / binom[n][k])
        val = a[(i - j + n) % n]
        ans += chance * val
    rv += str(ans) + " "
 
print(rv)