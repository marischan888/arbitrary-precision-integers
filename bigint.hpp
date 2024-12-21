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

    [[nodiscard]] bigint subtract_absolute_values(const bigint& value) const {
        bigint result;
        result.is_negative = (value.is_negative and abs_values_larger(value)) or (*this < value and not abs_values_larger(value));
        const vector<int64_t>& abs_larger = (abs_values_larger(value) ? value.digits : digits);
        const vector<int64_t>& abs_smaller = (abs_values_larger(value) ? digits : value.digits);
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

    [[nodiscard]] bigint multiply_absolute_values(const bigint& value) const {
        bigint result;
        result.digits.resize(digits.size() + value.digits.size(), 0);

        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < value.digits.size() || carry; ++j) {
                const int64_t current = result.digits[i + j] + digits[i] * (j < value.digits.size() ? value.digits[j] : 0) + carry;
                result.digits[i + j] = current % 10;
                carry = current / 10;
            }
        }
        result.remove_leading_zeros();
        return result;
    }

    [[nodiscard]] bool abs_values_larger(const bigint& value) const {
        if (digits.size() < value.digits.size()) return true;
        if (digits.size() > value.digits.size()) return false;
        for (size_t i = digits.size() - 1; i > 0; --i) {
            if (digits[i] != value.digits[i]) {
                return digits[i] < value.digits[i];
            }
        }
        return digits[0] < value.digits[0];
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

    friend std::ostream& operator<<(std::ostream& os, const bigint& num) {
        if (num.is_negative) os << '-';
        for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it) {
            os << *it;
        }
        return os;
    }

    // Unary
    bigint operator-() const {
        bigint temp = *this;
        if (temp.digits.size() > 1 or (temp.digits.size() == 1 and temp.digits[0] != 0)) temp.is_negative = !is_negative;
        return temp;
    }

    // Subtraction
    bigint operator-(const bigint& value) const {
        bigint result;
        if (is_negative != value.is_negative) {
            result = add_absolute_values(value);
            result.is_negative = is_negative;
        } else {
            result = subtract_absolute_values(-value);
        }
        result.remove_leading_zeros();
        return result;
    }

    bigint& operator-=(const bigint& value) {
        *this = *this - value;
        return *this;
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

    bigint& operator+=(const bigint& value) {
        *this = *this + value;
        return *this;
    }

    // Multiplication
    bigint operator*(const bigint& value) const {
        bigint result = multiply_absolute_values(value);
        result.is_negative = (is_negative != value.is_negative);
        return result;
    }

    bigint& operator*=(const bigint& other) {
        *this = *this * other;
        return *this;
    }

    // Increment and Decrement
    //pre
    bigint& operator++() {
        *this = *this + bigint(1);
        return *this;
    }

    //post
    bigint operator++(int) {
        bigint temp = *this;
        ++(*this);
        return temp;
    }

    bigint& operator--() {
        *this = *this - bigint(1);
        return *this;
    }

    bigint operator--(int) {
        bigint temp = *this;
        --(*this);
        return temp;
    }

};

#endif
