# LAHTP-PASSWORDTEST Tool v-1.0 for Linux

Welcome to the LAHTP-PASSWORDTEST tool v-1.0. This tool provides functionalities to:
1. Test the strength of a given password.
2. Generate a strong password.

This tool helps you evaluate the strength of your password and categorize it as weakest, weak, medium, strong, or strongest based on its score. It also generates secure passwords that adhere to best practices.

## Features

- **Password Strength Testing**: Validates an input password and provides a strength score.
- **Password Generation**: Generates a strong password that includes uppercase letters, lowercase letters, digits, and symbols.
- **Help**: Provides guidance on how to use the tool.

## Usage

To use this tool, you need to pass command-line arguments. The available options are:

- `-h`: Show the help message and exit.
- `-g`: Generate a strong password.
- `-t <password>`: Test the strength of the provided password.

### Examples

#### Show Help

```sh
./password_tool -h
```

#### Generate a Password

```sh
./password_tool -g
```

#### Test a Password

```sh
./password_tool -t YourPassword123!
```

## Password Strength Criteria

To achieve the strongest score, your password must:
- Be at least 8 characters long.
- Contain at least one uppercase letter.
- Contain at least three lowercase letters.
- Contain at least one symbol.
- Contain at least three numeric characters.

Passwords containing sequences of consecutive numbers are flagged as potentially weaker.



## Compilation

To compile the program, use the following command:

```sh
gcc -o password_tool password_tool.c
```


---

This README provides a comprehensive guide on how to use the LAHTP-PASSWORDTEST tool v-1.0. If you have any questions or need further assistance, please refer to the help option `-h` or contact the author.