#include <count_time.h>

long pinpoint_time() {
    struct timespec *time = (struct timespec *) malloc(sizeof(struct timespec));
    clock_gettime(CLOCK_REALTIME, time);
    long mt = 0;
    for (int i = 0; i < AVG; i++) {
        mt += (long) time->tv_sec * MS_FROM_SEC + (long) time->tv_nsec / MS_FROM_NS;
    }
    free(time);
    return mt / AVG;
}
