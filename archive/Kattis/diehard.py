d1 = list(map(int, input().split()))
d2 = list(map(int, input().split()))
d3 = list(map(int, input().split()))

good1 = True
good2 = True
good3 = True
count = 0
for x in d1:
    for y in d2:
        if x > y:
            count += 1
        if y > x:
            count -= 1

if count < 0:
    good1 = False
if count > 0:
    good2 = False

count = 0
for x in d1:
    for y in d3:
        if x > y:
            count += 1
        elif y > x:
            count -= 1
if count < 0:
    good1 = False
if count > 0:
    good3 = False

count = 0
for x in d2:
    for y in d3:
        if x > y:
            count += 1
        elif y > x:
            count -= 1
if count < 0:
    good2 = False
if count > 0:
    good3 = False

if (d1 == d2) and all([item == d1[0] for item in d1]):
    good1 = False
    good2 = False

if (d1 == d3) and all([item == d1[0] for item in d1]):
    good1 = False
    good3 = False

if (d2 == d3) and all([item == d2[0] for item in d2]):
    good2 = False
    good3 = False

if good1:
    print(1)
elif good2:
    print(2)
elif good3:
    print(3)
else:
    print('No dice')