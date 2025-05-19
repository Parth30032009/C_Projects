#ifndef BASIC_H
#define BASIC_H

// Libraries
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PHONE_LEN 10
#define MAX_NAME_LEN 20
#define MAX_PASS_LEN 99
#define DOB_LEN 10

typedef struct 
{
    int id;
    char *name;
    char *phone;
    char gender;
    char *DOB;
    char *pass;
} User;

/* 
    changes terminal ECHO settings
    ARGUMENTS-:
    0 = ECHO OFF
    1 = ECHO ON
 */
void term_ECHO(int echo);
void divider(char div);
void saveUser(User person);
void menu();
void signUp();
void login();

#endif