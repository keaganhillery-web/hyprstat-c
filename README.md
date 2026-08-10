# hyprstat-c

A terminal system dashboard written in C, as a learning project, no external libraries, reads directly from `/proc`.

## Build & run

```bash
gcc main.c -o hyprstat_c
./hyprstat_c
```

## Status

- CPU and memory usage, refreshed once a second
- Known bug: CPU percentage is currently a total-since-boot average (single snapshot of `/proc/stat`), not a live delta between two reads — next thing to fix
