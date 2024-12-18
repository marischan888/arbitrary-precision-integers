#include <assert.h>

#include "bigint.hpp"
#include <iostream>

void test_bigint_addition() {
    // int64_t
    bigint a(-100);
    bigint b(25);
    bigint result = a + b;
    assert(result == bigint(-75));
}

int main() {
    test_bigint_addition();
    return 0;
}

