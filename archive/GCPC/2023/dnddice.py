a, b, cx, d, e = [int(i) for i in input().split(" ")]

counts = []
for i in range(0, 1005):
    counts.append([])
    for j in range(0, 55):
        counts[i].append(0)

counts[0][0] = 1;

x = 0;

for i in range(0, a):
    for j in range(0, 1005):
        for k in range(1, 5):
            if (counts[j][x]):
                counts[j + k][x + 1] += counts[j][x];
    x += 1

for i in range(0, b):
    for j in range(0, 1005):
        for k in range(1, 7):
            if (counts[j][x]):
                counts[j + k][x + 1] += counts[j][x];
    x += 1

for i in range(0, cx):
    for j in range(0, 1005):
        for k in range(1, 9):
            if (counts[j][x]):
                counts[j + k][x + 1] += counts[j][x];
    x += 1

for i in range(0, d):
    for j in range(0, 1005):
        for k in range(1, 13):
            if (counts[j][x]):
                counts[j + k][x + 1] += counts[j][x];
    x += 1

for i in range(0, e):
    for j in range(0, 1005):
        for k in range(1, 21):
            if (counts[j][x]):
                counts[j + k][x + 1] += counts[j][x];
    x += 1

c = []

for i in range(0, 1005):
    if (counts[i][x] > 0):
        c.append([counts[i][x], i])

c = sorted(c)[::-1]

st = ""

for i in range(0, len(c)):
    st += str(c[i][1])
    if i < len(c) - 1:
        st += " "

print(st)