#include <stdio.h>
#include <stdlib.h>

struct Bank {
    int accountNo;
    char name[50];
    float balance;
};

// 1. Create Account
void createAccount() {
    struct Bank b, temp;
    int found = 0;

    FILE *fp = fopen("bank.dat", "rb");

    printf("\nEnter Account Number: ");
    scanf("%d", &b.accountNo);

    if (fp != NULL) {
        while (fread(&temp, sizeof(temp), 1, fp)) {
            if (temp.accountNo == b.accountNo) {
                found = 1;
                break;
            }
        }
        fclose(fp);
    }

    if (found) {
        printf("Account Already Exists!\n");
        return;
    }

    printf("Enter Account Holder Name: ");
    scanf(" %49[^\n]", b.name);

    printf("Enter Opening Balance: ");
    scanf("%f", &b.balance);

    if (b.balance < 0) {
        printf("Invalid Balance!\n");
        return;
    }

    fp = fopen("bank.dat", "ab");

    if (fp == NULL) {
        printf("File Error!\n");
        return;
    }

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("Account Created Successfully!\n");
}

// 2. Display All Accounts
void displayAccounts() {
    struct Bank b;

    FILE *fp = fopen("bank.dat", "rb");

    if (fp == NULL) {
        printf("No Records Found!\n");
        return;
    }

    printf("\n----- BANK RECORDS -----\n");

    while (fread(&b, sizeof(b), 1, fp)) {
        printf("\nAccount Number: %d", b.accountNo);
        printf("\nAccount Holder: %s", b.name);
        printf("\nBalance: %.2f\n", b.balance);
    }

    fclose(fp);
}

// 3. Search Account
void searchAccount() {
    struct Bank b;
    int number, found = 0;

    FILE *fp = fopen("bank.dat", "rb");

    if (fp == NULL) {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &number);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.accountNo == number) {
            printf("\nAccount Found!");
            printf("\nName: %s", b.name);
            printf("\nBalance: %.2f\n", b.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account Not Found!\n");
    }

    fclose(fp);
}

// 4. Deposit Money
void depositMoney() {
    struct Bank b;
    int number, found = 0;
    float amount;

    FILE *fp = fopen("bank.dat", "rb+");

    if (fp == NULL) {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &number);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.accountNo == number) {
            printf("Enter Deposit Amount: ");
            scanf("%f", &amount);

            if (amount <= 0) {
                printf("Invalid Amount!\n");
            } else {
                b.balance += amount;

                fseek(fp, -(long)sizeof(b), SEEK_CUR);
                fwrite(&b, sizeof(b), 1, fp);

                printf("Money Deposited Successfully!\n");
                printf("New Balance: %.2f\n", b.balance);
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account Not Found!\n");
    }

    fclose(fp);
}

// 5. Withdraw Money
void withdrawMoney() {
    struct Bank b;
    int number, found = 0;
    float amount;

    FILE *fp = fopen("bank.dat", "rb+");

    if (fp == NULL) {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &number);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.accountNo == number) {
            printf("Enter Withdrawal Amount: ");
            scanf("%f", &amount);

            if (amount <= 0) {
                printf("Invalid Amount!\n");
            } else if (amount > b.balance) {
                printf("Insufficient Balance!\n");
            } else {
                b.balance -= amount;

                fseek(fp, -(long)sizeof(b), SEEK_CUR);
                fwrite(&b, sizeof(b), 1, fp);

                printf("Withdrawal Successful!\n");
                printf("Remaining Balance: %.2f\n", b.balance);
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account Not Found!\n");
    }

    fclose(fp);
}

// 6. Update Account
void updateAccount() {
    struct Bank b;
    int number, found = 0;

    FILE *fp = fopen("bank.dat", "rb+");

    if (fp == NULL) {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &number);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.accountNo == number) {
            printf("Enter New Name: ");
            scanf(" %49[^\n]", b.name);

            fseek(fp, -(long)sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);

            printf("Account Updated Successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account Not Found!\n");
    }

    fclose(fp);
}

// 7. Delete Account
void deleteAccount() {
    struct Bank b;
    int number, found = 0;

    FILE *fp = fopen("bank.dat", "rb");

    if (fp == NULL) {
        printf("No Records Found!\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");

    if (temp == NULL) {
        printf("File Error!\n");
        fclose(fp);
        return;
    }

    printf("Enter Account Number to Delete: ");
    scanf("%d", &number);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.accountNo == number) {
            found = 1;
        } else {
            fwrite(&b, sizeof(b), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("bank.dat");
        rename("temp.dat", "bank.dat");
        printf("Account Deleted Successfully!\n");
    } else {
        remove("temp.dat");
        printf("Account Not Found!\n");
    }
}

// Main Function
int main() {
    int choice;

    do {
        printf("\n========== BANK RECORD MANAGEMENT ==========\n");
        printf("1. Create Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Search Account\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Update Account\n");
        printf("7. Delete Account\n");
        printf("8. Exit\n");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;

            case 2:
                displayAccounts();
                break;

            case 3:
                searchAccount();
                break;

            case 4:
                depositMoney();
                break;

            case 5:
                withdrawMoney();
                break;

            case 6:
                updateAccount();
                break;

            case 7:
                deleteAccount();
                break;

            case 8:
                printf("Thank You!\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while (choice != 8);

    return 0;
}