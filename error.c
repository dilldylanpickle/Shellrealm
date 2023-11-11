#include <stdio.h>

int is_valid_ip(const char *ip) {
    int num, dots = 0;
    const char *ptr = ip;

    if (ip == NULL) {
        return 0;
    }

    while (*ptr) {
        if (*ptr == '.') {
            if (dots == 3) {
                return 0;
            }
            dots++;
            ptr++;
            continue;
        }

        if (*ptr < '0' || *ptr > '9') {
            return 0;
        }

        num = 0;
        while (*ptr >= '0' && *ptr <= '9') {
            num = num * 10 + (*ptr - '0');
            ptr++;
        }

        if (num < 0 || num > 255) {
            return 0;
        }

        if (*ptr != '.' && *ptr != '\0') {
            return 0;
        }
    }

    return dots == 3 ? 1 : 0;
}
