/*
************************************************************
*  Hey,This is the LAHTP-PASSWORDTEST tool v-1.0, this for *
*              1.Test your password strength               *
*              2.Generate strong password                  *
*   This tool helps you to test your input password and    *
*   validate whether your password is weak or weakest or   *
*   medium or strong or strongest and rate your password   *
*   score with their corresponding strength.               *                 
************************************************************
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constants
#define PASSWORD_LENGTH 14
#define MIN_PASSWORD_LENGTH 8
#define MIN_UPPERCASE 2
#define MIN_LOWERCASE 3
#define MIN_DIGIT 3
#define MIN_SPECIALCHAR 2
#define SEQUENCE_THRESHOLD 2
#define MAX_SCORE 10 // Adjusted maximum score

typedef enum PassStrength_t {
    WEAKEST,
    WEAK,
    AVERAGE,
    MEDIUM,
    STRONG,
    STRONGEST
} PasswordStrength;

typedef struct Pass_t {
    char password[PASSWORD_LENGTH + 1];
} Password;

typedef struct PassProp_t {
    char password[PASSWORD_LENGTH + 1];
    int uppercase;
    int lowercase;
    int digit;
    int specialchar;
    int sequence_detected;
} PasswordProperties;

typedef struct PassResult_t {
    int score;
    PasswordStrength strength;
} PasswordResult;

// Function prototypes
static void print_help(void);
static void generate_password(void);
static void test_password_length(const char *password);
static PasswordProperties analyze_password(const char *password);
static PasswordResult evaluate_password(const PasswordProperties *props);
static int is_sequence(const char *password);
static const char* password_strength_str(PasswordStrength strength);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-h] [-g] [-t <password>]\n", argv[0]);
        print_help();
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-h") == 0) {
        print_help();
    } else if (strcmp(argv[1], "-g") == 0) {
        generate_password();
    } else if (strcmp(argv[1], "-t") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s -t <password> \n", argv[0]);
            return EXIT_FAILURE;
        }

        test_password_length(argv[2]);
    } else {
        fprintf(stderr, "Invalid option. Use -h for help\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Function to print help
static void print_help(void) {

    printf("                  ██       █████  ██   ██ ████████ ██████                                                  \n");
    printf("                  ██      ██   ██ ██   ██    ██    ██   ██                                                 \n");
    printf("                  ██      ███████ ███████    ██    ██████                                                  \n");
    printf("                  ██      ██   ██ ██   ██    ██    ██                                                      \n");
    printf("                  ███████ ██   ██ ██   ██    ██    ██                                                      \n");
    printf("                                                                                                           \n");
    printf("                                                                                                           \n");
    printf("  ██████   █████  ███████ ███████ ██     ██  ██████  ██████  ██████      ████████ ███████ ███████ ████████ \n");
    printf("  ██   ██ ██   ██ ██      ██      ██     ██ ██    ██ ██   ██ ██   ██        ██    ██      ██         ██    \n");
    printf("  ██████  ███████ ███████ ███████ ██  █  ██ ██    ██ ██████  ██   ██        ██    █████   ███████    ██    \n");
    printf("  ██      ██   ██      ██      ██ ██ ███ ██ ██    ██ ██   ██ ██   ██        ██    ██           ██    ██    \n");
    printf("  ██      ██   ██ ███████ ███████  ███ ███   ██████  ██   ██ ██████         ██    ███████ ███████    ██    \n");
    printf("                                                                                                           \n");
    printf("                                                                                                           \n");
    printf("                  ████████  ██████   ██████  ██                                                            \n");
    printf("                     ██    ██    ██ ██    ██ ██                                                            \n");
    printf("                     ██    ██    ██ ██    ██ ██                                                            \n");
    printf("                     ██    ██    ██ ██    ██ ██                                                            \n");
    printf("                     ██     ██████   ██████  ███████                                                       \n");

    printf("\nLAHTP-PASSWORDTEST TOOL V-1.0.1\n");
    printf("Options: \n");
    printf("\t-h                  Show this help message and exit\n");
    printf("\t-g                  Generate a strong password\n");
    printf("\t-t <password>       Test the strength of the provided password\n");

}

// Function to generate password
static void generate_password(void) {
    Password pass;
    const char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lower[] = "abcdefghijklmnopqrstuvwxyz";
    const char digits[] = "0123456789";
    const char symbols[] = "!@#$&*()_+|";
    size_t i, index;

    srand((unsigned int)time(NULL));
    // Ensure at least one character from each category is present
    pass.password[0] = upper[rand() % strlen(upper)];
    pass.password[1] = lower[rand() % strlen(lower)];
    pass.password[2] = digits[rand() % strlen(digits)];
    pass.password[3] = symbols[rand() % strlen(symbols)];

    // Fill the remaining characters
    for (i = 4; i < PASSWORD_LENGTH; i++) {
        index = rand() % 4;
        switch (index) {
            case 0:
                pass.password[i] = upper[rand() % strlen(upper)];
                break;
            case 1:
                pass.password[i] = lower[rand() % strlen(lower)];
                break;
            case 2:
                pass.password[i] = digits[rand() % strlen(digits)];
                break;
            case 3:
                pass.password[i] = symbols[rand() % strlen(symbols)];
                break;
        }
    }
    pass.password[PASSWORD_LENGTH] = '\0'; // Null-terminate
    printf("Generated password: %s\n", pass.password);
}

// Test the strength of the provided password
static void test_password_length(const char *password) {
    if (strlen(password) > PASSWORD_LENGTH) {
        fprintf(stderr, "ERROR: Your password length is out of bounds, "
                        "Please enter a password within %d characters. \n", PASSWORD_LENGTH);
        exit(EXIT_FAILURE);
    }

    printf("********** Password Validation **********\n");
    printf("Entered password: %s\n", password);

    PasswordProperties props = analyze_password(password);
    PasswordResult result = evaluate_password(&props);

    printf("Your password strength is %s\n", password_strength_str(result.strength));
    printf("Length of the password: %ld\n", strlen(password));
    printf("Password score is: %d\n", result.score);

    if (result.score < MAX_SCORE) {
        printf(">>>>>>>>>>>>>> Your password must satisfy these conditions <<<<<<<<<<<<<<\n");
        printf("\t[*] Your password must be a minimum of %d characters...\n", MIN_PASSWORD_LENGTH);
        printf("\t[*] Your password must have at least %d uppercase character(s)...\n", MIN_UPPERCASE);
        printf("\t[*] Your password must have at least %d lowercase character(s)...\n", MIN_LOWERCASE);
        printf("\t[*] Your password must have at least %d special character(s)...\n", MIN_SPECIALCHAR);
        printf("\t[*] Your password must have at least %d digit(s)...\n", MIN_DIGIT);
    }
}

// Analyze the properties of a password
static PasswordProperties analyze_password(const char *password) {
    PasswordProperties props = {0};
    size_t i;

    strcpy(props.password, password);

    for (i = 0; i < strlen(password); i++) {
        if (isupper((unsigned char)password[i])) {
            props.uppercase++;
        } else if (islower((unsigned char)password[i])) {
            props.lowercase++;
        } else if (isdigit((unsigned char)password[i])) {
            props.digit++;
        } else {
            props.specialchar++;
        }
    }

    props.sequence_detected = is_sequence(password);
    return props;
}

// Evaluate the strength of a password based on its properties
static PasswordResult evaluate_password(const PasswordProperties *props) {
    PasswordResult result = {0};

    int range = 0;
    if (props->uppercase >= MIN_UPPERCASE) {
        range += 2;
    }
    if (props->lowercase >= MIN_LOWERCASE) {
        range += 2;
    }
    if (props->digit >= MIN_DIGIT) {
        range += 2;
    }
    if (props->specialchar >= MIN_SPECIALCHAR) {
        range += 2;
    }
    if (strlen(props->password) >= MIN_PASSWORD_LENGTH) {
        range += 2; // Ensure minimum length requirement is met
    }

    result.score = range;
    if (range < 7) {
        result.strength = STRONG; // Adjusted for higher threshold
    } else if (range >= 7 && range < MAX_SCORE) {
        result.strength = STRONG;
    } else if (range == MAX_SCORE) {
        result.strength = STRONGEST;
    } else {
        result.strength = WEAK; // Default to weaker strength if score calculation fails
    }
    return result;
}

// Check if there is a sequence of consecutive numbers in the password
static int is_sequence(const char *password) {
    int seq_count = 0;
    size_t i;

    for (i = 1; i < strlen(password); i++) {
        if (isdigit((unsigned char)password[i]) && isdigit((unsigned char)password[i - 1])) {
            if ((password[i] == password[i - 1] + 1) || (password[i] == password[i - 1] - 1)) {
                seq_count++;
                if (seq_count >= SEQUENCE_THRESHOLD) {
                    return 1;
                }
            } else {
                seq_count = 0;
            }
        }
    }
    return 0;
}

// Convert PasswordStrength enum to string representation
static const char* password_strength_str(PasswordStrength strength) {
    switch (strength) {
        case WEAKEST:
            return "weakest";
        case WEAK:
            return "weak";
        case AVERAGE:
            return "average";
        case MEDIUM:
            return "medium";
        case STRONG:
            return "strong";
        case STRONGEST:
            return "strongest";
        default:
            return "unknown";
    }
}
