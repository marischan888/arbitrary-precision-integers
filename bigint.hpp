#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


class bigint {

public:
    bigint() : digits(0), is_negative(false) {};

    // [0, 0, 1] = 100, low to high
    explicit bigint(int64_t num) : is_negative(num < 0) {
        if (num < 0) num = - num;
        do {
            digits.push_back(num % 10);
            num = num / 10;
        } while (num > 0);
    }

    explicit bigint(const string& str) : is_negative(false) {
        if (str.empty()) throw invalid_argument("bigint string is empty");

        size_t lead = 0;
        if (str[0] == '-') {
            is_negative = true;
            lead = 1;
        }
        for (size_t i = lead; i < str.size(); ++i) {
            if (!isdigit(str[i])) throw invalid_argument("bigint string contains non-digit characters");
            digits.push_back(str[i] - '0');
        }
        ranges::reverse(digits);
        remove_leading_zeros();
    }

private:
    vector<int64_t> digits;
    bool is_negative;

    void remove_leading_zeros() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        if (digits.size() == 1 && digits[0] == 0) is_negative = false;
    }

    [[nodiscard]] bigint add_absolute_values(const bigint& value) const {
        bigint result;
        result.is_negative = is_negative;
        int64_t carry = 0, sum = 0;
        size_t max_size = std::max(digits.size(), value.digits.size());
        result.digits.resize(max_size);

        for (size_t i = 0; i < max_size; ++i) {
            sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < value.digits.size()) sum += value.digits[i];
            carry = sum / 10;
            result.digits[i] = sum % 10;
        }
        if (carry != 0) result.digits.push_back(carry);
        return result;
    }

    // 3(this) + (01)-
    [[nodiscard]] bigint subtract_absolute_values(const bigint& value) const {
        bigint result;
        const bool abs_value_is_larger = digits.size() < value.digits.size();
        result.is_negative = *this < value or abs_value_is_larger;
        const vector<int64_t>& abs_larger = (abs_value_is_larger ? value.digits : digits);
        const vector<int64_t>& abs_smaller = (abs_value_is_larger ? digits : value.digits);
        int borrow = 0;

        for (size_t i = 0; i < abs_larger.size(); ++i) {
            int64_t diff = abs_larger[i] - borrow - (i < abs_smaller.size() ? abs_smaller[i] : 0);
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits.push_back(diff);
        }
        result.remove_leading_zeros();
        return result;
    }

public:
    bool operator==(const bigint & value) const {
        return is_negative == value.is_negative && digits == value.digits;
    }

    bool operator!=(const bigint & value) const {
        return !(*this == value);
    }

    bool operator<(const bigint & value) const {
        // negative sign
        if (is_negative != value.is_negative) return is_negative;
        // size not equal
        if (digits.size() != value.digits.size()) {
            return is_negative ? digits.size() > value.digits.size() : digits.size() < value.digits.size();
        }
        // size equal: 102 and 003
        for (size_t i = digits.size() - 1; i > 0; --i) {
            if (digits[i] != value.digits[i]) {
                return is_negative ? digits[i] > value.digits[i] : digits[i] < value.digits[i];
            }
        }
        return digits[0] < value.digits[0];
    }

    bool operator>(const bigint & value) const {
        return value < *this;
    }

    bool operator>=(const bigint & value) const {
        return !(*this < value);
    }

    bool operator<=(const bigint & value) const {
        return value >= *this;
    }

    // Unary
    bigint operator-() const {
        bigint temp = *this;
        if (temp.digits[0] != 0) temp.is_negative = !is_negative;
        return temp;
    }

    // TODO: test the operator- and unary operator
    bigint operator-(const bigint& other) const {
        bigint result;
        if (is_negative != other.is_negative) {
            // Different sign: Perform addition
            result = add_absolute_values(other);
            result.is_negative = is_negative;
        } else {
            // Same sign: Perform subtraction
            result = subtract_absolute_values(other);
        }
        result.remove_leading_zeros();
        return result;
    }

    // Addition
    bigint operator+(const bigint& value) const {
        bigint sum_result;
        if (is_negative == value.is_negative) {
            sum_result = add_absolute_values(value);
        } else {
            sum_result = subtract_absolute_values(value);
        }
        return sum_result;
    }
};

#endif
