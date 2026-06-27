#include <iostream>
#include "fibonacci.h"

int main()
{
    constexpr unsigned COUNT = 16u;

    std::cout << "Fibonacci sequence (first " << COUNT << " numbers):\n";
    for (unsigned i = 0u; i < COUNT; ++i)
    {
        std::cout << "    F(" << i << ") = " << get_fibonacci(i) << '\n';
    }

    return 0;
}
