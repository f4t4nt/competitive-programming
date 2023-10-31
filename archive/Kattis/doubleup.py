n = int(input())
a = list(map(int, input().split()))

while len(a) > 1:
    i = 0
    ok = False
    while i < len(a) - 1:
        if a[i] == a[i + 1]:
            a[i] *= 2
            a.pop(i + 1)
            ok = True
        else:
            i += 1
    if not ok:
        a.pop(a.index(min(a)))

print(a[0])