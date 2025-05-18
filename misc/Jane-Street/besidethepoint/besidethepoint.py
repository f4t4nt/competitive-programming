import numpy as np
import matplotlib.pyplot as plt
from mpmath import mp, atan

mp.dps = 25

def A(a, b):
    s2 = mp.mpf('0.5')
    term1 = ((a**2 + b**2 - a)/2 + mp.mpf('0.25')) * mp.pi
    numerator1 = (a**2 + b**2 - a - b + mp.mpf('0.5'))
    numerator2 = (a**2 + b**2 - a + b + mp.mpf('0.5'))
    denom1 = s2 - b
    denom2 = s2 + b
    if denom1 == 0:
        arctan1 = mp.mpf(0)
    else:
        arctan1 = atan((s2 - a) / denom1)
    if denom2 == 0:
        arctan2 = mp.mpf(0)
    else:
        arctan2 = atan((s2 - a) / denom2)
    term2 = numerator1 * arctan1 + numerator2 * arctan2
    term3 = s2 - a
    result = term1 - term2 + term3
    return result

def integrate_A():
    a_min = mp.mpf('0')
    a_max = mp.mpf('0.5')
    
    def inner_integrand(b, a):
        return A(a, b)
    
    def outer_integrand(a):
        b_min = mp.mpf('0')
        b_max = a
        result = mp.quad(lambda b: inner_integrand(b, a), [b_min, b_max])
        return result
    
    total_integral = mp.quad(outer_integrand, [a_min, a_max])
    return total_integral

integral_value = integrate_A()

region_area = (mp.mpf('0.5') * mp.mpf('0.5')) / 2

average_value = integral_value / region_area

print("The integral value is:")
print(integral_value)
print("\nThe area of the region is:")
print(region_area)
print("\nThe average value of A(a, b) over the specified region is:")
print(average_value)

# 0.4914075788383079881742352

def plot_A(apply_symmetry=False):
    grid_points = 201
    a_vals = np.linspace(-0.5, 0.5, grid_points)
    b_vals = np.linspace(-0.5, 0.5, grid_points)
    A_vals = np.zeros((grid_points, grid_points))
    
    for i, a in enumerate(a_vals[grid_points//2:]):
        for j, b in enumerate(b_vals[grid_points//2:grid_points//2 + i + 1]):
            a_mp = mp.mpf(str(a))
            b_mp = mp.mpf(str(b))
            A_vals[grid_points//2 + j, grid_points//2 + i] = float(A(a_mp, b_mp))
    
    if apply_symmetry:
        for i in range(grid_points//2, grid_points):
            for j in range(grid_points//2, grid_points):
                if j > i:
                    A_vals[j, i] = A_vals[i, j]
        for i in range(grid_points//2 + 1, grid_points):
            i_neg = grid_points - i - 1
            A_vals[:, i_neg] = A_vals[:, i]
        for j in range(grid_points//2 + 1, grid_points):
            j_neg = grid_points - j - 1
            A_vals[j_neg, :] = A_vals[j, :]
    else:
        for i in range(grid_points):
            for j in range(grid_points):
                if a_vals[i] < 0 or b_vals[j] < 0 or b_vals[j] > a_vals[i]:
                    A_vals[j, i] = np.nan
    
    A_grid, B_grid = np.meshgrid(a_vals, b_vals)
    
    plt.figure(figsize=(10, 8))
    plt.contourf(A_grid, B_grid, A_vals, levels=100, cmap='viridis')
    plt.colorbar(label='A(a, b)')
    if apply_symmetry:
        plt.title('Plot of A(a, b) over the unit square with symmetry applied')
    else:
        plt.title('Plot of A(a, b) over the original domain')
    plt.xlabel('a')
    plt.ylabel('b')
    plt.savefig('plot.png')
    plt.show()

plot_A(apply_symmetry=True)

# Clear[A, a, b]
# A[a_, b_] := ((a^2 + b^2 - a)/2 + 1/4)*Pi -
#    ((a^2 + b^2 - a - b + 1/2)*ArcTan[(1/2 - a)/(1/2 - b)] +
#     (a^2 + b^2 - a + b + 1/2)*ArcTan[(1/2 - a)/(1/2 + b)]) +
#    (1/2 - a)

# desiredPrecision = 20;

# integral = NIntegrate[A[a, b], {a, 0, 1/2}, {b, 0, a},
#   WorkingPrecision -> desiredPrecision + 5,
#   PrecisionGoal -> desiredPrecision,
#   Method -> "GlobalAdaptive"
# ]

# regionArea = (1/2)*(1/2)/2;  (* Area = (base * height) / 2 *)

# averageValue = N[integral / regionArea, desiredPrecision];

# Print["The probability is approximately:"];
# Print[NumberForm[averageValue, {Infinity, desiredPrecision}]]

# 0.49140757883830798817