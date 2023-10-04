//
//  main.c
//  TH-lap-trinh-mang
//
//  Created by Kỳ Nguyễn on 28/09/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Account
{
    char username[30];
    char password[30];
    int status;
    int isSignIn;
    struct Account *next;

} Account;

int numAccount;
const char MSSV[] = "20204995";

Account *CreateNewAccount(char *username, char *password, int status);
Account *AddAccount(Account *account, char *username, char *password, int status);
int CheckUser(Account *account, char *username);
int CheckPassword(Account *account, char *password);
int CheckBlocked(Account *account, char *username);
void CheckSignIn(Account *account, char *username);
Account *ReadAccount(Account *account);
Account *Register(Account *account);
void UpdateFile(Account *account);
void SignIn(Account *account);
void Search(Account *account);
void SignOut(Account *account);
void freeList(Account *account);
void ActivateAccount(Account *account);
void ChangePassword(Account *account);

int main()
{
    int menu;
    Account *acc = NULL;
    acc = ReadAccount(acc);
    while (1 == 1)
    {
        printf("\nUSER MANAGEMENT PROGRAM\n");
        printf("\n");
        printf("1. Register\n");
               printf("2. Activate\n");
               printf("3. Sign in\n");
               printf("4. Search\n");
               printf("5. Change password\n");
               printf("6. Sign out\n");
               printf("Your choice (1-6, other to quit): ");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            acc = Register(acc);
            break;
        case 2:
            ActivateAccount(acc);
            break;
        case 3:
            SignIn(acc);
            break;
        case 4:
            Search(acc);
            break;
        case 5:
            ChangePassword(acc);
            break;
        case 6:
            SignOut(acc);
            break;
        default:
            freeList(acc);
            exit(0);
        }
    }
}

Account *CreateNewAccount(char *username, char *password, int status)
{
    Account *p = (Account *)malloc(sizeof(Account));
    strcpy(p->username, username);
    strcpy(p->password, password);
    p->status = status;
    p->isSignIn = 0;
    p->next = NULL;
    return p;
}

Account *AddAccount(Account *account, char *username, char *password, int status)
{
    if (account == NULL)
    {
        Account *temp = CreateNewAccount(username, password, status);
        return temp;
    }
    else
    {
        if (CheckUser(account, username))
        {
            Account *cur = account;
            while (cur->next != NULL)
            {
                cur = cur->next;
            }
            Account *temp = CreateNewAccount(username, password, status);
            cur->next = temp;
            return account;
        }
        else
        {
            return NULL;
        }
    }
}



void changeStatus(Account *account, char *username, int status)
{
    if (status == 0)
    {
        printf("Password is incorrect. Account is blocked\n");
    }
    Account *cur = account;
    while (cur != NULL)
    {
        if (strcmp(cur->username, username) == 0)
        {
            cur->status = status;
            return;
        }
        cur = cur->next;
    }
}

void ActivateAccount(Account *acc)
{
    printf("----Welcome to Activate function.----\n");
    char username[30];
    char password[30];
    char code[30];
    int n = 4;

    printf("Username: ");
    scanf("%s", username);

    if (CheckUser(acc, username) != 0)
    {
        printf("Cannot find account\n");
        return;
    }
    if (CheckBlocked(acc, username) == 0)
    {
        printf("Account is blocked\n");
        return;
    }
    else if (CheckBlocked(acc, username) == 1)
    {
        printf("Account is already activated\n");
        return;
    }

    printf("Password: ");
    scanf("%s", password);

    if (CheckPassword(acc, password) != 0)
    {
        printf("Password is incorrect\n");
        return;
    }

    while (n > 0)
    {
        printf("Code: ");
        scanf("%s", code);

        if (strcmp(code, MSSV) == 0)
        {
            changeStatus(acc, username, 1);
            UpdateFile(acc);
            printf("Account is activated\n");
            return;
        }
        else
        {
            printf("Account is not activated\n");
            n--;
        }
    }
    changeStatus(acc, username, 0);

    UpdateFile(acc);
    
}

void ChangePassword(Account *acc)
{
    printf("Welcome to ChangePassword\n");
    char username[30];
    char password[30];
    char newPassword[30];

    printf("Username: ");
    scanf("%s", username);

    if (CheckUser(acc, username) != 0)
    {
        printf("Cannot find account\n");
        return;
    }

    printf("Password: ");
    scanf("%s", password);

    if (CheckPassword(acc, password) != 0)
    {
        printf("Current password is incorrect. Please try again\n");
        return;
    }
    printf("NewPassword: ");
    scanf("%s", newPassword);

    Account *cur = acc;
    while (cur != NULL)
    {
        if (strcmp(cur->username, username) == 0)
        {
            strcpy(cur->password, newPassword);
        }
        cur = cur->next;
    }
    printf("Password is changed\n");

    UpdateFile(acc);
    return;
}


int CheckUser(Account *account, char *username)
{
    Account *cur = account;
    while (cur != NULL)
    {
        if (strcmp(cur->username, username) == 0)
        {
            return 0;
        }
        cur = cur->next;
    }
    return 1;
}

int CheckPassword(Account *account, char *password)
{
    Account *cur = account;
    while (cur != NULL)
    {
        if (strcmp(cur->password, password) == 0)
        {
            return 0;
        }
        cur = cur->next;
    }
    return 1;
}

int CheckBlocked(Account *account, char *username)
{
    Account *cur = account;
    while (cur != NULL)
    {
        if (strcmp(cur->username, username) == 0)
        {
            return cur->status;
        }
        cur = cur->next;
    }
    return 1;
}

void CheckSignIn(Account *account, char *username)
{
    Account *cur = account;
    while (cur != NULL)
    {
        if (strcmp(cur->username, username) == 0)
        {
            if (cur->isSignIn == 0)
            {
                printf("This account is not signed in! \n");
            }
            else
            {
                printf("Sign out is sucessful! \n");
                cur->isSignIn = 0;
            }
            return;
        }
        cur = cur->next;
    }
}

Account *ReadAccount(Account *acc)
{
    char username[30];
    char password[30];
    int status;
    numAccount = 0;
    FILE *inp = fopen("/Users/kynguyen/Documents/WorkSpace/TH-lap-trinh-mang/TH-lap-trinh-mang/account.txt", "r");
    if (!inp)
    {
        printf("Error: Can't open this file! \n");
        return NULL;
    }

    do
    {
        if (fscanf(inp, "%s %s %d", username, password, &status) > 0)
        {
            acc = AddAccount(acc, username, password, status);
            numAccount++;
        }
        else
            break;
    } while (1 == 1);
    fclose(inp);
    return acc;
}

Account *Register(Account *acc)
{
    printf("Welcome to Register\n");

    char username[30];
    char password[30];
    printf("Input your Username: ");
    scanf("%s", username);
    if (CheckUser(acc, username) != 0)
    {
        printf("Input your Password: ");
        scanf("%s", password);
        acc = AddAccount(acc, username, password, 2);
        numAccount++;
        printf("Successful registration. \n");
        UpdateFile(acc);
    }
    else
    {
        printf("This account existed! \n");
    }
    return acc;
}

void UpdateFile(Account *acc)
{
    FILE *inp = fopen("/Users/kynguyen/Documents/WorkSpace/TH-lap-trinh-mang/TH-lap-trinh-mang/account.txt", "w");
    Account *cur = acc;
    while (cur != NULL)
    {
        fprintf(inp, "%s %s %d\n", cur->username, cur->password, cur->status);
        cur = cur->next;
    }
    fclose(inp);
}

void SignIn(Account *acc)
{
    printf("Welcome to SignIn\n");
    char username[30];
    char password[30];

    int n = 3;
    printf("Input your Username: ");
    scanf("%s", username);
    if (CheckUser(acc, username) != 0)
    {
        printf("Cannot find account \n");
        return;
    }
    else
    {
        if (CheckBlocked(acc, username) == 0)
        {
            printf("Tài khoản của bạn đã bị khoá\n");
            return;
        }
        else
        {
            while (n > 0)
            {
                printf("Input your Password: ");
                scanf("%s", password);
                if (CheckPassword(acc, password) != 0)
                {
                    printf("Password is incorrect!\n");
                    n--;
                }
                else
                {
                    printf("Sign in is successful\n");
                    Account *cur = acc;
                    while (cur != NULL)
                    {
                        if (strcmp(cur->username, username) == 0)
                        {
                            cur->isSignIn = 1;
                        }
                        cur = cur->next;
                    }
                    return;
                }
            }
            printf("This account is blocked!\n");
            Account *cur = acc;
            while (cur != NULL)
            {
                if (strcmp(cur->username, username) == 0)
                {
                    cur->status = 0;
                }
                cur = cur->next;
            }
            UpdateFile(acc);
            return;
        }
    }
}

void Search(Account *acc)
{
    printf("Welcome to Search function\n");
    char username[30];

    printf("Input your Username: ");
    scanf("%s", username);
    if (CheckUser(acc, username) != 0)
    {
        printf("Account does not exist!\n");
    }
    else
    {
        if (CheckBlocked(acc, username) == 0)
        {
            printf("Account is blocked!\n");
        }
        else
        {
            printf("Account is active!\n");
        }
    }
    return;
}

void SignOut(Account *acc)
{
    printf("Welcome to SignOut function\n");
    char username[30];

    printf("Input your Username: ");
    scanf("%s", username);
    if (CheckUser(acc, username) != 0)
    {
        printf("Account does not exist!\n");
    }
    else
    {
        CheckSignIn(acc, username);
    }
}

void freeList(Account *head)
{
    Account *tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
