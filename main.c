#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNumber;
    char accHolderName[50];
    float balance;
};

void createAccount() {
    struct Account newAccount;
   
    printf("Enter account number: ");
    scanf("%d", &newAccount.accNumber);
   
    printf("Enter account holder name: ");
    scanf("%s", newAccount.accHolderName);
   
    newAccount.balance = 0.0;
   
    FILE *file = fopen("accounts.dat", "ab");
    if (file == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }
   
    fwrite(&newAccount, sizeof(struct Account), 1, file);
    fclose(file);
   
    printf("Account created successfully!\n");
}

void deposit() {
    int accNumber;
    float amount;
   
    printf("Enter account number: ");
    scanf("%d", &accNumber);
   
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
   
    FILE *file = fopen("accounts.dat", "rb+");
    if (file == NULL) {
        printf("Error: Unable to open file for reading and writing.\n");
        return;
    }
   
    struct Account account;
    int found = 0;
   
    while (fread(&account, sizeof(struct Account), 1, file) == 1) {
        if (account.accNumber == accNumber) {
            account.balance += amount;
            fseek(file, -sizeof(struct Account), SEEK_CUR);
            fwrite(&account, sizeof(struct Account), 1, file);
            found = 1;
            printf("Deposit successful!\n");
            break;
        }
    }
   
    fclose(file);
   
    if (!found) {
        printf("Error: Account not found.\n");
    }
}

void withdraw() {
    int accNumber;
    float amount;
   
    printf("Enter account number: ");
    scanf("%d", &accNumber);
   
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
   
    FILE *file = fopen("accounts.dat", "rb+");
    if (file == NULL) {
        printf("Error: Unable to open file for reading and writing.\n");
        return;
    }
   
    struct Account account;
    int found = 0;
   
    while (fread(&account, sizeof(struct Account), 1, file) == 1) {
        if (account.accNumber == accNumber) {
            if (account.balance >= amount) {
                account.balance -= amount;
                fseek(file, -sizeof(struct Account), SEEK_CUR);
                fwrite(&account, sizeof(struct Account), 1, file);
                found = 1;
                printf("Withdrawal successful!\n");
            } else {
                printf("Error: Insufficient funds.\n");
            }
            break;
        }
    }
   
    fclose(file);
   
    if (!found) {
        printf("Error: Account not found.\n");
    }
}

void checkBalance() {
    int accNumber;
   
    printf("Enter account number: ");
    scanf("%d", &accNumber);
   
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }
   
    struct Account account;
    int found = 0;
   
    while (fread(&account, sizeof(struct Account), 1, file) == 1) {
        if (account.accNumber == accNumber) {
            printf("Account Holder: %s\n", account.accHolderName);
            printf("Account Balance: %.2f\n", account.balance);
            found = 1;
            break;
        }
    }
   
    fclose(file);
   
    if (!found) {
        printf("Error: Account not found.\n");
    }
}

void displayAllAccounts() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }
   
    struct Account account;
   
    printf("All Accounts:\n");
    printf("Acc Number\tHolder Name\tBalance\n");
   
    while (fread(&account, sizeof(struct Account), 1, file) == 1) {
        printf("%d\t\t%s\t\t%.2f\n", account.accNumber, account.accHolderName, account.balance);
    }
   
    fclose(file);
}

int main() {
    int choice;
   
    do {
        printf("\nBank Management System\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Display All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
       
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                displayAllAccounts();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
   
    return 0;
}