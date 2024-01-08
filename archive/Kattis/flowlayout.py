while True:
    m = int(input())
    if m == 0:
        break
    rects = []
    while True:
        h, w = map(int, input().split())
        if h == -1 and w == -1:
            break
        rects.append((w, h))
    net_w = 0
    net_h = 0
    cur_w = 0
    cur_h = 0
    for h, w in rects:
        if cur_w + w > m:
            net_w = max(net_w, cur_w)
            net_h += cur_h
            cur_w, cur_h = w, h
        else:
            cur_w += w
            cur_h = max(cur_h, h)
    net_w = max(net_w, cur_w)
    net_h += cur_h
    print(net_w, 'x', net_h)