# read in a string
s = input()

# check if first half of string is equal to second half
# string must be even length
def is_rep(s):
    if len(s) % 2 == 0:
        if s[:len(s)//2] == s[len(s)//2:]:
            return True
        else:
            return False
    else:
        return False

count = 0
# check every disjoint pair of substrings
for i in range(len(s)):
    for j in range(i+1, len(s)+1):
        for k in range(j, len(s)+1):
            for l in range(k+1, len(s)+1):
                if is_rep(s[i:j] + s[k:l]):
                    count += 1
                    # print ___s[i:j]___s[k:l]___
                    space0 = "_" * i
                    space1 = "_" * (k-j)
                    space2 = "_" * (len(s)-l)
                    print(space0 + s[i:j] + space1 + s[k:l] + space2)

print(count)