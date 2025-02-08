k, r = map(int,input().split())

b = r-1
a = (2**k - 1) - b
#print(a,b)

ans = 0
fact = 1
count = 0
for i in range(k):
    num = 2 ** i
    #print(num)
    for j in range(num):
        fact *= (a-count)/(a+b-count)
        count += 1
        if fact == 0:
            break
    if fact == 0:
        break
    #print(fact)
    ans += fact

print(f'{ans:.5f}')
