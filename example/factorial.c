#include <stdint.h>

uint16_t factorial(uint16_t f)
{
    if (f >= 1) {
        return f * factorial(f-1);
    } else {
        return 1;
    }
}