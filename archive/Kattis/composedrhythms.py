
n = int(input())
print(n // 2)
if n % 2 == 1:
    print(3, *([2]*(n // 2 - 1)))
else:
    print(*([2] * (n//2)))
