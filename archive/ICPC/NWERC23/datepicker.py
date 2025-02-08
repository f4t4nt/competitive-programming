s = []
for _ in range(7):
    s.append(list(map(lambda x: x=='.', input())))

d, h = map(int,input().split())

ans =0

for i in range(2 ** 7):
    if bin(i).count('1') != d:
        continue
    # Take the days
    sub = [item for j,item in enumerate(s) if (2 ** j) & i]
    counts = [0] * 24
    for it in sub:
        for k,b in enumerate(it):
            counts[k] += b
    counts.sort()
    ans = max(ans, sum(counts[-h:]))

print(ans / (d*h))