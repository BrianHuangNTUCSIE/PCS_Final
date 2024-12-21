import matplotlib.pyplot as plt
import numpy as np

# File names
theoretical_files = ["100m_theoretical", "200m_theoretical", "500m_theoretical", "1000m_theoretical"]
experimental_files = ["100m_experimental", "200m_experimental", "500m_experimental", "1000m_experimental"]

# Function to read data from a file
def read_data(file_name):
    with open(file_name, 'r') as file:
        return float(file.read().strip())

# Initialize lists for theoretical, experimental values, and error rates
theoretical_values = []
experimental_values = []
error_rates = []

# Read data from all files
for t_file, e_file in zip(theoretical_files, experimental_files):
    theoretical_value = read_data(t_file)
    experimental_value = read_data(e_file)
    error_rate = abs(theoretical_value - experimental_value) / theoretical_value * 100  # Percentage error
    
    theoretical_values.append(theoretical_value)
    experimental_values.append(experimental_value)
    error_rates.append(error_rate)

# Data for the table
labels = ['100m', '200m', '500m', '1000m']
theoretical_values = np.array(theoretical_values)
experimental_values = np.array(experimental_values)
error_rates = np.array(error_rates)

# Create a figure and axis
fig, ax = plt.subplots(figsize=(10, 2))

# Create a table
table_data = np.column_stack((theoretical_values, experimental_values, error_rates))
columns = ['Theoretical', 'Experimental', 'Error Rate (%)']
ax.axis('tight')
ax.axis('off')

# Plot table
table = ax.table(cellText=table_data, rowLabels=labels, colLabels=columns, loc='center', cellLoc='center')

# Adjust layout to remove unnecessary margins
plt.tight_layout(pad=0.1)

# Save the result as "result.png" with high resolution
plt.savefig("result.png", dpi=300)

# Show the plot in a window
plt.show()
