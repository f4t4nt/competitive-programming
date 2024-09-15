def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    n = int(data[0])
    p = int(data[1])
    c = list(map(int, data[2:2 + n]))
    
    cur = 0
    for i in range(n):
        if cur + c[i] + i * (c[i] - 1) > p:
            print(i)
            return
        cur += c[i]
    
    print(n)

if __name__ == "__main__":
    main()
