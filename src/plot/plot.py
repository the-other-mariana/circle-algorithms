import pandas as pd
import matplotlib.pyplot as plt

# Replace 'your_file.csv' with the path to your CSV file
file_path = '../measures.csv'

# Read the CSV file into a DataFrame
df = pd.read_csv(file_path)
print(df.keys())

# Plotting
plt.figure(figsize=(10, 6))

# Iterate over unique 'calls' values and plot a line for each
for calls in df['calls'].unique():
    subset = df[(df['calls'] == calls) & (df['algorithm_id'] != 6)]
    plt.plot(subset['algorithm_id'], subset['time(ms)'], label=f'{calls} calls')

plt.title('Algorithm Execution Time')
plt.xlabel('Algorithm ID')
plt.ylabel('Time (ms)')
plt.legend()
plt.grid(True)
plt.xticks(df['algorithm_id'].unique())
plt.savefig("../plot2.png")
plt.show()