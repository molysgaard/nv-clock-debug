# nv-clock-debug

# Cloning

```
git clone https://github.com/molysgaard/nv-clock-debug.git
cd nv-clock-debug
```

# Building

```
mkdir build
cd build
cmake ..
make
```

# Running

Run this and observe if `monotonic` drifts away from `monotonic_raw`.

```
./nv-clock-debug timestamps.csv
```


# Analyze the drift using python:

To easily run the python script, you will need to install UV: https://docs.astral.sh/uv/getting-started/installation/

You can plot the drift using this command:
```
./analyze_timestamp_log.py timestamps.csv
```
