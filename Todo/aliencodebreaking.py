MOD, BASE = 2 ** 20, 27

ref = [0]
while (33 * ref[-1] + 1) % MOD != 0:
    ref += [(33 * ref[-1] + 1) % MOD]

def str_to_arr(s):
    rv = [0] * len(s)
    for i in range(len(s)):
        if s[i] == ' ':
            rv[i] = BASE - 1
        else:
            rv[i] = ord(s[i]) - ord('A')
    return rv

def arr_to_str(arr):
    rv = ''
    for i in range(len(arr)):
        if arr[i] != BASE - 1:
            rv += chr(arr[i] + ord('A'))
        else:
            rv += ' '
    return rv

def unwrap_digits(x, base=10):
    rv = []
    while x > 0:
        rv += [x % base]
        x //= base
    rv.reverse()
    return rv

def crutch(digits, base_src=10, base_dst=BASE):
    x = 0
    for d in digits:
        x = x * base_src + d
    rv = []
    while x > 0:
        rv += [x % base_dst]
        x //= base_dst
    rv.reverse()
    return rv

# multiply x and y, both in base_src in digit form
# return the result in base_dst in digit form
# use karatsuba
# digits are listed from most significant to least significant
# properly carry over etc
def add(digits_x, digits_y, base_src=10, base_dst=BASE):
    digits_x, digits_y = resize_arrs(digits_x, digits_y)
    rv = [0] * len(digits_x)
    carry = 0
    for i in range(len(digits_x)):
        rv[i] = (digits_x[i] + digits_y[i] + carry) % base_dst
        carry = (digits_x[i] + digits_y[i] + carry) // base_dst
    return rv

def sub(digits_x, digits_y, base_src=10, base_dst=BASE):
    digits_x, digits_y = resize_arrs(digits_x, digits_y)
    rv = [0] * len(digits_x)
    carry = 0
    for i in range(len(digits_x)):
        rv[i] = (digits_x[i] - digits_y[i] - carry) % base_dst
        carry = (digits_x[i] - digits_y[i] - carry) // base_dst
    return rv

def mul(digits_x, digits_y, base_src=10, base_dst=BASE):
    # use karatsuba
    digits_x, digits_y = resize_arrs(digits_x, digits_y)
    if len(digits_x) == 1:
        return unwrap_digits(digits_x[0] * digits_y[0], base_dst)
    digits_x_l, digits_x_r = digits_x[:len(digits_x) // 2], digits_x[len(digits_x) // 2:]
    digits_y_l, digits_y_r = digits_y[:len(digits_y) // 2], digits_y[len(digits_y) // 2:]
    digits_z0 = mul(digits_x_l, digits_y_l, base_src, base_dst)
    digits_z2 = mul(digits_x_r, digits_y_r, base_src, base_dst)
    digits_z1 = sub(mul(add(digits_x_l, digits_x_r), add(digits_y_l, digits_y_r)), add(digits_z0, digits_z2))

# digits are already unwrapped
def convert_base(digits, base_src=10, base_dst=BASE):
    if len(digits) == 1:
        return unwrap_digits(digits[0], base_dst)
    digits_l_src, digits_r_src = digits[:len(digits) // 2], digits[len(digits) // 2:]
    digits_l_dst = convert_base(digits_l_src, base_src, base_dst)
    digits_r_dst = convert_base(digits_r_src, base_src, base_dst)
    pow_l = pow(unwrap_digits(base_src, base_dst), len(digits_r_src), base_dst, base_dst)
    return add(mul(digits_l_dst, pow_l), digits_r_dst)
    
# for karatsuba, pad in the front
def resize_arrs(arr1, arr2):
    n = max(len(arr1), len(arr2))
    arr1 = [0] * (n - len(arr1)) + arr1
    arr2 = [0] * (n - len(arr2)) + arr2
    return arr1, arr2

def pad_arr(arr1, arr2):
    rv = [0] * len(arr1)
    for i in range(len(arr1)):
        rv[i] = (arr1[i] + arr2[i]) % BASE
    return rv

n, x = map(int, input().split())
s = input()
assert len(s) == n
arr = str_to_arr(s)
col_sum = [0] * x
for i in range(x):
    col_sum[0] = (col_sum[0] + ref[(i * x + 1) % len(ref)]) % MOD
for i in range(1, x):
    col_sum[i] = (33 * col_sum[i - 1] + x) % MOD
b10 = []
for c in col_sum:
    b10 += unwrap_digits(c)
b27 = convert_base(b10, 10, 10)
assert b27 == crutch(b10)
pad = pad_arr(arr, b27)
rv = arr_to_str(pad)
print(rv)