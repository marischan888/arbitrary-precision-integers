#include <cassert>

#include "bigint.hpp"
#include <iostream>

void test_bigint_constructors() {
    std::cout << "Running bigint constructor tests...\n";

    // Test 1: Default constructor
    const bigint a;
    assert(a == bigint());
    std::cout << "Test 1 Passed: Default constructor creates bigint(0) = " << a << "\n";

    // Test 2: Constructor with int64_t positive value
    bigint b(12345);
    assert(b == bigint("12345"));
    std::cout << "Test 2 Passed: bigint(12345) = " << b << "\n";

    // Test 3: Constructor with int64_t negative value
    bigint c(-12345);
    assert(c == bigint("-12345"));
    std::cout << "Test 3 Passed: bigint(-12345) = " << c << "\n";

    // Test 4: Constructor with int64_t zero
    bigint d(0);
    assert(d == bigint(0));
    std::cout << "Test 4 Passed: bigint(0) = " << d << "\n";

    // Test 5: Constructor with string positive value
    bigint e("9876543210");
    assert(e == bigint("9876543210"));
    std::cout << "Test 5 Passed: bigint(\"9876543210\") = " << e << "\n";

    // Test 6: Constructor with string negative value
    bigint f("-9876543210");
    assert(f == bigint("-9876543210"));
    std::cout << "Test 6 Passed: bigint(\"-9876543210\") = " << f << "\n";

    // Test 7: Constructor with string zero
    bigint g("0");
    assert(g == bigint(0));
    std::cout << "Test 7 Passed: bigint(\"0\") = " << g << "\n";

    // Test 8: Constructor with string containing leading zeros
    bigint h("000012345");
    assert(h == bigint("12345"));
    std::cout << "Test 8 Passed: bigint(\"000012345\") = " << h << "\n";

    // Test 9: Constructor with empty string (invalid)
    try {
        bigint i("");
        std::cout << "Test 9 Failed: Constructor with empty string did not throw exception\n";
    } catch (const std::invalid_argument& ex) {
        std::cout << "Test 9 Passed: Constructor with empty string threw exception: " << ex.what() << "\n";
    }

    // Test 10: Constructor with invalid string (non-digit characters)
    try {
        bigint j("123abc456");
        std::cout << "Test 10 Failed: Constructor with invalid string did not throw exception\n";
    } catch (const std::invalid_argument& ex) {
        std::cout << "Test 10 Passed: Constructor with invalid string threw exception: " << ex.what() << "\n";
    }

    // Test 11: Constructor with a very large number
    bigint k("100000000000000000000");
    assert(k == bigint("100000000000000000000"));
    std::cout << "Test 11 Passed: bigint(\"100000000000000000000\") = " << k << "\n";

    // Test 12: Constructor with negative very large number
    bigint l("-100000000000000000000");
    assert(l == bigint("-100000000000000000000"));
    std::cout << "Test 12 Passed: bigint(\"-100000000000000000000\") = " << l << "\n";

    std::cout << "All bigint constructor tests passed successfully!\n";
}

void test_bigint_addition() {
    std::cout << "Running bigint addition tests...\n";

    // Test 1: Addition of two positive numbers
    bigint a(123);
    bigint b(456);
    bigint result = a + b;
    assert(result == bigint(579));
    cout << "Test 1 Passed: 123 + 456 = " << result << "\n";

    // Test 2: Addition of two negative numbers
    a = bigint(-123);
    b = bigint(-456);
    result = a + b;
    assert(result == bigint(-579));
    cout << "Test 2 Passed: -123 + -456 = " << result << "\n";

    // Test 3: Positive + Negative (Result Positive)
    a = bigint(100);
    b = bigint(-25);
    result = a + b;
    assert(result == bigint(75));
    cout << "Test 3 Passed: 100 + (-25) = " << result << "\n";

    // Test 4: Positive + Negative (Result Negative)
    a = bigint(25);
    b = bigint(-100);
    result = a + b;
    assert(result == bigint(-75));
    cout << "Test 4 Passed: 25 + (-100) = " << result << "\n";

    // Test 5: Negative + Positive (Result Positive)
    a = bigint(-25);
    b = bigint(100);
    result = a + b;
    assert(result == bigint(75));
    cout << "Test 5 Passed: -25 + 100 = " << result << "\n";

    // Test 6: Negative + Positive (Result Negative)
    a = bigint(-100);
    b = bigint(25);
    result = a + b;
    assert(result == bigint(-75));
    cout << "Test 6 Passed: -100 + 25 = " << result << "\n";

    // Test 7: Addition with zero
    a = bigint(123);
    b = bigint(0);
    result = a + b;
    assert(result == bigint(123));
    cout << "Test 7 Passed: 123 + 0 = " << result << "\n";

    // Test 8: Addition with zero
    a = bigint(0);
    b = bigint(-123);
    result = a + b;
    assert(result == bigint(-123));
    cout << "Test 8 Passed: 0 + (-123) = " << result << "\n";

    // Test 9: Both numbers are zero
    a = bigint(0);
    b = bigint(0);
    result = a + b;
    assert(result == bigint(0));
    cout << "Test 9 Passed: 0 + 0 = " << result << "\n";

    // Test 10: Addition causing carry propagation
    a = bigint(999);
    b = bigint(1);
    result = a + b;
    assert(result == bigint(1000));
    cout << "Test 10 Passed: 999 + 1 = " << result << "\n";

    // Test 11: Handle -0
    a = bigint(0);
    b = bigint(-0);
    result = a + b;
    assert(result == bigint(0));
    cout << "Test 11 Passed: 0 + -0 = " << result << "\n";

    cout << "All addition tests passed successfully!\n";
}

void test_bigint_string_and_addition() {
    cout << "Running tests for bigint(string) constructor and addition...\n";

    // Test 1: Valid positive number
    bigint a("12345");
    bigint b("67890");
    bigint result = a + b;
    assert(result == bigint("80235"));
    cout << R"(Test 1 Passed: "12345" + "67890" = )" << result << "\n";

    // Test 2: Valid negative number
    a = bigint("-12345");
    b = bigint("-67890");
    result = a + b;
    assert(result == bigint("-80235"));
    cout << R"(Test 2 Passed: "-12345" + "-67890" = )" << result << "\n";

    // Test 3: Positive + Negative (Result Positive)
    a = bigint("1000");
    b = bigint("-999");
    result = a + b;
    assert(result == bigint("1"));
    cout << R"(Test 3 Passed: "1000" + "-999" = )" << result << "\n";

    // Test 4: Positive + Negative (Result Negative)
    a = bigint("1000");
    b = bigint("-2000");
    result = a + b;
    assert(result == bigint("-1000"));
    cout << R"(Test 4 Passed: "1000" + "-2000" = )" << result << "\n";

    // Test 5: String with leading zeros
    a = bigint("00012345");
    b = bigint("000067890");
    result = a + b;
    assert(result == bigint("80235"));
    cout << R"(Test 5 Passed: "00012345" + "000067890" = )" << result << "\n";

    // Test 6: One number is zero
    a = bigint("0");
    b = bigint("-12345");
    result = a + b;
    assert(result == bigint("-12345"));
    cout << R"(Test 6 Passed: "0" + "-12345" = )" << result << "\n";

    // Test 7: Both numbers are zero
    a = bigint("0");
    b = bigint("0");
    result = a + b;
    assert(result == bigint("0"));
    cout << R"(Test 7 Passed: "0" + "0" = )" << result << "\n";

    // Test 8: Empty string (invalid input)
    try {
        a = bigint("");
        cout << "Test 8 Failed: Empty string did not throw an exception\n";
    } catch (const invalid_argument& e) {
        cout << "Test 8 Passed: Empty string threw exception: " << e.what() << "\n";
    }

    // Test 9: String with invalid characters
    try {
        a = bigint("123a45");
        cout << "Test 9 Failed: Invalid string did not throw an exception\n";
    } catch (const std::invalid_argument& e) {
        cout << "Test 9 Passed: Invalid string threw exception: " << e.what() << "\n";
    }

    // Test 10: Both numbers has same size with different sign
    a = bigint("-100");
    b = bigint("100");
    result = a + b;
    assert(result == bigint("0"));
    cout << R"(Test 10 Passed: "-100" + "100" = )" << result << "\n";

    // Test 11: Both numbers has same size with different sign
    a = bigint("100");
    b = bigint("-100");
    result = a + b;
    assert(result == bigint("0"));
    cout << R"(Test 11 Passed: "100" + "-100" = )" << result << "\n";

    // Test 12: Both numbers has same size with different sign and leading zero
    a = bigint("100");
    b = bigint("-00100");
    result = a + b;
    assert(result == bigint("0"));
    cout << R"(Test 12 Passed: "100" + "-00100" = )" << result << "\n";

    cout << "All tests for bigint(string) constructor and addition passed successfully!\n";
}

void test_bigint_subtraction() {
    std::cout << "Running bigint(int64_t) subtraction tests...\n";

    // Test 1: Positive - Positive (result positive)
    bigint a(100);
    bigint b(25);
    bigint result = a - b;
    assert(result == bigint(75));
    std::cout << "Test 1 Passed: 100 - 25 = " << result << "\n";

    // Test 2: Positive - Positive (result negative)
    a = bigint(25);
    b = bigint(100);
    result = a - b;
    assert(result == bigint(-75));
    std::cout << "Test 2 Passed: 25 - 100 = " << result << "\n";

    // Test 3: Positive - Negative
    a = bigint(100);
    b = bigint(-25);
    result = a - b;
    assert(result == bigint(125));
    std::cout << "Test 3 Passed: 100 - (-25) = " << result << "\n";

    // Test 4: Negative - Positive
    a = bigint(-100);
    b = bigint(25);
    result = a - b;
    assert(result == bigint(-125));
    std::cout << "Test 4 Passed: -100 - 25 = " << result << "\n";

    // Test 5: Negative - Negative (result negative)
    a = bigint(-100);
    b = bigint(-25);
    result = a - b;
    assert(result == bigint(-75));
    std::cout << "Test 5 Passed: -100 - (-25) = " << result << "\n";

    // Test 6: Negative - Negative (result positive)
    a = bigint(-25);
    b = bigint(-100);
    result = a - b;
    assert(result == bigint(75));
    std::cout << "Test 6 Passed: -25 - (-100) = " << result << "\n";

    // Test 7: Zero - Positive
    a = bigint(0);
    b = bigint(25);
    result = a - b;
    assert(result == bigint(-25));
    std::cout << "Test 7 Passed: 0 - 25 = " << result << "\n";

    // Test 8: Zero - Negative
    a = bigint(0);
    b = bigint(-25);
    result = a - b;
    assert(result == bigint(25));
    std::cout << "Test 8 Passed: 0 - (-25) = " << result << "\n";

    // Test 9: Zero - Zero
    a = bigint(0);
    b = bigint(0);
    result = a - b;
    assert(result == bigint(0));
    std::cout << "Test 9 Passed: 0 - 0 = " << result << "\n";

    // Test 10: Large Positive - Small Positive
    a = bigint(1000000);
    b = bigint(1);
    result = a - b;
    assert(result == bigint(999999));
    std::cout << "Test 10 Passed: 1000000 - 1 = " << result << "\n";

    // Test 11: Small Positive - Large Positive
    a = bigint(1);
    b = bigint(1000000);
    result = a - b;
    assert(result == bigint(-999999));
    std::cout << "Test 11 Passed: 1 - 1000000 = " << result << "\n";

    // Test 12: Small Positive - Large Positive
    a = bigint(100);
    b = bigint(-100);
    result = a - b;
    assert(result == bigint(200));
    std::cout << "Test 12 Passed: 100 - (-100) = " << result << "\n";

    // Test 13: Small Positive - Large Positive
    a = bigint(-100);
    b = bigint(-100);
    result = a - b;
    assert(result == bigint(0));
    std::cout << "Test 13 Passed: - 100 - (-100) = " << result << "\n";
    std::cout << "All bigint(int64_t) subtraction tests passed successfully!\n";
}

void test_bigint_string_subtraction() {
    std::cout << "Running bigint subtraction tests...\n";

    // Test 1: Subtraction of two positive numbers (result positive)
    bigint a("000012345");
    bigint b("1234");
    bigint result = a - b;
    assert(result == bigint("11111"));
    std::cout << R"(Test 1 Passed: "12345" - "1234" = )" << result << "\n";

    // Test 2: Subtraction of two positive numbers (result negative)
    a = bigint("1234");
    b = bigint("12345");
    result = a - b;
    assert(result == bigint("-11111"));
    std::cout << R"(Test 2 Passed: "1234" - "12345" = )" << result << "\n";

    // Test 3: Subtraction with zero (positive - 0)
    a = bigint("12345");
    b = bigint("0");
    result = a - b;
    assert(result == bigint("12345"));
    std::cout << R"(Test 3 Passed: "12345" - "0" = )" << result << "\n";

    // Test 4: Subtraction with zero (negative - 0)
    a = bigint("-12345");
    b = bigint("0");
    result = a - b;
    assert(result == bigint("-12345"));
    std::cout << R"(Test 4 Passed: "-12345" - "0" = )" << result << "\n";

    // Test 5: Subtraction of zero from zero
    a = bigint("000000");
    b = bigint("0");
    result = a - b;
    assert(result == bigint("0"));
    std::cout << R"(Test 5 Passed: "0" - "0" = )" << result << "\n";

    // Test 6: Subtraction of two negative numbers (result negative)
    a = bigint("-12345");
    b = bigint("-123");
    result = a - b;
    assert(result == bigint("-12222"));
    std::cout << R"(Test 6 Passed: "-12345" - "-123" = )" << result << "\n";

    // Test 7: Subtraction of two negative numbers (result positive)
    a = bigint("-123");
    b = bigint("-12345");
    result = a - b;
    assert(result == bigint("12222"));
    std::cout << R"(Test 7 Passed: "-123" - "-12345" = )" << result << "\n";

    // Test 8: Subtraction with mixed signs (positive - negative)
    a = bigint("12345");
    b = bigint("-123");
    result = a - b;
    assert(result == bigint("12468"));
    std::cout << R"(Test 8 Passed: "12345" - "-123" = )" << result << "\n";

    // Test 9: Subtraction with mixed signs (negative - positive)
    a = bigint("-123");
    b = bigint("123");
    result = a - b;
    assert(result == bigint("-246"));
    std::cout << R"(Test 9 Passed: "-123" - "123" = )" << result << "\n";

    // Test 10: Large number subtraction (no carry)
    a = bigint("1000000");
    b = bigint("1");
    result = a - b;
    assert(result == bigint("999999"));
    std::cout << R"(Test 10 Passed: "1000000" - "1" = )" << result << "\n";

    // Test 11: Large number subtraction with carry
    a = bigint("1000");
    b = bigint("1");
    result = a - b;
    assert(result == bigint("999"));
    std::cout << R"(Test 11 Passed: "1000" - "1" = )" << result << "\n";

    std::cout << "All subtraction tests passed successfully!\n";
}

void test_bigint_comparisons() {
    std::cout << "Running bigint comparison operator tests...\n";

    // Test 1: Equality operator (==)
    bigint a(100);
    bigint b("100");
    assert(a == b);
    std::cout << "Test 1 Passed: bigint(100) == bigint(\"100\")\n";

    // Test 2: Inequality operator (!=)
    a = bigint(100);
    b = bigint("-100");
    assert(a != b);
    std::cout << "Test 2 Passed: bigint(100) != bigint(\"-100\")\n";

    // Test 3: Less-than operator (<)
    a = bigint(50);
    b = bigint(100);
    assert(a < b);
    std::cout << "Test 3 Passed: bigint(50) < bigint(100)\n";

    // Test 4: Greater-than operator (>)
    a = bigint(150);
    b = bigint(100);
    assert(a > b);
    std::cout << "Test 4 Passed: bigint(150) > bigint(100)\n";

    // Test 5: Less-than-or-equal-to operator (<=)
    a = bigint(100);
    b = bigint("100");
    assert(a <= b);
    a = bigint(50);
    assert(a <= b);
    std::cout << "Test 5 Passed: bigint(100) <= bigint(\"100\") and bigint(50) <= bigint(\"100\")\n";

    // Test 6: Greater-than-or-equal-to operator (>=)
    a = bigint(100);
    b = bigint(100);
    assert(a >= b);
    a = bigint(150);
    assert(a >= b);
    std::cout << "Test 6 Passed: bigint(100) >= bigint(100) and bigint(150) >= bigint(100)\n";

    // Test 7: Mixed sign comparison
    a = bigint(-50);
    b = bigint(50);
    assert(a < b);
    assert(b > a);
    std::cout << "Test 7 Passed: bigint(-50) < bigint(50) and bigint(50) > bigint(-50)\n";

    // Test 8: Comparison with zero
    a = bigint(0);
    b = bigint("-0");
    assert(a == b);
    b = bigint(-100);
    assert(a > b);
    std::cout << "Test 8 Passed: bigint(0) == bigint(\"-0\") and bigint(0) > bigint(\"-100\")\n";

    // Test 9: Large number comparison
    a = bigint("123456789012345678901234567890");
    b = bigint("123456789012345678901234567891");
    assert(a < b);
    assert(b > a);
    std::cout << "Test 9 Passed: bigint(\"123456789012345678901234567890\") < bigint(\"123456789012345678901234567891\")\n";

    // Test 10: Leading zeros
    a = bigint("00123");
    b = bigint(123);
    assert(a == b);
    std::cout << "Test 10 Passed: bigint(\"00123\") == bigint(123)\n";

    std::cout << "All comparison operator tests passed successfully!\n";
}

void test_bigint_unary_negation() {
    std::cout << "Running bigint unary negation tests...\n";

    // Test 1: Negation of a positive number
    bigint a(12345);
    bigint result = -a;
    assert(result == bigint("-12345"));
    std::cout << "Test 1 Passed: -bigint(12345) = " << result << "\n";

    // Test 2: Negation of a negative number
    a = bigint(-12345);
    result = -a;
    assert(result == bigint("12345"));
    std::cout << "Test 2 Passed: -bigint(-12345) = " << result << "\n";

    // Test 3: Negation of zero
    a = bigint(0);
    result = -a;
    assert(result == bigint("0"));
    std::cout << "Test 3 Passed: -bigint(0) = " << result << "\n";

    // Test 4: Negation of large positive number
    a = bigint("98765432109876543210");
    result = -a;
    assert(result == bigint("-98765432109876543210"));
    std::cout << "Test 4 Passed: -bigint(\"98765432109876543210\") = " << result << "\n";

    // Test 5: Negation of large negative number
    a = bigint("-98765432109876543210");
    result = -a;
    assert(result == bigint("98765432109876543210"));
    std::cout << "Test 5 Passed: -bigint(\"-98765432109876543210\") = " << result << "\n";

    // Test 6: Negation of a number with leading zeros
    a = bigint("00012345");
    result = -a;
    assert(result == bigint("-12345"));
    std::cout << "Test 6 Passed: -bigint(\"00012345\") = " << result << "\n";

    // Test 7: Negation of a negative number with leading zeros
    a = bigint("-00012345");
    result = -a;
    assert(result == bigint("12345"));
    std::cout << "Test 7 Passed: -bigint(\"-00012345\") = " << result << "\n";

    // Test 8: Double negation of a positive number
    a = bigint(12345);
    result = -(-a);
    assert(result == bigint("12345"));
    std::cout << "Test 8 Passed: -(-bigint(12345)) = " << result << "\n";

    // Test 9: Double negation of a negative number
    a = bigint(-12345);
    result = -(-a);
    assert(result == bigint("-12345"));
    std::cout << "Test 9 Passed: -(-bigint(-12345)) = " << result << "\n";

    std::cout << "All unary negation tests passed successfully!\n";
}

void test_bigint_assignment_operators() {
    std::cout << "Running bigint assignment operator tests...\n";

    // Test 1: += with bigint(int)
    bigint a(100);
    bigint b(25);
    a += b;
    assert(a == bigint(125));
    std::cout << "Test 1 Passed: bigint(100) += bigint(25) = " << a << "\n";

    // Test 2: += with bigint(string)
    a = bigint("12345");
    b = bigint("54321");
    a += b;
    assert(a == bigint("66666"));
    std::cout << R"(Test 2 Passed: bigint("12345") += bigint("54321") = )" << a << "\n";

    // Test 3: += with default-constructed bigint()
    a = bigint();
    b = bigint(100);
    a += b;
    assert(a == bigint(100));
    std::cout << "Test 3 Passed: bigint() += bigint(100) = " << a << "\n";

    // Test 4: -= with bigint(int)
    a = bigint(200);
    b = bigint(50);
    a -= b;
    assert(a == bigint(150));
    std::cout << "Test 4 Passed: bigint(200) -= bigint(50) = " << a << "\n";

    // Test 5: -= with bigint(string)
    a = bigint("10000");
    b = bigint("1234");
    a -= b;
    assert(a == bigint("8766"));
    std::cout << R"(Test 5 Passed: bigint("10000") -= bigint("1234") = )" << a << "\n";

    // Test 6: -= with default-constructed bigint()
    a = bigint();
    b = bigint(12345);
    a -= b;
    assert(a == bigint("-12345"));
    std::cout << "Test 6 Passed: bigint() -= bigint(12345) = " << a << "\n";

    // Test 7: += with negative numbers
    a = bigint(-50);
    b = bigint(-25);
    a += b;
    assert(a == bigint(-75));
    std::cout << "Test 7 Passed: bigint(-50) += bigint(-25) = " << a << "\n";

    // Test 8: -= with negative numbers
    a = bigint(-50);
    b = bigint(-25);
    a -= b;
    assert(a == bigint(-25));
    std::cout << "Test 8 Passed: bigint(-50) -= bigint(-25) = " << a << "\n";

    // Test 9: += with zero
    a = bigint(0);
    b = bigint(12345);
    a += b;
    assert(a == bigint(12345));
    std::cout << "Test 9 Passed: bigint(0) += bigint(12345) = " << a << "\n";

    // Test 10: -= with zero
    a = bigint(12345);
    b = bigint(0);
    a -= b;
    assert(a == bigint(12345));
    std::cout << "Test 10 Passed: bigint(12345) -= bigint(0) = " << a << "\n";

    std::cout << "All bigint assignment operator tests passed successfully!\n";
}

void test_bigint_multiplication() {
    std::cout << "Running bigint multiplication tests...\n";

    // Test 1: Multiplication of two positive numbers
    bigint a(123);
    bigint b(456);
    bigint result = a * b;
    assert(result == bigint("56088"));
    std::cout << "Test 1 Passed: 123 * 456 = " << result << "\n";

    // Test 2: Multiplication of a positive and a negative number
    a = bigint(12);
    b = bigint(-4);
    result = a * b;
    assert(result == bigint("-48"));
    std::cout << "Test 2 Passed: 12 * -4 = " << result << "\n";

    // Test 3: Multiplication of two negative numbers
    a = bigint(-123);
    b = bigint(-456);
    result = a * b;
    assert(result == bigint("56088"));
    std::cout << "Test 3 Passed: -123 * -456 = " << result << "\n";

    // Test 4: Multiplication with zero
    a = bigint(12345);
    b = bigint(0);
    result = a * b;
    assert(result == bigint("0"));
    std::cout << "Test 4 Passed: 12345 * 0 = " << result << "\n";

    // Test 5: Multiplication of large numbers
    a = bigint("987654321");
    b = bigint("123456789");
    result = a * b;
    assert(result == bigint("121932631112635269"));
    std::cout << "Test 5 Passed: 987654321 * 123456789 = " << result << "\n";

    // Test 6: Compound multiplication assignment *= with positive numbers
    a = bigint(12);
    b = bigint(34);
    a *= b;
    assert(a == bigint("408"));
    std::cout << "Test 6 Passed: bigint(12) *= bigint(34) = " << a << "\n";

    // Test 7: Compound multiplication assignment *= with a negative number
    a = bigint(12);
    b = bigint(-34);
    a *= b;
    assert(a == bigint("-408"));
    std::cout << "Test 7 Passed: bigint(12) *= bigint(-34) = " << a << "\n";

    // Test 8: Compound multiplication assignment *= with zero
    a = bigint(12345);
    b = bigint(0);
    a *= b;
    assert(a == bigint("0"));
    std::cout << "Test 8 Passed: bigint(12345) *= bigint(0) = " << a << "\n";

    // Test 9: Multiplication with bigint(string)
    a = bigint("123456");
    b = bigint("654321");
    result = a * b;
    assert(result == bigint("80779853376"));
    std::cout << R"(Test 9 Passed: bigint("123456") * bigint("654321") = )" << result << "\n";

    // Test 10: Multiplication involving a default-constructed bigint()
    a = bigint();
    b = bigint(789);
    result = a * b;
    assert(result == bigint("0"));
    std::cout << "Test 10 Passed: bigint() * bigint(789) = " << result << "\n";

    std::cout << "All bigint multiplication tests passed successfully!\n";
}

void test_bigint_string_multiplication() {
    std::cout << "Running bigint(string) multiplication tests...\n";

    // Test 1: Multiplication of two positive string numbers
    bigint a("123");
    bigint b("456");
    bigint result = a * b;
    assert(result == bigint("56088"));
    std::cout << R"(Test 1 Passed: bigint("123") * bigint("456") = )" << result << "\n";

    // Test 2: Multiplication of a positive and a negative string number
    a = bigint("123");
    b = bigint("-456");
    result = a * b;
    assert(result == bigint("-56088"));
    std::cout << R"(Test 2 Passed: bigint("123") * bigint("-456") = )" << result << "\n";

    // Test 3: Multiplication of two negative string numbers
    a = bigint("-123");
    b = bigint("-456");
    result = a * b;
    assert(result == bigint("56088"));
    std::cout << R"(Test 3 Passed: bigint("-123") * bigint("-456") = )" << result << "\n";

    // Test 4: Multiplication involving zero
    a = bigint("12345");
    b = bigint("0");
    result = a * b;
    assert(result == bigint("0"));
    std::cout << R"(Test 4 Passed: bigint("12345") * bigint("0") = )" << result << "\n";

    // Test 5: Multiplication of large string numbers
    a = bigint("987654321");
    b = bigint("123456789");
    result = a * b;
    assert(result == bigint("121932631112635269"));
    std::cout << R"(Test 5 Passed: bigint("987654321") * bigint("123456789") = )" << result << "\n";

    // Test 6: Compound multiplication assignment *= with positive string numbers
    a = bigint("12");
    b = bigint("34");
    a *= b;
    assert(a == bigint("408"));
    std::cout << R"(Test 6 Passed: bigint("12") *= bigint("34") = )" << a << "\n";

    // Test 7: Compound multiplication assignment *= with a negative string number
    a = bigint("12");
    b = bigint("-34");
    a *= b;
    assert(a == bigint("-408"));
    std::cout << R"(Test 7 Passed: bigint("12") *= bigint("-34") = )" << a << "\n";

    // Test 8: Compound multiplication assignment *= with zero
    a = bigint("12345");
    b = bigint("0");
    a *= b;
    assert(a == bigint("0"));
    std::cout << R"(Test 8 Passed: bigint("12345") *= bigint("0") = )" << a << "\n";

    // Test 9: Multiplication of numbers with leading zeros
    a = bigint("00123");
    b = bigint("0456");
    result = a * b;
    assert(result == bigint("56088"));
    std::cout << R"(Test 9 Passed: bigint("00123") * bigint("0456") = )" << result << "\n";

    // Test 10: Multiplication involving default-constructed bigint()
    a = bigint();
    b = bigint("789");
    result = a * b;
    assert(result == bigint("0"));
    std::cout << "Test 10 Passed: bigint() * bigint(\"789\") = " << result << "\n";

    std::cout << "All bigint(string) multiplication tests passed successfully!\n";
}

void test_bigint_increment() {
    std::cout << "Running bigint increment tests...\n";

    // Test 1: Pre-increment with bigint(int)
    bigint a(123);
    bigint result = ++a;
    assert(a == bigint(124));
    assert(result == bigint(124));
    std::cout << "Test 1 Passed: ++bigint(123) = " << a << "\n";

    // Test 2: Post-increment with bigint(int)
    a = bigint(123);
    result = a++;
    assert(a == bigint(124));
    assert(result == bigint(123));
    std::cout << "Test 2 Passed: bigint(123)++ = " << result << ", after increment: " << a << "\n";

    // Test 3: Pre-increment with bigint(string)
    a = bigint("999");
    result = ++a;
    assert(a == bigint("1000"));
    assert(result == bigint("1000"));
    std::cout << "Test 3 Passed: ++bigint(\"999\") = " << a << "\n";

    // Test 4: Post-increment with bigint(string)
    a = bigint("999");
    result = a++;
    assert(a == bigint("1000"));
    assert(result == bigint("999"));
    std::cout << "Test 4 Passed: bigint(\"999\")++ = " << result << ", after increment: " << a << "\n";

    // Test 5: Pre-increment with a negative bigint
    a = bigint(-1);
    result = ++a;
    assert(a == bigint(0));
    assert(result == bigint(0));
    std::cout << "Test 5 Passed: ++bigint(-1) = " << a << "\n";

    // Test 6: Post-increment with a negative bigint
    a = bigint(-1);
    result = a++;
    assert(a == bigint(0));
    assert(result == bigint(-1));
    std::cout << "Test 6 Passed: bigint(-1)++ = " << result << ", after increment: " << a << "\n";

    // Test 7: Pre-increment with a default-constructed bigint
    a = bigint();
    result = ++a;
    assert(a == bigint(1));
    assert(result == bigint(1));
    std::cout << "Test 7 Passed: ++bigint() = " << a << "\n";

    // Test 8: Post-increment with a default-constructed bigint
    a = bigint();
    result = a++;
    assert(a == bigint(1));
    assert(result == bigint());
    std::cout << "Test 8 Passed: bigint()++ = " << result << ", after increment: " << a << "\n";

    // Test 9: Incrementing a large number
    a = bigint("999999999999");
    result = ++a;
    assert(a == bigint("1000000000000"));
    assert(result == bigint("1000000000000"));
    std::cout << "Test 9 Passed: ++bigint(\"999999999999\") = " << a << "\n";

    std::cout << "All bigint increment tests passed successfully!\n";
}

void test_bigint_decrement() {
    std::cout << "Running bigint decrement tests...\n";

    // Test 1: Pre-decrement with bigint(int)
    bigint a(123);
    bigint result = --a;
    assert(a == bigint(122));
    assert(result == bigint(122));
    std::cout << "Test 1 Passed: --bigint(123) = " << a << "\n";

    // Test 2: Post-decrement with bigint(int)
    a = bigint(123);
    result = a--;
    assert(a == bigint(122));
    assert(result == bigint(123));
    std::cout << "Test 2 Passed: bigint(123)-- = " << result << ", after decrement: " << a << "\n";

    // Test 3: Pre-decrement with bigint(string)
    a = bigint("1000");
    result = --a;
    assert(a == bigint("999"));
    assert(result == bigint("999"));
    std::cout << "Test 3 Passed: --bigint(\"1000\") = " << a << "\n";

    // Test 4: Post-decrement with bigint(string)
    a = bigint("1000");
    result = a--;
    assert(a == bigint("999"));
    assert(result == bigint("1000"));
    std::cout << "Test 4 Passed: bigint(\"1000\")-- = " << result << ", after decrement: " << a << "\n";

    // Test 5: Pre-decrement with a negative bigint
    a = bigint(-1);
    result = --a;
    assert(a == bigint(-2));
    assert(result == bigint(-2));
    std::cout << "Test 5 Passed: --bigint(-1) = " << a << "\n";

    // Test 6: Post-decrement with a negative bigint
    a = bigint(-1);
    result = a--;
    assert(a == bigint(-2));
    assert(result == bigint(-1));
    std::cout << "Test 6 Passed: bigint(-1)-- = " << result << ", after decrement: " << a << "\n";

    // Test 7: Pre-decrement with a default-constructed bigint
    a = bigint();
    result = --a;
    assert(a == bigint(-1));
    assert(result == bigint(-1));
    std::cout << "Test 7 Passed: --bigint() = " << a << "\n";

    // Test 8: Post-decrement with a default-constructed bigint
    a = bigint();
    result = a--;
    assert(a == bigint(-1));
    assert(result == bigint());
    std::cout << "Test 8 Passed: bigint()-- = " << result << ", after decrement: " << a << "\n";

    // Test 9: Decrementing a large number
    a = bigint("1000000000000");
    result = --a;
    assert(a == bigint("999999999999"));
    assert(result == bigint("999999999999"));
    std::cout << "Test 9 Passed: --bigint(\"1000000000000\") = " << a << "\n";

    std::cout << "All bigint decrement tests passed successfully!\n";
}

int main() {
    test_bigint_constructors();
    test_bigint_addition();
    test_bigint_string_and_addition();
    test_bigint_subtraction();
    test_bigint_string_subtraction();
    test_bigint_comparisons();
    test_bigint_unary_negation();
    test_bigint_assignment_operators();
    test_bigint_multiplication();
    test_bigint_string_multiplication();
    test_bigint_increment();
    test_bigint_decrement();
    return 0;
}

