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

#define PASSWORD_LENGTH 14

// Function declarations
void print_help();
void generate_password();
int check_password(char *password);
int is_sequence(char *password);

int main(int argc, char *argv[]){

    // Check if there are enough arguments
    if(argc < 2){
        printf("Usage: %s [-h]  [-g]  [-t <password>]\n", argv[0]);
        print_help();
        return 1;
    }

    // Check if the first argument is "-h" for help "-g" for generate password and "-t <password>" for test a password 
    if(strcmp(argv[1], "-h") == 0){
        print_help();
    } else if(strcmp(argv[1], "-g") == 0){
        generate_password();
    } else if(strcmp(argv[1], "-t") == 0){
        // Ensure there is a second argument (the password)
        if(argc != 3){
            printf("Usage: %s -t <password>\n", argv[0]);
            return 1;
        }
        // Validate password
        char *password = argv[2];
        if(strlen(password) > PASSWORD_LENGTH){
            perror("Error: Your password length is out of bounds. Please enter a password within 15 characters.\n");
            exit(EXIT_FAILURE);
            return 1;
        }
        printf("**********Password Validation**********\n");
        printf("Entered password: %s\n", password);

        int score = check_password(password);
        // Print the strength of the password based on its score
        if (score == 0) {
            printf("Your password is weakest\n");
        } else if (score > 0 && score < 3) {
            printf("Your password is weak\n");
        } else if (score > 2 && score < 5) {
            printf("Your password is average\n");
        } else if (score > 4 && score < 7) {
            printf("Your password is medium\n");
        } else if (score > 6 && score < 9) {
            printf("Your password is strong\n");
        } else if (score == 9) {
            printf("Your password is strongest\n");
        }

        printf("Length of the password: %ld\n", strlen(password));
        printf("Password score is: %d\n", score);

        // If the password is not strongest, print conditions for a strong password
        if (score < 8) {
            printf(">>>>>>>>>>>>>>Your password must have satisfied under these conditions<<<<<<<<<<<<<<\n");
            printf("\t[*]Your password must be minimum of 8 characters...\n");
            printf("\t[*]Your password must have one uppercase character...\n");
            printf("\t[*]Your password must have three lowercase characters...\n");
            printf("\t[*]Your password must have one symbol...\n");
            printf("\t[*]Your password must have three numeric characters...\n");
        }
    } else {
        printf("Invalid option. Use -h for help.\n");
    }

    return 0;
}

// Function to print the help message
void print_help(){

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

    printf("\n\t\t\t\tV-1.0 for Linux\n");

    printf("Options: \n");
    printf("\t\t-h                  Show this help message and exit\n");
    printf("\t\t-g                  Generate a strong password\n");
    printf("\t\t-t <password>       Test the strength of the provided password\n");
}

// Function to generate a random strong password
void generate_password(){
    char password[PASSWORD_LENGTH + 1];
    const char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lower[] = "abcdefghijklmnopqrstuvwxyz";
    const char digits[] = "0123456789";
    const char symbols[] = "!@#$&*()_+|";
    int i, index;

     srandom(time(NULL));

    // Ensure at least one character from each category is present
    password[0] = upper[random() % strlen(upper)];
    password[1] = lower[random() % strlen(lower)];
    password[2] = digits[random() % strlen(digits)];
    password[3] = symbols[random() % strlen(symbols)];

    // Fill the remaining characters
    for (i = 4; i < PASSWORD_LENGTH; i++) {
        index = random() % 4;
        if (index == 0) {
            password[i] = upper[random() % strlen(upper)];
        } else if (index == 1) {
            password[i] = lower[random() % strlen(lower)];
        } else if (index == 2) {
            password[i] = digits[random() % strlen(digits)];
        } else {
            password[i] = symbols[random() % strlen(symbols)];
        }
    }
    password[PASSWORD_LENGTH] = '\0'; // Null-terminate the password

    printf("Generated password: %s\n", password);
}

// Function to check the strength of the password
int check_password(char *password) {
    int uppercase = 0, lowercase = 0, specialchar = 0, digit = 0;
    int sequenceDetected = is_sequence(password);

    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) {
            uppercase++;
        } else if (islower(password[i])) {
            lowercase++;
        } else if (isdigit(password[i])) {
            digit++;
        } else {
            specialchar++;
        }
    }

    int range = 0;
    if (strlen(password) >= 8) {
        range = 1;
    }
    if (uppercase >= 1) {
        range += 2;
    }
    if (lowercase >= 3) {
        range += 2;
    }
    if (digit >= 3) {
        range += 2;
    }
    if (specialchar >= 1) {
        range += 2;
    }

    if (sequenceDetected) {
        printf("Your password contains a sequence of numbers, So please use unsequence order of numbers.\n");
        range -= 1;
    }

    return range;
}

// Function to check if there is a sequence of consecutive numbers in the password
int is_sequence(char *password) {
    int seq_count = 0;

    for (int i = 1; i < strlen(password); i++) {
        if (isdigit(password[i]) && isdigit(password[i - 1])) {
            if ((password[i] == password[i - 1] + 1) || (password[i] == password[i - 1] - 1)) {
                seq_count++;
                if (seq_count >= 2) {
                    return 1;
                }
            } else {
                seq_count = 0;
            }
        }
    }
    return 0;
}
