#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <algorithm>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Compares the absolute values of the current bigint object
 *        with another bigint object to determine which is larger.
 *
 *        This method considers only the magnitudes of the numbers
 *        and does not take into account their signs.
 *
 * @param value The bigint object to compare against.
 * @return True if the absolute value of the provided bigint object is larger
 *         than the absolute value of the current bigint object, otherwise false.
 */
class bigint {
public:
    /**
     * @brief Default constructor for the bigint class.
     *        Initializes a bigint object with default values.
     *
     * @return An instance of bigint with default digits set to 0
     *         and is_negative set to false.
     */
    bigint() : digits(0), is_negative(false) {}


    /**
     * @brief Constructs a bigint object from a given int64_t number.
     *        The number is converted into its digit representation,
     *        with each digit stored in the `digits` vector in reverse order.
     *        Handles both positive and negative numbers.
     *
     * @param num The int64_t number to initialize the bigint object.
     *            If the number is negative, the bigint will be marked
     *            as negative.
     * @return A bigint object representing the given number.
     */
    explicit bigint(int64_t num) : is_negative(num < 0) {
        if (num < 0) num = - num;
        do {
            digits.push_back(num % 10);
            num = num / 10;
        } while (num > 0);
    }

    /**
     * @brief Constructs a bigint object from a string representation of a number.
     *        Initializes the bigint object based on the input string, which may
     *        include an optional leading "-" to indicate a negative number.
     *
     * @param str The string representation of the number to initialize the bigint object with.
     *            Must contain only digits and an optional leading "-" for negative numbers.
     *            Leading zeros are handled appropriately, and the result will not maintain
     *            them in storage.
     *
     * @throw std::invalid_argument Throws an exception if the input string is empty
     *                               or contains invalid (non-digit) characters.
     */
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
    /**
     * @brief Stores the individual digits of a large integer.
     *        This container holds each digit of the large integer as
     *        separate elements, allowing for efficient manipulation
     *        and operations on the number. The digits are typically
     *        stored in a specific order (e.g., the least significant digit
     *        first), depending on the implementation.
     */
    vector<int64_t> digits;

    /**
     * @brief Boolean flag indicating whether the number is negative.
     *        Represents the sign of a number, where true denotes a negative
     *        value and false indicates a non-negative value.
     */
    bool is_negative;

    /**
     * @brief Removes leading zeros from the digits vector of the bigint object.
     *        Ensures that the bigint representation is normalized.
     *
     *        This method iteratively removes any trailing zeros in the digits vector,
     *        leaving only the most significant digits. If the resulting bigint has a
     *        value of zero (i.e., only one digit remaining which is 0), the is_negative
     *        flag is set too false to represent a non-negative zero.
     */
    void remove_leading_zeros() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        if (digits.size() == 1 && digits[0] == 0) is_negative = false;
    }

    /**
     * @brief Computes the sum of absolute values of the current bigint and the provided bigint.
     *        This method assumes that both numbers are treated as non-negative regardless
     *        of their actual sign and returns the result with the same sign as the current bigint.
     *
     * @param value A reference to the bigint object that is to be added to the current object.
     * @return A bigint object representing the sum of the absolute values of the two bigints,
     *         with the same sign as the current bigint.
     */
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

    /**
     * @brief Subtracts the absolute values of two bigint objects.
     *        The result retains the appropriate sign based on the relative size
     *        of the operands and their signs.
     *
     * @param value The bigint object whose absolute value is to be subtracted
     *              from the absolute value of the current bigint object.
     *
     * @return A bigint object representing the result of the absolute value subtraction.
     *         The sign of the result is determined by the relative size and sign of
     *         the operands.
     */
    [[nodiscard]] bigint subtract_absolute_values(const bigint& value) const {
        bigint result;
        const bool is_value_larger = abs_values_larger(value);
        result.is_negative = (value.is_negative and is_value_larger) or (*this < value and not is_value_larger);
        const vector<int64_t>& abs_larger = (is_value_larger ? value.digits : digits);
        const vector<int64_t>& abs_smaller = (is_value_larger ? digits : value.digits);
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

    /**
     * @brief Multiplies the absolute values of the current bigint object
     *        and another bigint object without considering their signs.
     *
     *        This method calculates the product of the digits of the two bigints
     *        as if they were positive numbers and stores the result in a new
     *        bigint object. Any leading zeros in the result are removed.
     *
     * @param value The bigint object whose absolute value is multiplied
     *              with the absolute value of the current bigint.
     * @return A new bigint object representing the product of the
     *         absolute values of the two bigints.
     */
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

    /**
     * @brief Compares the absolute values of the current bigint object
     *        with another bigint object to determine which is larger.
     *
     * @param value The bigint object to compare against.
     * @return True if the absolute value of the provided bigint object is larger
     *         than the absolute value of the current bigint object, false otherwise.
     */
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
    /**
     * @brief Equality operator for comparing two bigint objects.
     *        Checks if both the is_negative flag and the digits of the
     *        two bigint objects are identical.
     *
     * @param value The bigint object to compare with the current instance.
     * @return true if both bigint objects are equal, otherwise false.
     */
    bool operator==(const bigint & value) const {
        return is_negative == value.is_negative && digits == value.digits;
    }

    /**
     * @brief Inequality operator for comparing two bigint objects.
     *        Determines if the current bigint object is not equal to the given bigint object.
     *
     * @param value The bigint object to compare with the current object.
     * @return True if the current bigint object is not equal to the given bigint object,
     *         otherwise false.
     */
    bool operator!=(const bigint & value) const {
        return !(*this == value);
    }

    /**
     * @brief Overloads the `<` operator to compare two bigint objects.
     *        Determines whether the current bigint object is less than
     *        the given bigint object.
     *
     * @param value The bigint object to compare against.
     * @return True if the current bigint object is less than the given
     *         bigint object, otherwise False.
     */
    bool operator<(const bigint & value) const {
        if (is_negative != value.is_negative) return is_negative;
        if (digits.size() != value.digits.size()) {
            return is_negative ? digits.size() > value.digits.size() : digits.size() < value.digits.size();
        }
        for (size_t i = digits.size() - 1; i > 0; --i) {
            if (digits[i] != value.digits[i]) {
                return is_negative ? digits[i] > value.digits[i] : digits[i] < value.digits[i];
            }
        }
        return digits[0] < value.digits[0];
    }

    /**
     * @brief Overloaded greater-than operator for comparing two bigint objects.
     *
     *        Compares the current bigint object with another bigint object to determine
     *        if the current object is greater.
     *
     * @param value A reference to the bigint object being compared to the current object.
     *
     * @return True if the current bigint object is greater than the provided bigint object,
     *         otherwise false.
     */
    bool operator>(const bigint & value) const {
        return value < *this;
    }

    /**
     * @brief Compares the current bigint object with the given bigint object
     *        to determine if it is greater than or equal to the other.
     *
     * @param value The bigint object to compare against.
     * @return True if the current object is greater than or equal to the given bigint object,
     *         otherwise false.
     */
    bool operator>=(const bigint & value) const {
        return !(*this < value);
    }

    /**
     * @brief Overloaded less than or equal to operator for bigint comparison.
     *        Compares the current bigint object with the provided bigint
     *        to determine if it is less than or equal.
     *
     * @param value A constant reference to the bigint object to compare with.
     * @return True if the current bigint object is less than or equal
     *         to the provided bigint, otherwise false.
     */
    bool operator<=(const bigint & value) const {
        return value >= *this;
    }

    /**
     * @brief Overloaded operator for performing a custom operation
     *        specific to the class or type where it is defined.
     *
     * @param other The operand to perform the operation with.
     *              The type of the parameter depends on the context
     *              in which the operator is implemented.
     *
     * @return The result of applying the operator, with the return
     *         type depending on the nature of the operation being
     *         implemented.
     */
    friend ostream& operator<<(std::ostream& os, const bigint& num) {
        if (num.is_negative) os << '-';
        for (int64_t digit : std::ranges::reverse_view(num.digits)) {
            os << digit;
        }
        return os;
    }

    /**
     * @brief Unary negation operator for the bigint class.
     *        Creates a new bigint object with its sign inverted, unless it
     *        represents zero.
     *
     * @return A new bigint object with the sign inverted if the value is non-zero,
     *         otherwise, returns a bigint object representing zero with no sign change.
     */
    bigint operator-() const {
        bigint temp = *this;
        if (temp.digits.size() > 1 or (temp.digits.size() == 1 and temp.digits[0] != 0)) temp.is_negative = !is_negative;
        return temp;
    }

    /**
     * @brief Overloaded subtraction operator for bigint.
     *        Computes the result of subtracting the given bigint
     *        value from the current bigint instance.
     *
     * @param value The bigint instance to be subtracted from
     *              the current bigint.
     * @return A new bigint instance representing the result
     *         of the subtraction operation.
     */
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

    /**
     * @brief Subtracts the given bigint from the current bigint and updates the current bigint.
     *
     * Performs subtraction by using the overloaded subtraction operator and assigns
     * the result back to the current bigint object.
     *
     * @param value The bigint object to be subtracted from the current object.
     * @return A reference to the modified bigint object after performing the subtraction.
     */
    bigint& operator-=(const bigint& value) {
        *this = *this - value;
        return *this;
    }

    /**
     * @brief Overloads the addition operator for the bigint class.
     *        Computes the sum of the current bigint and the provided bigint.
     *
     * @param value A constant reference to a bigint object to be added to the current object.
     * @return A new bigint object that represents the result of the addition.
     *         Maintains proper sign handling based on the input values.
     */
    bigint operator+(const bigint& value) const {
        bigint sum_result;
        if (is_negative == value.is_negative) {
            sum_result = add_absolute_values(value);
        } else {
            sum_result = subtract_absolute_values(value);
        }
        return sum_result;
    }

    /**
     * @brief Overloads the += operator for the bigint class to add another bigint.
     *        This updates the current bigint object by adding the provided bigint value.
     *
     * @param value The bigint to be added to the current bigint object.
     * @return A reference to the updated bigint object after addition.
     */
    bigint& operator+=(const bigint& value) {
        *this = *this + value;
        return *this;
    }

    /**
     * @brief Overloaded multiplication operator for the bigint class.
     *        Computes the product of the current bigint object and the given bigint value.
     *
     * @param value The bigint object to be multiplied with the current object.
     * @return A new bigint object representing the product of the two bigint values.
     *         The resulting sign (positive or negative) is computed based on the signs
     *         of the operands.
     */
    bigint operator*(const bigint& value) const {
        bigint result = multiply_absolute_values(value);
        result.is_negative = (is_negative != value.is_negative);
        return result;
    }

    /**
     * @brief Compound assignment operator for multiplying this bigint by another bigint.
     *        Multiplies the current bigint by the provided bigint and assigns the result
     *        to the current bigint.
     *
     * @param other The bigint instance to multiply with the current bigint.
     * @return A reference to the current bigint after multiplication.
     */
    bigint& operator*=(const bigint& other) {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Pre-increment operator to increase the value of the current bigint object by one.
     *
     *        This operator modifies the current bigint object by adding 1 to its value.
     *
     * @return A reference to the current bigint object after incrementing its value.
     */
    bigint& operator++() {
        *this = *this + bigint(1);
        return *this;
    }

    /**
     * @brief Increments the value of the current bigint object by 1, but returns
     *        its original value before the increment.
     *
     *        This is the post-increment operator, which provides a copy
     *        of the bigint object as it was before the increment operation.
     *
     * @return A copy of the bigint object as it was before the increment.
     */
    bigint operator++(int) {
        bigint temp = *this;
        ++(*this);
        return temp;
    }

    /**
     * @brief Decrements the current bigint object by 1 and returns a reference to it.
     *
     *        This method reduces the value of the current bigint object by a unit
     *        and updates it in place. The operation modifies the original object.
     *
     * @return A reference to the current bigint object after decrementing its value.
     */
    bigint& operator--() {
        *this = *this - bigint(1);
        return *this;
    }

    /**
     * @brief Decrements the current bigint object by one (postfix decrement operator)
     *        and returns the value prior to the decrement.
     *
     *        This operator decreases the numeric value of the bigint object by one
     *        while storing the original value in a temporary bigint object to return it.
     *
     * @param None
     * @return A bigint object that represents the value of the current bigint
     *         object before the decrement operation.
     */
    bigint operator--(int) {
        bigint temp = *this;
        --(*this);
        return temp;
    }
};

#endif