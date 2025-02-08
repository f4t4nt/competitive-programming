n,k = map(int, input().split())

h = []
for _ in range(n):
    h.append(list(map(int, input().split())))
h.sort()

h1 = [[-item[0], item[1]] for item in h if item[0] < 0]
h2 = [item for item in h if item[0] >= 0]

h1 = h1[::-1]

cost = 0
rem = 0
while h2:
    x,m = h2.pop()
    if rem >= m:
        rem -= m
        continue
    m -= rem
    rem = 0
    trips = (m + (k-1)) // k
    cost += 2 * x * trips
    rem = trips * k - m

rem = 0
while h1:
    x,m = h1.pop()
    if rem >= m:
        rem -= m
        continue
    m -= rem
    rem = 0
    trips = (m + (k-1)) // k
    cost += 2 * x * trips
    rem = trips * k - m


print(cost)
