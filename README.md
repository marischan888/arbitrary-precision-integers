# arbitrary-precision-integers
`bigint.hpp`, an implementation of arbitrary-precision integers. This
class provides functionality for performing mathematical operations (addition, subtraction, multiplication, etc.) on
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
   ```cpp
   bigint();                               // Default constructor - initializes to 0
   bigint(int value);                      // Constructs from an integer
   bigint(const std::string& value);       // Constructs from a string representation
   ```
   Description: Initializes a `bigint` object from different types, allowing flexibility in usage and seamless
   integration with existing code that uses numeric types.

2. **Arithmetic Operators**
   ```cpp
   bitint operator+(const bigint& value) const;
   bitint operator-(const bigint& value) const;
   bitint operator*(const bigint& value) const;

   bitint& operator+=(const bigint& value);
   bitint& operator-=(const bigint& value);
   bitint& operator*=(const bigint& value);
   ```

   Description: Overloaded operators to perform arithmetic on `bigint` objects. These operators allow direct
   manipulation, similar to built-in numeric types.

4. **Comparison Operators**
   ```cpp
   bool operator==(const bigint& value) const;
   bool operator!=(const bigint& value) const;
   bool operator<(const bigint& value) const;
   bool operator<=(const bigint& value) const;
   bool operator>(const bigint& value) const;
   bool operator>=(const bigint& value) const;
   ```
   Description: Overloaded comparison operators to enable relational operations between `bigint` objects.

5. **Input/Output Operators**
   ```cpp
   friend std::ostream& operator<<(std::ostream& os, const BigInt& bigint);
   ```
   Description: Stream insertion and extraction overload allow the user to output `bigint` objects directly with
   `cout`.

6. **Increment and Decrement Operators**
   ```cpp
   bigint& operator++();       // Pre-increment
   bigint operator++(int);     // Post-increment
   bigint& operator--();       // Pre-decrement
   bigint operator--(int);     // Post-decrement
   ```
   Description: Overloaded increment and decrement operators to modify the value of a `bigint` object by 1.
    - **Pre-increment (`++obj`)**: Increments the value before returning the object.
    - **Post-increment (`obj++`)**: Returns the object before incrementing its value.
    - **Pre-decrement (`--obj`)**: Decrements the value before returning the object.
    - **Post-decrement (`obj--`)**: Returns the object before decrementing its value.
   
## Test
Unit tests are in `test.cpp`.

## Usage under Mac
Build the `test.cpp` with clang++ (or with g++)
```shell
clang++ -o test test.cpp -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow -Wpedantic -std=c++23
```
Run test
```shell
./test
```
