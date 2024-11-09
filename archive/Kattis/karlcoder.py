import sys
flush = sys.stdout.flush
i = 2
print(f'buf[{i}]')
flush()
if input() == '0':
    print('strlen(buf) = 2')
    sys.exit()
low = 2
while True:
    high = 2 * low + 1
    print(f'buf[{high}]')
    flush()
    if input() == '0':
        break
    low = high

while low < high:
    mid = (low + high +1) // 2
    print(f'buf[{mid}]')
    flush()
    if input() == '0':
        high = mid-1
    else:
        low = mid
print(f'strlen(buf) = {low+1}')