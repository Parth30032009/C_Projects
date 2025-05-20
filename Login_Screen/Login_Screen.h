#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

// Libraries
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Constants for string lengths
#define MAX_PHONE_LEN 10
#define MAX_NAME_LEN 20
#define MAX_PASS_LEN 99
#define DOB_LEN 10\
// Labels
#define LABEL_ID "ID: "
#define LABEL_NAME "Name: "
#define LABEL_GENDER "Gender: "
#define LABEL_DOB "Date of Birth: "
#define LABEL_PHONE "Phone Number: "
#define LABEL_PASSWORD "Password: "

/**
 * @brief User structure to store user information
 * 
 * All string fields are dynamically allocated and should be freed when no longer needed
 */
typedef struct 
{
    int id;                 ///< Unique identifier for the user
    char *name;            ///< User's name (max length: MAX_NAME_LEN)
    char *phone;           ///< User's phone number (max length: MAX_PHONE_LEN)
    char gender;           ///< User's gender ('M' or 'F')
    char *DOB;             ///< Date of birth in DD/MM/YYYY format
    char *pass;            ///< User's password (max length: MAX_PASS_LEN)
} User;

/**
 * @brief Changes terminal ECHO settings
 * @param echo 0 for ECHO OFF, 1 for ECHO ON
 */
void term_ECHO(int echo);

/**
 * @brief Prints a divider line
 * @param div Character to use for the divider
 */
void divider(char div);

/**
 * @brief Saves user data to file
 * @param person User structure containing the data to save
 */
int genrate_ID();

void saveUser(User person);

/**
 * @brief Displays and handles the main menu
 */
void menu();

/**
 * @brief Handles the sign up process
 */
void signUp();

/**
 * @brief Handles the login process
 */
void login();

/**
 * @brief Verifies user credentials
 * @param name Username to verify
 * @param password Password to verify
 * @return true if credentials are valid, false otherwise
 */
bool verifyUser(char *name, char *password);

#endif /* LOGIN_SCREEN_H */