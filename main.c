#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define SAMPLE_RATE_HZ 5
#define NS_PER_SEC 1000000000ULL
#define NS_PER_MS 1000000.0

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <output_csv_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "w");
    if (!fp) {
        perror("Failed to open output file");
        return 1;
    }

    // Write CSV header
    fprintf(fp, "clock_realtime_ns,clock_monotonic_ns,clock_monotonic_raw_ns\n");

    while (1) {
        // Get timestamps as close together as possible
        struct timespec ts_realtime, ts_mono, ts_mono_raw;

        if (clock_gettime(CLOCK_REALTIME, &ts_realtime) != 0) {
            perror("clock_gettime CLOCK_REALTIME failed");
            break;
        }
        if (clock_gettime(CLOCK_MONOTONIC, &ts_mono) != 0) {
            perror("clock_gettime CLOCK_MONOTONIC failed");
            break;
        }
        if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts_mono_raw) != 0) {
            perror("clock_gettime CLOCK_MONOTONIC_RAW failed");
            break;
        }

        // Convert to nanoseconds
        int64_t realtime_ns = (int64_t)ts_realtime.tv_sec * NS_PER_SEC + (int64_t)ts_realtime.tv_nsec;
        int64_t mono_ns = (int64_t)ts_mono.tv_sec * NS_PER_SEC + (int64_t)ts_mono.tv_nsec;
        int64_t mono_raw_ns = (int64_t)ts_mono_raw.tv_sec * NS_PER_SEC + (int64_t)ts_mono_raw.tv_nsec;

        // Calculate difference in milliseconds
        int64_t diff_ns = mono_ns - mono_raw_ns;
        double diff_ms = (double)diff_ns / NS_PER_MS;

        // Write to CSV
        fprintf(fp, "%llu,%llu,%llu\n", 
                (unsigned long long)realtime_ns,
                (unsigned long long)mono_ns, 
                (unsigned long long)mono_raw_ns);
        fflush(fp);

        // Print the difference
        printf("Difference (monotonic - monotonic_raw): %7.3f ms\n", diff_ms);
        fflush(stdout);

        // Sleep until next sample
        usleep(NS_PER_SEC / SAMPLE_RATE_HZ / 1000);
    }

    fclose(fp);
    return 0;
} 