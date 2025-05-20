#include "Login_Screen.h"


int main()
{
    divider('-');
    menu();
    divider('-');

    return 0;
}


// Functions

void term_ECHO(int echo)
{
    struct termios oldt, newt;
    
    if (!echo)
    {
        // Turn echoing off and save old terminal settings
        tcgetattr(STDIN_FILENO, &oldt);           // Get current terminal settings
        newt = oldt;
        newt.c_lflag &= ~(ECHO);                  // Disable echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Apply new settings        
    }
    else
    {
        // Restore terminal settings (turn echo back on)
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

void divider(char div)
{
    printf("\n\t");
    for (int i = 0; i < 50; i++)
    {
        printf("%c", div);
    }
    printf("\t\n");
}

int generate_ID()
{
    int random = rand();
    return random;
}

void menu()
{
    printf("\n\t********************\tMENU\t**********************\t\n");
    printf("SELECT THE OPTION\n");
    printf("1: Sign Up\n");
    printf("2: Login\n");

    int num;
    scanf("%i", &num);
    // Clear input buffer
    while (getchar() != '\n');

    switch (num)
    {
    case 1:
        signUp();  // Fixed typo in function name
        break;
    case 2:
        login();
        break;
    default:
        printf("Option not found. Rerun to Try again");
        break;
    }
}

void saveUser(User person)
{
    int id = generate_ID();
    FILE *file = fopen("users.txt", "a");
    if (file == NULL)
    {
        printf("File could not be opened");
    }
    // Write each field with its label
    fprintf(file, "\n%s%d\n", LABEL_ID, id);
    fprintf(file, "%s%s\n", LABEL_NAME, person.name);
    fprintf(file, "%s%c\n", LABEL_GENDER, person.gender);
    fprintf(file, "%s%s\n", LABEL_DOB, person.DOB);
    fprintf(file, "%s%s\n", LABEL_PHONE, person.phone);
    fprintf(file, "%s%s\n", LABEL_PASSWORD, person.pass);

    fclose(file);     
}

void signUp()
{
    User person;
    person.name = (char *)malloc(MAX_NAME_LEN + 1);
    person.pass = (char *)malloc(MAX_PASS_LEN + 1);
    person.DOB = (char *)malloc(DOB_LEN + 1);
    person.phone = (char *)malloc(MAX_PHONE_LEN + 1);
    
    printf("Enter Your Name: ");
    fgets(person.name, MAX_NAME_LEN + 1, stdin);
    person.name[strcspn(person.name, "\n")] = 0;

    printf("Choose Gender:\t");
    printf("M: Male\tF: Female\n");
    scanf(" %c", &person.gender);
    person.gender = toupper(person.gender);
    while (getchar() != '\n' && getchar() != EOF);  // Clear input buffer

    printf("Date Of Birth (DD/MM/YYYY): ");
    fgets(person.DOB, DOB_LEN + 1, stdin);
    person.DOB[strcspn(person.DOB, "\n")] = 0;

    printf("Contact Number: ");
    while (getchar() != '\n' && getchar() != EOF);  // Clear input buffer
    fgets(person.phone, MAX_PHONE_LEN + 1, stdin);
    person.phone[strcspn(person.phone, "\n")] = 0;

    printf("Create Password: ");
    // Turning OFF Echo for password
    term_ECHO(0);
    while (getchar() != '\n' && getchar() != EOF);  // Clear input buffer
    fgets(person.pass, MAX_PASS_LEN + 1, stdin);
    person.pass[strcspn(person.pass, "\n")] = 0;

    // Save the user data to a file
    saveUser(person);

    printf("\nSign up successful!\n");
}

void login()
{
    char *name = (char *)malloc(MAX_NAME_LEN + 1);
    char *password = (char *)malloc(MAX_PASS_LEN + 1);
    printf("Username: ");
    fgets(name, MAX_NAME_LEN + 1, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Password: ");
    // Turning OFF Echo
    // term_ECHO(0);
    fgets(password, MAX_PASS_LEN + 1, stdin);
    password[strcspn(password, "\n")] = 0;
    // term_ECHO(1);
    if(verifyUser(name, password))
    {
        printf("Login Successful");
    }
    else
    {
        printf("User not found");
    }
}

bool verifyUser(char *name, char *password)
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("File could not be found");
        return false;
    }

    char *file_name = (char *)malloc(MAX_NAME_LEN);
    char *file_pass = (char *)malloc(MAX_PASS_LEN);
    char *line = (char *)malloc(256);
    while (fgets(line, 256, file))
    {
        if (strncmp(line, LABEL_NAME, strlen(LABEL_NAME)) == 0)
        {   
            strcpy(file_name, line + strlen(LABEL_NAME));
            file_name[strcspn(file_name, "\n")] = 0;
            
        }
        else if (strncmp(line, LABEL_PASSWORD, strlen(LABEL_PASSWORD)) == 0)
        {
            strcpy(file_pass, line + strlen(LABEL_PASSWORD));
            file_pass[strcspn(file_pass, "\n")] = 0;
        }
        //Check if found a match
        if (strcmp(name, file_name) == 0 && strcmp(password, file_pass) == 0)
        {
            free(file_name);
            free(file_pass);
            free(line);
            fclose(file);
            return true;
        }
    }   

    free(file_name);
    free(file_pass);
    free(line);
    fclose(file);
    return false;

}