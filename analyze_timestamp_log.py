#!/usr/bin/env -S uv run

# /// script
# dependencies = [
#     "pandas>=2.0.0",
#     "matplotlib>=3.7.0"
# ]
# ///

import pandas as pd
import matplotlib.pyplot as plt
import sys

def plot_clock_differences(csv_file):
    # Read the CSV file
    df = pd.read_csv(csv_file)
    
    # Convert nanoseconds to seconds for better readability
    df['clock_realtime_s'] = df['clock_realtime_ns'] / 1e9
    df['clock_monotonic_s'] = df['clock_monotonic_ns'] / 1e9
    df['clock_monotonic_raw_s'] = df['clock_monotonic_raw_ns'] / 1e9
    
    # Calculate the difference between MONOTONIC and MONOTONIC_RAW
    df['difference_ms'] = (df['clock_monotonic_ns'] - df['clock_monotonic_raw_ns']) / 1e6
    
    # Create the plot
    plt.figure(figsize=(12, 6))
    plt.plot(df['clock_realtime_s'], df['difference_ms'], label='MONOTONIC - MONOTONIC_RAW')
    
    # Customize the plot
    plt.xlabel('Real Time (seconds)')
    plt.ylabel('Difference (milliseconds)')
    plt.title('Difference between CLOCK_MONOTONIC and CLOCK_MONOTONIC_RAW')
    plt.grid(True)
    plt.legend()
    
    # Show the plot
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: ./analyze_timestamp_log.py <csv_file>")
        sys.exit(1)
    
    plot_clock_differences(sys.argv[1])
