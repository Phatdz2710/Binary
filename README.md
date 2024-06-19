# BINARY DATA TYPE CLASS 'Bin'
## Overview
The binary class represents a binary number (8-bits) and provides methods to manipulate and convert these numbers. It offers functionalities commonly found in binary arithmetic and logic operations.

## Class Members
* `protected char* bin` - Stores the binary representation of the number as a null-terminated character array. 
* Constructors
* Member Functions
```c++
int ToDecimal() const \\ Converts the binary number to its decimal equivalent
```

* Overload Operators (all binary)
  + `+`  : Addition
  + `-`  : Subtraction
  + `*`  : Multiplication
  + `\`  : Division
  + `<<` : Left shift
  + `>>` : Right shift
  + `&`  : Bitwise AND
  + `|`  : Bitwise OR
  + `^`  : Bitwise XOR
  + `~`  : Bitwise NOT
  + `[]` : Get bit by position

## Examples
```c++
#include "Binary.h"

int main()
{
    Bin a(-15);
    Bin b("00101100");
    Bin c = a + b;
    Bin c = a * b;
    cout << "Result: " << c;
    return 1;
}
 
