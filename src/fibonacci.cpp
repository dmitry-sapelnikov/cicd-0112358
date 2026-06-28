#include "fibonacci.h"

uint64_t get_fibonacci(const unsigned index) noexcept
{
    if(index <= 1U)
    {
        return index;
    }

    uint64_t prev = 0ULL;
    uint64_t cur = 1ULL;

    for(unsigned i = 2U; i <= index; ++i)
    {
        uint64_t next = prev + cur;
        prev = cur;
        cur = next;
    }

    return cur;
}
