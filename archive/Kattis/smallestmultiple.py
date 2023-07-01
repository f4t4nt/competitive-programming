def gcd(a, b):
    if a == 0:
        return b
    return gcd(b % a, a)

def lcm(a, b):
    return a // gcd(a, b) * b

while True:
    try:
        line = input()
        x_values = list(map(int, line.split()))
        result = 1
        for x in x_values:
            result = lcm(result, x)
        print(result)
    except EOFError:
        break