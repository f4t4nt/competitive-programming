import sys
n = int(input())
nums = list(map(int, input().split()))
nums.sort()
if len(nums) == 1:
    print(nums[0])
    sys.exit()
k =nums.count(1)
k2 = nums.count(2)
if k == 0:
    s = '*'.join(map(str, nums))
    print(s)
elif k == 1:
    s = f'(1+{nums[1]})*' + '*'.join(map(str, nums[2:]))
    print(s.strip('*'))
else:
    remain = nums[k:]
    remain = remain[::-1]
    remain = list(map(str, remain))
    pile = []
    while k > 1:
        if remain and eval(remain[-1]) == 2:
            pile.append(f'({remain[-1]}+1)')
            k -= 1
            remain.pop()
            continue
        elif k > 1:
            remain.append('(1+1)')
            k -= 2
    if k:
        if remain and eval(remain[-1]) == 2:
            pile.append(f'({remain[-1]}+1)')
            remain.pop()
        else:
            pile[-1] = f'({pile[-1]}+1)'
    print('*'.join(pile + remain))