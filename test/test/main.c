//
//  main.c
//  test
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

Account *ReadAccount(Account *acc)
{
    char username[30];
    char password[30];
    int status;
    numAccount = 0;
    FILE *inp = fopen("/Users/kynguyen/Documents/WorkSpace/TH-lap-trinh-mang/test/account.txt", "r");
    if (!inp)
    {
        printf("Error: Can't open this file! \n");
        return NULL;
    }else {
        printf("Ok");
    }
    fclose(inp);
    return acc;
}



int main() {
    Account *acc = NULL;
    acc = ReadAccount(acc);
    return 1;
}
