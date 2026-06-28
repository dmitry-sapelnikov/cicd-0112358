#pragma once

#include <cstdint>

/**
    Returns the i-th Fibonacci number (0-indexed)
    \param index The index of the Fibonacci number to return
    \return The i-th Fibonacci number
    \note Returns an overflowed result for index >= 94
*/
[[nodiscard]] uint64_t get_fibonacci(unsigned index) noexcept;
