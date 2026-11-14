#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

#if !defined(__aarch64__) || !defined(__sun)
#error This smoke test must compile natively for aarch64 illumos
#endif

int main(void)
{
    struct utsname info;
    assert(uname(&info) == 0);
    assert(strcmp(info.sysname, "SunOS") == 0);
    assert(sizeof(void *) == 8);
    uint64_t *values = calloc(1024, sizeof(*values));
    assert(values != NULL);
    uint64_t sum = 0;
    for (size_t i = 0; i < 1024; ++i) {
        values[i] = i * i;
        sum += values[i];
    }
    assert(sum == UINT64_C(357389824));
    free(values);
    puts("Native aarch64 illumos compile and execution passed");
    return 0;
}
