# arbitrary-precision-integers

`bigint.hpp`, an implementation of arbitrary-precision integers. This class provides functionality for performing mathematical operations (addition, subtraction, multiplication, etc.) on
integers of any size, far beyond the limits of built-in C++ types.

## Overview
The `bitint` supports the following features:

- Construction from various numeric types and string of digit.
- Addition (+ and +=)
- Subtraction (- and -=)
- Multiplication (* and *=)
- Negation (unary -)
- Comparison (==, !=, <, >, <=, and >=)
- Insertion (<<, to print the integer to a stream such as std::cout or a file)
- Increment (++, both pre-increment and post-increment)
- Decrement (--, both pre-decrement and post-decrement)

## Method Documentation

### Public Methods

1. **Constructors**

   Initializes a `bigint` object from different types, allowing flexibility in usage and seamless
   integration with existing code that uses numeric types.

   ```cpp
   bigint();                               // Default constructor - initializes to 0
   bigint(int value);                      // Constructs from an integer
   bigint(const std::string& value);       // Constructs from a string representation
   ```

2. **Arithmetic Operators**

   Overloaded operators to perform arithmetic on `bigint` objects. These operators allow direct
   manipulation, similar to built-in numeric types.

   ```cpp
   bitint operator+(const bigint& value) const;
   bitint operator-(const bigint& value) const;
   bitint operator*(const bigint& value) const;

   bitint& operator+=(const bigint& value);
   bitint& operator-=(const bigint& value);
   bitint& operator*=(const bigint& value);
   ```
3. **Comparison Operators**

   Overloaded comparison operators to enable relational operations between `bigint` objects.

   ```cpp
   bool operator==(const bigint& value) const;
   bool operator!=(const bigint& value) const;
   bool operator<(const bigint& value) const;
   bool operator<=(const bigint& value) const;
   bool operator>(const bigint& value) const;
   bool operator>=(const bigint& value) const;
   ```
   
4. **Output Operators**

   Stream extraction overload allow the user to output `bigint` objects directly with
   `cout`.

   ```cpp
   friend std::ostream& operator<<(std::ostream& os, const BigInt& bigint);
   ```

5. **Increment and Decrement Operators**

   Overloaded increment and decrement operators to modify the value of a `bigint` object by 1.
   - **Pre-increment (`++obj`)**: Increments the value before returning the object.
   - **Post-increment (`obj++`)**: Returns the object before incrementing its value.
   - **Pre-decrement (`--obj`)**: Decrements the value before returning the object.
   - **Post-decrement (`obj--`)**: Returns the object before decrementing its value.
   
   ```cpp
   bigint& operator++();       // Pre-increment
   bigint operator++(int);     // Post-increment
   bigint& operator--();       // Pre-decrement
   bigint operator--(int);     // Post-decrement
   ```
   
## Test
Unit tests are in `test.cpp`.

### Run test under Mac
Build the `test.cpp` with clang++ (or with g++)
```shell
clang++ -o test test.cpp -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow -Wpedantic -std=c++23
```
Run test
```shell
./test
```
