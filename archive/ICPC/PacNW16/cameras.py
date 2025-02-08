n,k,r = map(int, input().split())

cams = []
for _ in range(k):
    cams.append(int(input()))

cams.sort()
has_cam = [False]*n
for cam in cams:
    has_cam[cam-1]=True

pfs = [0]*(n+1)
for i in range(n):
    pfs[i+1] = pfs[i] + has_cam[i]

added = []
for i in range(n-r+1):
    #print(i,added)
    count = pfs[i+r] - pfs[i]
    if added and added[-1] >= i:
        count += 1
    if len(added) >= 2 and added[-2] >= i:
        count += 1
    if count >= 2:
        continue
    if count == 1:
        if has_cam[i+r-1]:
            added.append(i+r-2)
        else:
            added.append(i+r-1)
        continue
    added.append(i+r-2)
    added.append(i+r-1)

print(len(added))
