from decimal import Decimal, getcontext, ROUND_HALF_EVEN

getcontext().prec = 30
getcontext().rounding = ROUND_HALF_EVEN

n = int(input())
r = list(map(int, input().split()))

total = Decimal(0)
for i in range(n):
    for j in range(i + 1, n):
        a = r[i]
        b = r[j]
        t = min(a, b + 1)
        term = Decimal((t - 1) * t) / (2 * b) + (a - t)
        total += term / a

print(total.quantize(Decimal("0.000001")))
