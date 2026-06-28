#include "fibonacci.h"

unsigned long long get_fibonacci(const unsigned index) noexcept
{
    if(index <= 1U)
    {
        return index;
    }

    unsigned long long prev = 0ULL;
    unsigned long long cur = 1ULL;

    for(unsigned i = 2U; i <= index; ++i)
    {
        unsigned long long next = prev + cur;
        prev = cur;
        cur = next;
    }

    return cur;
}
