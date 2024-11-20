import matplotlib.pyplot as plt
import numpy as np

# Step 1: Initialize plot
plt.figure(figsize=(10, 6))

# List of data files to read
data_files = ["100m", "200m", "500m", "1000m"]

# Loop over each file and plot the data
for file_name in data_files:
    x_values = []
    y_values = []
    
    # Read data from the current file
    with open(file_name, "r") as file:
        for line in file:
            x, y = map(float, line.strip().split())
            x_values.append(x)
            y_values.append(y)

    # Plot the data for the current file
    plt.plot(x_values, y_values, marker='o', linestyle='-', label=f'{file_name}')

# Step 2: Customize the plot
plt.title("measure 6", fontsize=14)
plt.xlabel("distance (m)", fontsize=12)
plt.ylabel("connectivity", fontsize=12)
plt.legend()

# Set the x-axis and y-axis ticks
x_ticks = np.arange(min(x_values), max(x_values) + 1, 1000)  # Tick difference of 1000
y_ticks = np.arange(0, max(y_values) + 0.01, 0.1)  # Force y-axis to start at 0
plt.xticks(x_ticks)
plt.yticks(y_ticks)

# Set y-axis limits explicitly
plt.ylim(0, max(y_values) + 0.1)  # Ensure y-axis starts at 0

# Add grid lines for better visibility
plt.grid(True, linestyle='--', alpha=0.7)

# Step 3: Show or save the plot
plt.savefig("result.png")  # Save to a file
plt.show()  # Display the plot
