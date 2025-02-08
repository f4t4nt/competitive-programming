# required_digits = {'0', '2', '5'}

# def find_gcd_candidates(max_gcd=100):
#     possible_gcds = []
#     all_digits = set('0123456789')

#     for gcd_candidate in range(1, max_gcd+1):
#         gcd_str = str(gcd_candidate)
#         D = len(gcd_str)
#         modulo = 10 ** D
#         # Generate multiples of gcd_candidate
#         remainders = set()
#         valid_numbers = []
#         multiple = 1
#         while True:
#             n = gcd_candidate * multiple
#             last_D_digits = n % modulo
#             if last_D_digits in remainders:
#                 # Starting to repeat
#                 break
#             remainders.add(last_D_digits)
#             number_str = str(last_D_digits).zfill(D)
#             digits_in_number = set(number_str)
#             if len(digits_in_number) == D:
#                 # Digits are unique within the number
#                 valid_numbers.append((number_str, multiple))
#             multiple += 1
#         if len(valid_numbers) < 9:
#             continue  # Not enough valid numbers to select from
#         # Try to select 9 numbers satisfying the constraints
#         result = select_numbers(valid_numbers, required_digits)
#         if result:
#             success, selected_numbers, used_digits = result
#             # Determine the excluded digit
#             excluded_digits = all_digits - used_digits - required_digits
#             excluded_digit = excluded_digits.pop() if excluded_digits else None
#             possible_gcds.append({
#                 'gcd': gcd_candidate,
#                 'selected_numbers': selected_numbers,
#                 'excluded_digit': excluded_digit
#             })
#             print(f"\nPossible GCD found: {gcd_candidate}")
#             print(f"Selected multiples and numbers:")
#             print(f"{'Multiple':<10}\t{'Calculation':<20}\t{'Last ' + str(D) + ' digits'}")
#             print('-' * 50)
#             for num_info in selected_numbers:
#                 num_str, mult = num_info
#                 total = gcd_candidate * mult
#                 calc_str = f"{gcd_candidate} x {mult} = {total}"
#                 print(f"{mult:<10}\t{calc_str:<20}\t{num_str}")
#             # Print the excluded digit
#             print(f"Excluded Digit: {excluded_digit}")
#     return possible_gcds

# def select_numbers(valid_numbers, required_digits):
#     # Try to select 9 numbers satisfying the constraints
#     # Initialize parameters
#     positions = len(valid_numbers[0][0])  # D
#     all_digits = set('0123456789')

#     def backtrack(selected_numbers, used_digits, position_used_digits, index):
#         if len(used_digits | required_digits) > 9:
#             return None
#         if len(selected_numbers) == 9:
#             if len(used_digits | required_digits) == 9:
#                 # Exactly 9 digits used (including required digits)
#                 return True, selected_numbers.copy(), used_digits.copy()
#             else:
#                 return None
#         if index >= len(valid_numbers):
#             return None
#         number_str, multiple = valid_numbers[index]
#         digits_in_number = set(number_str)
#         # Check that new digits won't exceed 9 when combined with required digits
#         if len(used_digits | digits_in_number | required_digits) > 9:
#             # Exceeding 9 distinct digits
#             return backtrack(selected_numbers, used_digits, position_used_digits, index + 1)
#         # Check no repeats in positions
#         can_use = True
#         for pos, ch_digit in enumerate(number_str):
#             if ch_digit in position_used_digits[pos]:
#                 can_use = False
#                 break
#         if can_use:
#             selected_numbers.append((number_str, multiple))
#             used_digits.update(digits_in_number)
#             for pos, ch_digit in enumerate(number_str):
#                 position_used_digits[pos].add(ch_digit)
#             # Proceed to next
#             result = backtrack(selected_numbers, used_digits, position_used_digits, index + 1)
#             if result:
#                 return result
#             # Backtrack
#             selected_numbers.pop()
#             used_digits.difference_update(digits_in_number)
#             for pos, ch_digit in enumerate(number_str):
#                 position_used_digits[pos].remove(ch_digit)
#         # Try next number
#         return backtrack(selected_numbers, used_digits, position_used_digits, index + 1)
#     used_digits = set()
#     position_used_digits = [set() for _ in range(positions)]
#     return backtrack([], used_digits, position_used_digits, 0)

# # Run the function
# if __name__ == "__main__":
#     possible_gcds = find_gcd_candidates(100)

def print_not_divisible_by_2_or_5(start, end):
    for num in range(start, end + 1):
        if num % 2 != 0 and num % 5 != 0:
            print(num)

# Example usage
print_not_divisible_by_2_or_5(1, 1000)