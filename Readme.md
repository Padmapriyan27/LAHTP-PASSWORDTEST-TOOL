# LAHTP-PASSWORDTEST Tool

## Version: 1.0.2

The LAHTP-PASSWORDTEST tool for linux is designed for testing and generating passwords. It helps you:
1. **Test the strength of your password**
2. **Generate strong passwords**

This tool evaluates your password based on various criteria and provides feedback on its strength.

## Features

- **Password Strength Testing**: Evaluates your password against criteria such as length, uppercase, lowercase, digits, and special characters.
- **Password Generation**: Generates a random strong password with a mix of uppercase, lowercase, digits, and special characters.

## Usage

### Compilation

To compile the tool, use:

```bash
gcc -o lahtp_passwordtest lahtp_passwordtest.c
```

### Commands

- **Help**: Display help message
    ```bash
    ./lahtp_passwordtest -h
    ```

- **Generate Password**: Generate a strong password
    ```bash
    ./lahtp_passwordtest -g
    ```

- **Test Password**: Test the strength of a provided password
    ```bash
    ./lahtp_passwordtest -t <password>
    ```

### Examples

1. **Generate a Password**:
    ```bash
    ./lahtp_passwordtest -g
    ```

2. **Test a Password**:
    ```bash
    ./lahtp_passwordtest -t MyP@ssw0rd123!
    ```

## Description

### Options

- `-h` : Show help message and exit.
- `-g` : Generate a strong password.
- `-t <password>` : Test the strength of the provided password.

### Password Validation

The tool checks the following criteria for password strength:

- Minimum length of 8 characters.
- At least 2 uppercase letters.
- At least 3 lowercase letters.
- At least 3 digits.
- At least 2 special characters (e.g., !@#$-^&*()_+|).

It also detects sequences of consecutive numbers and provides feedback if the password does not meet the required criteria.

### Password Strength Levels

- **Weakest**: The password is very weak.
- **Weak**: The password is weak but can be improved.
- **Average**: The password is average in strength.
- **Medium**: The password is medium strength.
- **Strong**: The password is strong.
- **Strongest**: The password is very strong.

## Code Overview

The code consists of functions for generating passwords, testing password strength, analyzing password properties, and evaluating the password based on predefined criteria.

Thank you!