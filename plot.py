import matplotlib.pyplot as plt
import numpy as np

# Step 1: Initialize subplots
fig, axes = plt.subplots(1, 2, figsize=(16, 6))  # Two plots side by side

# File groups
theoretical_files = ["100m_theoretical", "200m_theoretical", "500m_theoretical", "1000m_theoretical"]
experimental_files = ["100m_experimental", "200m_experimental", "500m_experimental", "1000m_experimental"]

# Function to plot data
def plot_data(ax, data_files, title):
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
        ax.plot(x_values, y_values, marker='o', linestyle='-', label=f'{file_name}')
    
    # Customize the plot
    ax.set_title(title, fontsize=14)
    ax.set_xlabel("Distance (m)", fontsize=12)
    ax.set_ylabel("Connectivity", fontsize=12)
    ax.legend()
    ax.grid(True, linestyle='--', alpha=0.7)

    # Set the x-axis and y-axis ticks
    x_ticks = np.arange(min(x_values), max(x_values) + 1, 1000)  # Tick difference of 1000
    y_ticks = np.arange(0, max(y_values) + 0.01, 0.1)  # Force y-axis to start at 0
    ax.set_xticks(x_ticks)
    ax.set_yticks(y_ticks)

    # Set y-axis limits explicitly
    ax.set_ylim(0, max(y_values) + 0.1)

# Plot theoretical data on the left subplot
plot_data(axes[0], theoretical_files, "Theoretical Measurements")

# Plot experimental data on the right subplot
plot_data(axes[1], experimental_files, "Experimental Measurements")

# Step 2: Adjust layout and save/show the plot
plt.tight_layout()
plt.savefig("result.png")  # Save to a file
plt.show()  # Display the plot
