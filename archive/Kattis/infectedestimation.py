import math
import random

DBG = False

TOTAL_POPULATION = 10_000_000
FACTOR = 1.01

def run_simulation(actual_infected=None, suppress_output=False):
    history = []
    
    x = 100
    xs = {}
    while x <= TOTAL_POPULATION / 2:
        xs[x] = 1
        x = int(x * FACTOR)
        if x >= TOTAL_POPULATION / 2:
            break

    total_prob = sum(xs.values())
    for k in xs:
        xs[k] = xs[k] / total_prob

    def get_x_star():
        log_x_star = 0
        for x_, p in xs.items():
            if p > 0:
                log_x_star += p * math.log(x_)
        return int(math.exp(log_x_star))

    def probability_positive_pre(k_, x_):
        return 1 - (1 - x_ / TOTAL_POPULATION) ** k_

    def probability_result_given_x(k_, result_, x_):
        p_positive = probability_positive_pre(k_, x_)
        return p_positive if result_ else 1 - p_positive

    def get_best_k():
        lo = 1
        hi = TOTAL_POPULATION
        x_star = get_x_star()
        while hi - lo > 1:
            mid = (lo + hi) / 2
            p_positive = probability_positive_pre(int(mid), x_star)
            if p_positive > 0.5:
                hi = mid
            else:
                lo = mid
        k_ = int(lo * random.uniform(0.9, 1.1))
        k_ = max(1, min(k_, TOTAL_POPULATION))
        return k_

    for _ in range(50):
        k = get_best_k()
        if DBG and actual_infected is not None:
            p_positive = probability_positive_pre(k, actual_infected)
            result = random.random() < p_positive
            if not suppress_output:
                print(f"test {k}")
                print(int(result))
        else:
            print(f"test {k}")
            result_input = input().strip()
            result = result_input == "1"
        history.append((k, result))

        xs_post = {}
        total_prob_post = 0
        for x_ in xs:
            p_likelihood = probability_result_given_x(k, result, x_)
            p_posterior = xs[x_] * p_likelihood
            xs_post[x_] = p_posterior
            total_prob_post += p_posterior
        if total_prob_post > 0:
            for x_ in xs:
                xs[x_] = xs_post[x_] / total_prob_post
        else:
            total_xs = len(xs)
            for x_ in xs:
                xs[x_] = 1.0 / total_xs

    estimate = get_x_star()
    estimate = max(100, min(5_000_000, estimate))
    if DBG and actual_infected is not None:
        if actual_infected / 2 <= estimate <= actual_infected * 2:
            pass
        else:
            return actual_infected, estimate
    else:
        print(f"estimate {estimate}")
    return None


if DBG:
    start = 100
    end = TOTAL_POPULATION // 2
    interval = 10_000

    failures = []
    actual_infected_list = list(range(start, end + 1, interval))
    for sim_num, actual_infected in enumerate(actual_infected_list):
        failure = run_simulation(actual_infected, suppress_output=True)
        if failure:
            actual, estimate = failure
            failures.append((sim_num + 1, actual, estimate))

    print(f"Total simulations: {len(actual_infected_list)}")
    print(f"Number of failures: {len(failures)}")
    if failures:
        print("Failures:")
        for sim_num, actual, estimate in failures:
            print(f"Simulation {sim_num}: Actual infected = {actual}, Estimated = {estimate}")
else:
    run_simulation()