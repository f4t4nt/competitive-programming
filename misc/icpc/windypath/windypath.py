import matplotlib.pyplot as plt

# Function to read input data
def read_input():
    # Read number of coordinates
    n = int(input("Enter the number of coordinates: "))

    # Read coordinates
    coordinates = []
    print("Enter the coordinates (x y):")
    for _ in range(n):
        x, y = map(int, input().split())
        coordinates.append((x, y))
    
    return coordinates

# Function to determine turn direction
def get_turn_direction(p1, p2, p3):
    # Vector cross-product to determine orientation
    turn = (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p2[1] - p1[1]) * (p3[0] - p1[0])
    if turn > 0:
        return 'L'  # Left turn
    elif turn < 0:
        return 'R'  # Right turn
    else:
        return 'S'  # Straight (if needed)

# Main function to plot the path and generate turn sequence
def plot_path(coordinates, visit_order):
    # Organize coordinates in visit order
    ordered_coords = [coordinates[i - 1] for i in visit_order]

    # Determine turn directions
    turns = []
    for i in range(1, len(ordered_coords) - 1):
        turn = get_turn_direction(ordered_coords[i - 1], ordered_coords[i], ordered_coords[i + 1])
        turns.append(turn)

    # Plot the path
    plt.figure(figsize=(10, 10))
    for i in range(len(ordered_coords) - 1):
        start = ordered_coords[i]
        end = ordered_coords[i + 1]
        
        if i == 0:
            color = 'black'  # First segment
        elif turns[i - 1] == 'L':
            color = 'red'    # Left turn
        elif turns[i - 1] == 'R':
            color = 'blue'   # Right turn
        else:
            color = 'black'  # Straight segment (optional)

        plt.plot([start[0], end[0]], [start[1], end[1]], color=color, linewidth=2)

    # Mark starting and ending points
    plt.scatter(ordered_coords[0][0], ordered_coords[0][1], color='green', label='Start', s=50)
    plt.scatter(ordered_coords[-1][0], ordered_coords[-1][1], color='purple', label='End', s=50)

    # Save plot without showing it
    plt.legend()
    plt.savefig('./tmp.png')
    plt.close()

    # Print turn sequence
    turn_sequence = ''.join(turns)
    print("Turn sequence:", turn_sequence)

# Run the script
coordinates = read_input()

while True:
    try:
        print("Enter the visit order (or type 'exit' to quit):")
        visit_order_input = input().strip()
        if visit_order_input.lower() == 'exit':
            print("Exiting program.")
            break
        visit_order = list(map(int, visit_order_input.split()))

        # Check if visit order matches the number of coordinates
        if len(visit_order) != len(coordinates):
            print(f"Error: Visit order length ({len(visit_order)}) does not match number of coordinates ({len(coordinates)}). Please try again.")
            continue

        plot_path(coordinates, visit_order)
    except ValueError:
        print("Invalid input. Please enter a sequence of numbers separated by spaces.")
