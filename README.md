# Arbitrary Precision Calculator (APC)

A powerful C implementation of an Arbitrary Precision Calculator that performs arithmetic operations on extremely large numbers beyond the limits of standard integer data types.

## Overview

APC (Arbitrary Precision Calculator) enables you to perform addition, subtraction, multiplication, and division on numbers of virtually unlimited size. The program uses doubly linked lists to store numbers digit by digit, allowing calculations that would otherwise cause integer overflow in traditional implementations.

## Features

- **Arbitrary Precision**: Handle numbers with hundreds or thousands of digits
- **Four Basic Operations**: Addition, Subtraction, Multiplication, and Division
- **Sign Handling**: Proper management of both positive and negative numbers
- **Automatic Optimization**: Leading zeros are automatically removed from results
- **Memory Efficient**: Doubly linked list implementation optimizes memory usage
- **Command Line Interface**: Simple and intuitive command-line operation

## Technical Details

- **Data Structure**: Doubly Linked Lists (each node stores a single digit)
- **Algorithm**: 
  - Addition/Subtraction: Digit-by-digit with carry/borrow propagation
  - Multiplication: Standard long multiplication with partial products
  - Division: Repeated subtraction method
- **Language**: C
- **Platform**: Cross-platform (Linux, macOS, Windows with appropriate compiler)

### How It Works

Each large number is stored as a doubly linked list where:
- Each node contains a single digit (0-9)
- The head points to the most significant digit
- The tail points to the least significant digit
- Bidirectional traversal enables efficient arithmetic operations

**Operations:**
- **Addition**: Processes digits from right to left with carry propagation
- **Subtraction**: Handles borrowing when necessary, ensures larger number is minuend
- **Multiplication**: Uses positional multiplication (like manual long multiplication)
- **Division**: Implements quotient calculation through repeated subtraction

## Prerequisites

- GCC compiler or any C compiler
- Basic knowledge of command line operations
- Understanding of basic arithmetic (optional, but helpful!)

## Installation

1. Clone the repository:
```bash
git clone https://github.com/SLADE0261/Arbitrary-Precision-Calculator-APC-.git
cd Arbitrary-Precision-Calculator-APC-
```

2. Compile the project:
```bash
gcc main.c addition.c subtraction.c multiplication.c division.c -o apc
```

Or compile individual files:
```bash
gcc -c main.c addition.c subtraction.c multiplication.c division.c
gcc main.o addition.o subtraction.o multiplication.o division.o -o apc
```

## Usage

### General Syntax
```bash
./apc <number1> <operator> <number2>
```

### Operations

#### Addition
```bash
./apc 12345678901234567890 + 98765432109876543210
# Output: 111111111011111111100

./apc -500 + 300
# Output: -200

./apc 999999999999999999 + 1
# Output: 1000000000000000000
```

#### Subtraction
```bash
./apc 1000000000000000000 - 1
# Output: 999999999999999999

./apc 100 - 250
# Output: -150

./apc -50 - -30
# Output: -20
```

#### Multiplication
```bash
./apc 123456789 * 987654321
# Output: 121932631112635269

./apc -25 * 4
# Output: -100

./apc 999999999 * 999999999
# Output: 999999998000000001
```

#### Division
```bash
./apc 1000000000000 / 123456789
# Output: 8100 (quotient only)

./apc 100 / 3
# Output: 33

./apc -100 / 5
# Output: -20
```

## Project Structure

```
Arbitrary-Precision-Calculator-APC-/
├── main.c              # Main program entry point and utility functions
├── addition.c          # Addition implementation
├── subtraction.c       # Subtraction implementation
├── multiplication.c    # Multiplication implementation
├── division.c          # Division implementation
├── apc.h              # Header file with function prototypes
└── README.md          # This file
```

## Function Overview

### Core Arithmetic Functions
- `addition()` - Adds two large numbers
- `subtraction()` - Subtracts two large numbers (num1 - num2)
- `multiplication()` - Multiplies two large numbers
- `division()` - Divides two large numbers (returns quotient)

### List Manipulation Functions
- `dl_insert_first()` - Inserts digit at the beginning of list
- `dl_insert_last()` - Inserts digit at the end of list
- `dl_delete_first()` - Removes the first node
- `dl_delete_list()` - Deletes entire list
- `print_list()` - Displays the number stored in the list

## Sign Handling Logic

The calculator implements comprehensive sign handling:

| Operation | Sign Combination | Result Sign | Method |
|-----------|-----------------|-------------|---------|
| Addition | Both positive | Positive | Add magnitudes |
| Addition | Both negative | Negative | Add magnitudes |
| Addition | Different signs | Larger magnitude | Subtract magnitudes |
| Subtraction | Same signs | Depends | Subtract magnitudes |
| Subtraction | Different signs | First operand | Add magnitudes |
| Multiplication | Same signs | Positive | Multiply magnitudes |
| Multiplication | Different signs | Negative | Multiply magnitudes |
| Division | Same signs | Positive | Divide magnitudes |
| Division | Different signs | Negative | Divide magnitudes |

## Important Notes

1. **Input Format**: Numbers can include optional '+' or '-' signs
2. **Division**: Only returns quotient (no remainder/modulo)
3. **Division by Zero**: Returns error message
4. **Leading Zeros**: Automatically removed from results
5. **Memory Management**: All allocated memory is properly freed
6. **Number Size**: Limited only by available memory

## Example Workflow

```bash
# Compile the program
gcc main.c addition.c subtraction.c multiplication.c division.c -o bignumcalc

# Test with small numbers
./bignumcalc 25 + 75
# Output: 100

# Test with very large numbers
./bignumcalc 123456789012345678901234567890 * 987654321098765432109876543210
# Output: (very large result)

# Test with negative numbers
./bignumcalc -1000 - -500
# Output: -500

# Test division
./bignumcalc 999999999 / 7
# Output: 142857142
```

## Error Handling

| Error | Meaning | Solution |
|-------|---------|----------|
| Invalid Input | Wrong number of arguments | Use format: `./bignumcalc num1 op num2` |
| Invalid Input | Non-digit characters | Use only digits, '+', or '-' |
| Division by zero | Divisor is zero | Use non-zero divisor |
| Memory allocation failed | Insufficient memory | Close other programs |

## Performance Characteristics

- **Addition**: O(max(n, m)) where n, m are number of digits
- **Subtraction**: O(max(n, m))
- **Multiplication**: O(n × m)
- **Division**: O(n × m) worst case (repeated subtraction)

## Limitations

- Division only returns integer quotient (no decimal/remainder)
- Division uses repeated subtraction (slower for large quotients)
- No support for decimal/floating-point numbers
- Input must be provided via command line arguments

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

### Potential Enhancements
- [ ] Add modulo operation for remainders
- [ ] Implement power/exponentiation
- [ ] Add square root calculation
- [ ] Support for decimal/floating-point numbers
- [ ] Interactive mode (multiple operations in one session)
- [ ] Optimize division algorithm (long division method)
- [ ] Add factorial calculation
- [ ] GCD and LCM operations

## License

This project is open source and available under the [MIT License](LICENSE).

## Author

**Krishnakant C. Pore**
- Project Date: July 7, 2025
- Email: [your-email@example.com]
- GitHub: [@yourusername]

## Acknowledgments

- Doubly linked list data structure
- Elementary arithmetic algorithms
- C programming community

## Testing

### Test Cases Included

```bash
# Basic Operations
./bignumcalc 123 + 456                    # Expected: 579
./bignumcalc 1000 - 1                     # Expected: 999
./bignumcalc 25 * 4                       # Expected: 100
./bignumcalc 100 / 5                      # Expected: 20

# Large Numbers
./bignumcalc 999999999999 + 1             # Expected: 1000000000000
./bignumcalc 123456789012345 * 9          # Expected: 1111111101111105

# Negative Numbers
./bignumcalc -50 + -50                    # Expected: -100
./bignumcalc -100 * -5                    # Expected: 500
./bignumcalc 100 - 200                    # Expected: -100
```

## FAQ

**Q: What's the maximum number size I can use?**  
A: The only limit is your system's available memory. Each digit requires one node in the linked list.

**Q: Can I use decimal numbers?**  
A: No, currently only integers are supported.

**Q: Why doesn't division show remainders?**  
A: The current implementation only returns the quotient. Remainder functionality can be added.

**Q: Is this faster than normal integer arithmetic?**  
A: No, this is significantly slower. Use this only when numbers exceed standard integer limits.

---

**⭐ If you find this project useful, please consider giving it a star!**