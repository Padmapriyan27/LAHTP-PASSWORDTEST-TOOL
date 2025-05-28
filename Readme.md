# LAHTP-PASSWORDTEST Tool


A command-line tool to test password strength and generate strong passwords.

## Features
- **Password Strength Testing**: Evaluates passwords based on multiple criteria.
- **Password Generation**: Creates strong, randomized passwords.
- **Detailed Feedback**: Provides actionable insights to improve weak passwords.
- **Colorful Terminal Output**: Visual strength indicators.

## Installation
No installation required! Just compile and run:

```bash
gcc lahtp-passwordtest.c -o passwordtest
```

## Usage

### Basic Commands
```
./passwordtest [OPTION] [PASSWORD]
```

### Options
| Option          | Description                                |
|-----------------|--------------------------------------------|
| `-h`, `--help`  | Show help message                          |
| `-g`, `--gen`   | Generate a strong password                 |
| `-t`, `--test`  | Test password strength (requires password) |

### Examples
1. Generate a password:
   ```bash
   ./passwordtest --gen
   ```

2. Test a password:
   ```bash
   ./passwordtest --test "MyP@ssw0rd!"
   ```

## Password Strength Criteria
The tool evaluates passwords based on:

| Criteria               | Minimum Requirement |
|------------------------|---------------------|
| Length                 | 8 characters        |
| Uppercase letters      | 2                   |
| Lowercase letters      | 3                   |
| Digits                 | 3                   |
| Special characters     | 2                   |
| Consecutive sequences  | None allowed        |

## Strength Ratings
| Rating      | Score | Color  |
|-------------|-------|--------|
| Weakest     | 0-3   | Red    |
| Weak        | 4-5   | Red    |
| Average     | 6     | Yellow |
| Medium      | 7-8   | Yellow |
| Strong      | 9     | Green  |
| Strongest   | 10    | Green  |

## Technical Details
- **Max Password Length**: 16 characters
- **Character Sets**: A-Z, a-z, 0-9, !@#$-^&*()_+|<>{}
- **Sequence Detection**: Identifies consecutive character/number sequences

## Requirements
- C compiler (GCC recommended)
- PS or Linux/Unix terminal (for color support)
