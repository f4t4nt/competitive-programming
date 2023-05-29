import math

def bezout(a, b):
    if a == 0:
        return 0, 1
    x, y = bezout(b % a, a)
    return y - (b // a) * x, x

def crt(m, n, a, b):
    g = math.gcd(m, n)
    if a % g != b % g:
        return -1
    lcm = m // g * n
    u, v = bezout(m // g, n // g)
    k = (b - a) // g
    x = (a + m * k * u) % lcm
    if x < 0:
        x += lcm
    return x

q = int(input())

for _ in range(q):
    n = int(input())
    m_, a_ = [], []
    for i in range(n):
        m, a = map(int, input().split())
        m_ += [m]
        if i % 2 == 1:
            a = m - a
        a_ += [a]
    m, a = m_[0], a_[0]
    for i in range(1, n):
        a = crt(m, m_[i], a, a_[i])
        if a == -1:
            break
        m = m // math.gcd(m, m_[i]) * m_[i]
    print("Impossible" if a == -1 else a)