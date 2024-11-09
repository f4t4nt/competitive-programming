import random
import time

def simulate_trial():
    x_b, y_b = random.uniform(0, 1), random.uniform(0, 1)
    x_r, y_r = random.uniform(0, 1), random.uniform(0, 1)

    d_left = x_b
    d_right = 1 - x_b
    d_bottom = y_b
    d_top = 1 - y_b

    min_distance = min(d_left, d_right, d_bottom, d_top)
    closest_sides = []

    if abs(d_left - min_distance) < 1e-9:
        closest_sides.append(('vertical', 0))
    if abs(d_right - min_distance) < 1e-9:
        closest_sides.append(('vertical', 1))
    if abs(d_bottom - min_distance) < 1e-9:
        closest_sides.append(('horizontal', 0))
    if abs(d_top - min_distance) < 1e-9:
        closest_sides.append(('horizontal', 1))

    for side_type, side_value in closest_sides:
        if side_type == 'vertical':
            x = side_value
            denominator = 2 * (y_r - y_b)
            if abs(denominator) < 1e-9:
                continue
            numerator = 2 * x * (x_r - x_b) + (x_b**2 - x_r**2) + (y_b**2 - y_r**2)
            y = - numerator / denominator
            if 0 <= y <= 1:
                return True
        else:
            y = side_value
            denominator = 2 * (x_r - x_b)
            if abs(denominator) < 1e-9:
                continue
            numerator = 2 * y * (y_r - y_b) + (x_b**2 - x_r**2) + (y_b**2 - y_r**2)
            x = - numerator / denominator
            if 0 <= x <= 1:
                return True

    return False

def estimate_probability(num_samples):
    success_count = 0
    for _ in range(num_samples):
        if simulate_trial():
            success_count += 1
    probability = success_count / num_samples
    return probability

def main():
    num_samples = 10_000_000
    start_time = time.time()
    probability = estimate_probability(num_samples)
    end_time = time.time()
    margin_of_error = 1.96 * ((probability * (1 - probability) / num_samples) ** 0.5)
    lower_bound = probability - margin_of_error
    upper_bound = probability + margin_of_error
    theoretical_probability = 0.4914075788383079881742352

    print(f'Time taken: {end_time - start_time:.2f} seconds')
    print(f'Average time per sample: {(end_time - start_time) / num_samples:.10f} seconds')
    print(f'Estimated Probability (based on {num_samples} samples): {probability:.10f} ± {margin_of_error:.10f}')
    print(f'Lower Bound: {probability - margin_of_error:.10f}')
    print(f'Upper Bound: {probability + margin_of_error:.10f}')
    print(f'Theoretical Probability: {theoretical_probability:.10f}')
    print(f'Error: {abs(theoretical_probability - probability):.10f}')
    if lower_bound <= theoretical_probability <= upper_bound:
        print('The theoretical probability is within the confidence interval.')
    else:
        print('The theoretical probability is not within the confidence interval.')

if __name__ == '__main__':
    main()