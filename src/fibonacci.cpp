#include "fibonacci.h"

[[nodiscard]]
unsigned long long get_fibonacci(const unsigned index) noexcept
{
    if (index == 0U)
    {
        return 0ULL;
    }

    if (index == 1U)
    {
        return 1ULL;
    }

    unsigned long long prev = 0ULL;
    unsigned long long cur = 1ULL;

    for (unsigned i = 2U; i <= index; ++i)
    {
        unsigned long long next = prev + cur;
        prev = cur;
        cur = next;
    }

    return cur;
}
