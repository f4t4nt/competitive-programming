# retruns the interpolated value of y at xInput
def linear(x1, y1, x2, y2, xInput):
    return y1 + (y2 - y1) * (xInput - x1) / (x2 - x1)

def linear_interpolate(n, xKnots, yKnots, xInput):
    knots = []
    # accumulate knots
    for i in range(n):
        knots.append((xKnots[i], yKnots[i]))
    # sort knots by x
    knots.sort()
    # if xInput is left of the first knot, return the linear interpolation of the first two knots
    if xInput <= knots[0][0]:
        return linear(knots[0][0], knots[0][1], knots[1][0], knots[1][1], xInput)
    # if xInput is right of the last knot, return the linear interpolation of the last two knots
    elif xInput >= knots[n - 1][0]:
        return linear(knots[n - 2][0], knots[n - 2][1], knots[n - 1][0], knots[n - 1][1], xInput)
    else:
        # find the knot that xInput is between and return the linear interpolation of that knot and the next knot
        # don't bother with binary search due to small n
        for i in range(n - 1):
            if knots[i][0] <= xInput and xInput <= knots[i + 1][0]:
                return linear(knots[i][0], knots[i][1], knots[i + 1][0], knots[i + 1][1], xInput)
    assert(False)