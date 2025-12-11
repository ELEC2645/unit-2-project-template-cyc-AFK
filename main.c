#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcs.h"

static void main_menu(void);             // Main menu handler          
static void print_main_menu(void);       // Print Main Menu Function  
static int  get_user_input(void);        // Get and validate the menu option entered by the user   
static void select_menu_item(int input); // Select the corresponding function based on user input
static void go_back_to_main(void);       // Waiting for user input to return to the main menu  
static int  is_integer(const char* s);   // Determine whether a string is an integer

/**
 * Main function, program entry point
 * Continuously display the main menu through an infinite loop and handle user operations
 */
int main(void)
{
    for (;;) {  // Keep the program running until the user chooses to exit
        main_menu();
    }
    return 0;
}

/**
 * Main Menu Handler
 * The process of coordinating the display menu, obtaining user input, and executing the corresponding functions
 */
static void main_menu(void)
{
    print_main_menu();
    {
        int input = get_user_input();
        select_menu_item(input);
    }
}

/**
 * Get and validate the menu option entered by the user
 * Make sure the user enters an integer between 1 and 5; otherwise, prompt them to enter it again.
 * Return value: a valid menu option (1-5)
 */
static int get_user_input(void)
{
    enum { MENU_ITEMS = 5 };// Total number of menu options (5 options in total, from 1 to 5)
    char buf[128];          // Buffer for storing user input
    int valid_input = 0;    // Flag indicating whether the input is valid (0: invalid, 1: valid)
    int value = 0;          // Store converted integer options

    do {
        printf("\nPlease select a function option:");
        // Read user input, and exit the program if reading fails
        if (!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error, program exiting.");
            exit(1);
        }

        // Verify that the input is a positive number
        buf[strcspn(buf, "\r\n")] = '\0';

        // Verify whether the input is an integer
        if (!is_integer(buf)) {
            printf("Please enter an integer!\n");
            valid_input = 0;
        }
        else {
            value = (int)strtol(buf, NULL, 10);
            if (value >= 1 && value <= MENU_ITEMS) {
                valid_input = 1;
            }
            else {
                printf("Invalid menu option!\n");
                valid_input = 0;
            }
        }
    } while (!valid_input);// Keep looping until the input is valid

    return value;
}

/**
 * Select the corresponding function based on user input
 * input - The menu option entered by the user (1-5)
 * Call the matrix operation function for the selected option, or exit the program
 */
static void select_menu_item(int input)
{
    switch (input) {
    case 1:
        matrix_addition(); 
        go_back_to_main(); 
        break;
    case 2:
        matrix_multiplication(); 
        go_back_to_main();
        break;
    case 3:
        matrix_transpose();
        go_back_to_main();
        break;
    case 4:
        matrix_determinant(); 
        go_back_to_main();
        break;
    default:  // Option 5 (Exit Program)
        printf("bye!\n");
        exit(0);
    }
}

/**
 * Print main menu
 * Display all matrix operation options supported by the program
 */
static void print_main_menu(void)
{
    printf("\n----------- matrix -----------\n");
    printf("\n"
        "\t1. Matrix Addition\t\t\n"
        "\t2. Matrix Multiplication\t\n"
        "\t3. Matrix Transpose\t\n"
        "\t4. Determinant Calculation (2nd/3rd Order)\t\n"
        "\t5. Exit\t\t\n");
    printf("---------------matrix------------\n");
}

/**
 * Waiting for user input to return to the main menu
 * Ensure that the main menu is only returned after the user enters 'b' or 'B'; for any other input, prompt to re-enter.
 */
static void go_back_to_main(void)
{
    char buf[64];
    do {
        printf("\nPlease enter 'b' or 'B' to return to the main menu:");
        if (!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error, program exiting.");
            exit(1);
        }
        buf[strcspn(buf, "\r\n")] = '\0';
    } while (!(buf[0] == 'b' || buf[0] == 'B') || buf[1] != '\0');
}

/**
 * Determine whether a string is an integer
 * Parameter: s - the string to be evaluated
 * Return value: 1 indicates it is an integer, 0 indicates it is not
 * Supports positive and negative integers, but empty strings or non-numeric characters are not allowed
 */
static int is_integer(const char* s)
{
    if (!s || !*s) return 0;

    // Skip the plus or minus sign (if present)
    if (*s == '+' || *s == '-') s++;

    // A number must follow the symbol
    if (!isdigit((unsigned char)*s)) return 0;

    
    // Check if the remaining characters are all digits
    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}