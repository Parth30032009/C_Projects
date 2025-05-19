
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
    FILE *file = fopen("users.txt", "a");
    if (file == NULL)
    {
        printf("File could not be opened");
    }
    fwrite(person.name, sizeof(char), strlen(person.name), file);
    fwrite("\n", sizeof(char), 1, file);
    fwrite(&person.gender, sizeof(char), 1, file);
    fwrite("\n", sizeof(char), 1, file);
    fwrite(person.DOB, sizeof(char), strlen(person.DOB), file);
    fwrite("\n", sizeof(char), 1, file);
    fwrite(person.phone, sizeof(char), strlen(person.phone), file);
    fwrite("\n", sizeof(char), 1, file);
    fwrite(person.pass, sizeof(char), strlen(person.pass), file);
    fwrite("\n", sizeof(char), 1, file);

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

}