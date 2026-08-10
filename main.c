#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    while (1) {
        printf("\033[2J\033[H");

        // ----- read cpu stuff
        FILE *fp = fopen("/proc/stat", "r");
        if (fp == NULL) {
            printf("couldn't open /proc/stat\n");
            return 1;
        }

        char cpu_label[10];
        long user, nice, system, idle;
        fscanf(fp, "%s %ld %ld %ld %ld", cpu_label, &user, &nice, &system, &idle);
        fclose(fp);

        long total = user + nice + system + idle;
        long used = user + nice + system;
        double cpu_percent = (double)used / (double)total * 100.0;

        printf("=== hyprstat (C version) ===\n\n");
        printf("CPU usage (rough): %.1f%%\n", cpu_percent);

        // read memory
        FILE *mem = fopen("/proc/meminfo", "r");
        if (mem == NULL) {
            printf("couldn't open /proc/meminfo\n");
            return 1;
        }

        long mem_total = 0, mem_available = 0;
        char line[256];
        while (fgets(line, sizeof(line), mem)) {
            if (sscanf(line, "MemTotal: %ld kB", &mem_total) == 1) continue;
            if (sscanf(line, "MemAvailable: %ld kB", &mem_available) == 1) continue;
        }
        fclose(mem);

        double mem_percent = (double)(mem_total - mem_available) / (double)mem_total * 100.0;
        printf("Memory usage: %.1f%%\n", mem_percent);

        printf("\n(press Ctrl+C to quit)\n");

        sleep(1);
    }

    return 0;
}