import matplotlib.pyplot as plt
import numpy as np
import matplotlib.colors as mcolors
import random

def generate_random_colors(num_colors):
    # Generate random colors
    colors = []
    for _ in range(num_colors):
        colors.append((random.random(), random.random(), random.random()))
    return colors

def save_grid(grid, filename):
    # Get unique letters in the grid
    unique_letters = set(''.join(grid))
    num_colors = len(unique_letters)
    
    # Generate random colors for each letter
    colors = generate_random_colors(num_colors)
    cmap = mcolors.ListedColormap(colors)
    bounds = [ord(letter) for letter in sorted(unique_letters)]
    norm = mcolors.BoundaryNorm(bounds, cmap.N)
    
    # Reverse the order of rows in the grid
    grid = np.flip(grid, axis=0)
    
    # Create figure and axis
    fig, ax = plt.subplots()
    
    # Plot each cell with respective color
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            color_index = ord(grid[i][j])
            ax.add_patch(plt.Rectangle((j, i), 1, 1, fill=True, color=cmap(norm(color_index))))
    
    ax.set_xlim(0, len(grid[0]))
    ax.set_ylim(0, len(grid))
    ax.set_aspect('equal', adjustable='box')
    ax.axis('off')  # Turn off axis
    
    # Save the plot to file
    plt.savefig(filename, bbox_inches='tight', pad_inches=0)
    plt.close()

grid = np.array([
    "AAABBBCCDDD",
    "AEEEBBCDDDF",
    "AEEBBBCDDDF",
    "AEEBBGGDFFF",
    "AEBBDDGDFIF",
    "ADDDDDDDIIJ",
    "KDDDDLLDIII",
    "KKMDMLLDDID",
    "KKMMMLLDDDD",
    "KMMKKKLDDDN",
    "KKKKKLLLDDN"
])

save_grid(grid, "grid.png")