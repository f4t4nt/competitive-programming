import sys
n,k = map(int, input().split())

def shoot(i,j):
    if min(i,j) < 0 or max(i,j) >= n:
        return 0
    print(i+1,j+1)
    sys.stdout.flush()
    s = input()
    return ['miss','hit','sunk'].index(s)

pos = []
for i in range(n):
    for j in range(n):
        if (i-j) % 5 == 0:
            res = shoot(i,j)
            if res:
                pos.append((i,j))

sunk_count = 0

dirs = [[0,1],
        [0,-1],
        [1,0],
        [-1,0]
        ]

for x,y in pos:
    for i in range(1,5):
        for dx,dy in dirs:
            r = shoot(x+dx*i, y+dy*i)
            if r == 2:
                sunk_count += 1
                if sunk_count == k:
                    sys.exit()
