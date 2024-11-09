a_str = input()
b_str = input()

a = list(map(int, a_str[::-1]))
b = list(map(int, b_str[::-1]))

if len(b) < len(a):
    a,b = b,a

if len(a) < len(b):
    a.extend([0] * (len(b) - len(a)))

N = len(a)

c = [0] * (len(a) + 1)
carry = 0
for i in range(N):
    d = carry + a[i] + b[i]
    if d >= 10:
        d -= 10
        carry = 1
    else:
        carry = 0
    c[i] = d
if carry:
    c[-1] = 1
a.append(0)
b.append(0)

a_orig = a[:]
b_orig = b[:]

def to_int(a):
    ans = 0
    for i in range(len(a)-1,-1,-1):
        char = a[i]
        ans *= 10
        ans += char
    return ans

def sub(a,b):
    if len(a) < len(b):
        a.extend([0] * (len(b) - len(a)))
    if len(b) < len(a):
        b.extend([0] * (len(a) - len(b)))
    
    N = len(a)
    c = [ad - bd for ad,bd in zip(a,b)]
    for i in range(N-1):
        if c[i] < 0:
            c[i] += 10
            c[i+1] -= 1
    while len(c) > 1 and c[-1] == 0:
        c.pop()
    return c

def sml(a,b):
    while len(a) > 1 and a[-1] == 0:
        a.pop()
    while len(b) > 1 and b[-1] == 0:
        b.pop()
    if len(a) > len(b):
        return b
    if len(b) > len(a):
        return a
    N = len(a)
    for i in range(N-1,-1,-1):
        if a[i] > b[i]:
            return b
        if b[i] > a[i]:
            return a
    return a

def check(a, c, a_orig):

    N = len(a)
    k = N  - 1
    while k >= 0:
        if a[k] <= c[k]:
            k -= 1
        else:
            break
    if k == -1:
        return [0]
    a[:k] = [0]*k
    a[k] = 0
    k += 1
    while True:
        if c[k] == a[k]:
            a[k] = 0
            k += 1
        a[k] += 1
        break
    return sub(a, a_orig)

a_ans = check(a, c, a_orig)
b_ans = check(b, c, b_orig)

ans = sml(a_ans, b_ans)
print(''.join(map(str, ans[::-1])))
