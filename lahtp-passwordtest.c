/*
 * LAHTP-PASSWORDTEST tool V1.0.3
 *
 * 1. Test your password strength
 * 2. Generate strong password
 *
 * This tool helps you to test your input password and
 * validate whether your password is weak or weakest or
 * medium or strong or strongest and rate your password
 * score with their corresponding strength.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

/* Constants */
#define password_length 16
#define min_password_length 8
#define min_uppercase 2
#define min_lowercase 3
#define min_digit 3
#define min_specialchar 2
#define sequence_threshold 2
#define max_score 10
#define max_input_length 256

/* Terminal colors */
#define red "\e[0;31m"
#define bgrn "\e[1;32m"
#define byel "\e[1;33m"
#define yel "\e[0;33m"
#define bblu "\e[1;34m"
#define bmag "\e[1;35m"
#define bcyn "\e[1;36m"
#define bwht "\e[1;37m"
#define reset "\e[0m"
#define c_weakest "\e[0;31m"
#define c_weak "\e[0;31m"
#define c_average "\e[1;33m"
#define c_medium "\e[1;33m"
#define c_strong "\e[1;32m"
#define c_strongest "\e[1;32m"

enum password_strength
{
        WEAKEST,
        WEAK,
        AVERAGE,
        MEDIUM,
        STRONG,
        STRONGEST
};

struct password_properties
{
        int uppercase;
        int lowercase;
        int digit;
        int specialchar;
        int sequence_detected;
};

struct password_result
{
        int score;
        enum password_strength strength;
};

static void print_help(void);
static void generate_password(void);
static void test_password_strength(const char *password);
static struct password_properties analyze_password(const char *password,
                                                   size_t length);
static struct password_result evaluate_password(
    const struct password_properties *props, size_t length);
static bool has_consecutive_sequence(const char *password, size_t length);
static const char *password_strength_str(enum password_strength strength);
static bool is_valid_input(const char *input);

int main(int argc, char *argv[])
{
        if (argc < 2)
        {
                fprintf(stderr, "%sUsage:%s %s %s[-h][--help] [-g][--gen] "
                                "[-t][--test]%s %s<password>%s\n",
                        red, reset, argv[0], byel, reset, bwht, reset);
                return EXIT_FAILURE;
        }

        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        {
                print_help();
        }
        else if (strcmp(argv[1], "-g") == 0 ||
                 strcmp(argv[1], "--gen") == 0)
        {
                generate_password();
        }
        else if (strcmp(argv[1], "-t") == 0 ||
                 strcmp(argv[1], "--test") == 0)
        {
                if (argc != 3)
                {
                        fprintf(stderr, "%sERROR: Please provide a password "
                                        "to test.%s\n",
                                red, reset);
                        return EXIT_FAILURE;
                }

                if (!is_valid_input(argv[2]))
                {
                        fprintf(stderr, "%sERROR: Invalid password input.%s\n",
                                red, reset);
                        return EXIT_FAILURE;
                }

                test_password_strength(argv[2]);
        }
        else
        {
                fprintf(stderr, "%sERROR: Unknown option%s %s'%s'%s.\n",
                        red, reset, byel, argv[1], reset);
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

static bool is_valid_input(const char *input)
{
        if (!input || strlen(input) > password_length)
                return false;

        for (size_t i = 0; i < strlen(input); i++)
        {
                if (!isprint((unsigned char)input[i]))
                        return false;
        }
        return true;
}

static void print_help(void)
{
        printf("%s", bgrn);
        printf("                                               __    ___    __  ____________                \n");
        printf("                                              / /   /   |  / / / /_  __/ __ \\              \n");
        printf("                                             / /   / /| | / /_/ / / / / /_/ /               \n");
        printf("                                            / /___/ ___ |/ __  / / / / ____/                \n");
        printf("     ____  ___   ___________       ______  /_____/_/_ |_/_/_/_/_/_/_/_/_________            \n");
        printf("    / __ \\/   | / ___/ ___/ |     / / __ \\/ __ \\/ __ \\  /_  __/ ____/ ___/_  __/        \n");
        printf("   / /_/ / /| | \\__ \\\\__ \\| | /| / / / / / /_/ / / / /   / / / __/  \\__ \\\\/ /        \n");
        printf("  / ____/ ___ |___/ /__/ /| |/ |/ / /_/ / _, _/ /_/ /   / / / /___ ___/ // /                \n");
        printf(" /_/   /_/  |_/____/____/ |__/|__/\\____/_/ |_/_____/___/_/_/_____//____//_/                \n");
        printf("                                                   /_  __/ __ \\/ __ \\/ /                  \n");
        printf("                                                    / / / / / / / / / /                     \n");
        printf("                                                   / / / /_/ / /_/ / /___                   \n");
        printf("                                                  /_/  \\____/\\____/_____/                 \n");
        printf("%s", reset);

        printf("\n %s                                  - 0xD4rkEYe %s\n",
               bmag, reset);
        printf("%sOptions:%s \n", bcyn, reset);
        printf("%s\t-h  --help%s                 %s Show this help message and exit%s\n",
               byel, reset, bgrn, reset);
        printf("%s\t-g  --gen%s                  %sGenerate a strong password%s\n",
               byel, reset, bgrn, reset);
        printf("%s\t-t  --test%s %s<password>%s       %sTest the strength of the provided password%s\n",
               byel, reset, bwht, reset, bgrn, reset);
}

static void generate_password(void)
{
        char password[password_length + 1] = {0};
        const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz"
                               "0123456789"
                               "!@#$-^&*()_+|<>{}";

        srand((unsigned int)time(NULL));

        for (size_t i = 0; i < password_length; i++)
        {
                int key = rand() % (int)(sizeof(charset) - 1);
                password[i] = charset[key];
        }
        password[password_length] = '\0';
        printf("%sGenerated password%s: %s%s%s\n", byel, reset, bgrn,
               password, reset);
}

static void test_password_strength(const char *password)
{
        if (!password)
        {
                fprintf(stderr, "%sERROR: Null password provided.%s\n",
                        red, reset);
                exit(EXIT_FAILURE);
        }

        size_t length = strlen(password);

        if (length >= password_length)
        {
                fprintf(stderr, "%s ERROR: Your password length is out of bounds.%s\n"
                                "%s Please enter a password within%s %s%d%s%s characters.%s\n",
                        red, reset, red, reset, byel, password_length,
                        reset, red, reset);
                exit(EXIT_FAILURE);
        }

        printf("%s********** Password Validation **********%s\n", bblu, reset);
        printf("%sEntered password%s: %s%s%s\n", bcyn, reset, bgrn,
               password, reset);

        struct password_properties props = analyze_password(password, length);
        struct password_result result = evaluate_password(&props, length);

        const char *color;
        switch (result.strength)
        {
        case WEAKEST:
                color = c_weakest;
                break;
        case WEAK:
                color = c_weak;
                break;
        case AVERAGE:
                color = c_average;
                break;
        case MEDIUM:
                color = c_medium;
                break;
        case STRONG:
                color = c_strong;
                break;
        case STRONGEST:
                color = c_strongest;
                break;
        default:
                color = reset;
                break;
        }

        printf("%sYour password strength is%s %s%s%s\n", bcyn, reset, color,
               password_strength_str(result.strength), reset);
        printf("%sLength of the password%s: %s%zu%s\n", bcyn, reset, byel,
               length, reset);
        printf("%sPassword score is%s: %s%d%s\n", bcyn, reset, byel,
               result.score, reset);

        if (props.sequence_detected)
        {
                printf("%s", yel);
                printf("Warning: A sequence of consecutive characters was "
                       "detected in the password.\n");
                printf("%s", reset);
        }

        printf("\n");
        if (result.score < max_score - 1)
        {
                printf("%s", red);
                printf(">>>>>>>>>>>>>> Your password must satisfy these "
                       "conditions <<<<<<<<<<<<<<\n");
                printf("\t[*] Your password must be a minimum of %d characters...\n",
                       min_password_length);
                printf("\t[*] Your password must have at least %d uppercase character(s)...\n",
                       min_uppercase);
                printf("\t[*] Your password must have at least %d lowercase character(s)...\n",
                       min_lowercase);
                printf("\t[*] Your password must have at least %d special character(s)...\n",
                       min_specialchar);
                printf("\t[*] Your password must have at least %d digit(s)...\n",
                       min_digit);
                printf("%s", reset);
        }
}

static struct password_properties analyze_password(const char *password,
                                                   size_t length)
{
        struct password_properties props = {0};

        if (!password || length == 0)
                return props;

        for (size_t i = 0; i < length; i++)
        {
                if (isupper((unsigned char)password[i]))
                {
                        props.uppercase++;
                }
                else if (islower((unsigned char)password[i]))
                {
                        props.lowercase++;
                }
                else if (isdigit((unsigned char)password[i]))
                {
                        props.digit++;
                }
                else if (isprint((unsigned char)password[i]))
                {
                        props.specialchar++;
                }
        }
        props.sequence_detected = has_consecutive_sequence(password, length);
        return props;
}

static struct password_result evaluate_password(
    const struct password_properties *props, size_t length)
{
        struct password_result result = {0};

        if (!props)
                return result;

        if (props->uppercase >= min_uppercase)
                result.score += 2;
        if (props->lowercase >= min_lowercase)
                result.score += 2;
        if (props->digit >= min_digit)
                result.score += 2;
        if (props->specialchar >= min_specialchar)
                result.score += 2;
        if (length >= min_password_length)
                result.score += 2;

        if (props->sequence_detected)
                result.score -= 1;

        if (result.score == max_score)
        {
                result.strength = STRONGEST;
        }
        else if (result.score >= 7)
        {
                result.strength = STRONG;
        }
        else
        {
                result.strength = MEDIUM;
        }

        return result;
}

static bool has_consecutive_sequence(const char *password, size_t length)
{
        if (!password || length < 2)
                return false;

        int seq_count = 0;

        for (size_t i = 1; i < length; i++)
        {
                if (isdigit((unsigned char)password[i]) &&
                    isdigit((unsigned char)password[i - 1]))
                {
                        if ((password[i] == password[i - 1] + 1) ||
                            (password[i] == password[i - 1] - 1))
                        {
                                seq_count++;
                                if (seq_count >= sequence_threshold)
                                        return true;
                        }
                        else
                        {
                                seq_count = 0;
                        }
                }
        }
        return false;
}

static const char *password_strength_str(enum password_strength strength)
{
        switch (strength)
        {
        case WEAKEST:
                return "Weakest";
        case WEAK:
                return "Weak";
        case AVERAGE:
                return "Average";
        case MEDIUM:
                return "Medium";
        case STRONG:
                return "Strong";
        case STRONGEST:
                return "Strongest";
        default:
                return "Unknown";
        }
}