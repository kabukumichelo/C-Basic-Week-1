#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ACCOUNTS 100
#define NAME_LEN 50
#define ACCNO_LEN 20
#define PASS_LEN 20
#define FILE_NAME "accounts.dat"
typedef struct {
    char name[NAME_LEN];
    char accNo[ACCNO_LEN];
    char password[PASS_LEN];
    double balance;
    int active;
} Account;
/* Global array to hold accounts in memory */
Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

char *getInput(char *buf,
int size, const char *prompt);
int  getChoice(int min, int max);
int  yesNo(const char *prompt);
/* --------------------------------------------------- */
int main(void)
{
    loadAccounts();
    int choice;
    char accNo[ACCNO_LEN];
    while (1) {
        showMenuLoggedOut();
        choice = getChoice(1, 3);
        if (choice == 1) {       /* Register */
            registerAccount();
        } else if (choice == 2) { /* Login */
            if (login(accNo) == 0) {
                showMenuLoggedIn(accNo);
            } else {
                printf("\nLogin failed. Please try again.\n");
            }
        } else {
            /* close */
            saveAccounts();
            printf("\nThank you for banking with us...\n");
            printf("\nGoodbye!\n");
            break;
        }
    }
    return 0; }



/* Load all accounts from the file into memory  for actions  */
 void loadAccounts(void)
{
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return;               /* No file yet â€“ start with empty DB */
    fread(&accountCount, sizeof(int), 1, fp);
    fread(accounts, sizeof(Account), accountCount, fp);
     fclose(fp);
}
/* Save inâ€‘memory accounts to the file                */
void saveAccounts(void)
{
    FILE *fp = fopen(FILE_NAME, "wb");
    if (!fp) {
        perror("Unable to open file for saving");
        return;
    }
    fwrite(&accountCount, sizeof(int), 1, fp);
    fwrite(accounts, sizeof(Account), accountCount, fp);
    fclose(fp);
}
/* Find index of account with given number; -1 if none */
int findAccount(const char *accNo)
{
    for (int i = 0; i < accountCount; ++i)
        if (accounts[i].active && strcmp(accounts[i].accNo, accNo)== 0)
        return i;

    return -1; }

/* --------------------------------------------------- */
/* Login routine â€“ returns 0 on success, -1 on failure */
int login(char *accNo)
{
    char username[ACCNO_LEN];
    char password[PASS_LEN];
    int attempts = 3;
    while (attempts--) {
        getInput(username, ACCNO_LEN, "\nEnter account number: ");
        getInput(password, PASS_LEN, "Enter password: ");
        int idx = findAccount(username);
        if (idx != -1 && strcmp(accounts[idx].password, password) == 0) {
            strcpy(accNo, username);
            return 0;                     /* success */
        }
        printf("Invalid credentials (%d attempts left).\n", attempts);
    }
    return -1; }

/* --------------------------------------------------- */
void registerAccount(void)
{
    if (accountCount >= MAX_ACCOUNTS) {
        printf("\nMaximum number of accounts reached.\n");
        return;
    }
    Account newAcc;
    memset(&newAcc, 0, sizeof(Account)); newAcc.active = 1;
    getInput(newAcc.name, NAME_LEN, "\nEnter full name: ");

    getInput(newAcc.accNo, ACCNO_LEN, "Create account number: ");
    while (findAccount(newAcc.accNo) != -1) {
        printf("Account number already exists.\n");
        getInput(newAcc.accNo, ACCNO_LEN, "Enter a different account number: ");     }
        getInput(newAcc.password, PASS_LEN, "Create password: ");
    char depositStr[20];
    double initDeposit = 0.0;
    while (1) {
        getInput(depositStr, sizeof(depositStr), "Initial deposit(minimum 100): ");
        if (sscanf(depositStr, "%lf", &initDeposit) == 1 && initDeposit >= 100)
            break;
        printf("Please enter a numeric value >= 100.\n");
    }
    newAcc.balance = initDeposit;
    accounts[accountCount++] = newAcc;
    printf("\nAccount created successfully! Please login.\n"); }
/* --------------------------------------------------- */
void deposit(const char *accNo)
{
    int idx = findAccount(accNo);
    if (idx == -1) return;
    char amtStr[20];
    double amount = 0.0;
    while (1) {
        getInput(amtStr, sizeof(amtStr), "Enter amount to deposit:");
        if (sscanf(amtStr, "%lf", &amount) == 1 && amount > 0)
            break;
        printf("Invalid amount.\n");
    }
    accounts[idx].balance += amount;
    printf("New balance: %.2f\n", accounts[idx].balance); }
/* --------------------------------------------------- */
void withdraw(const char *accNo)
{
    int idx = findAccount(accNo);
        if (idx == -1)
    return;

    char amtStr[20];
    double amount = 0.0;
    while (1) {
        getInput(amtStr, sizeof(amtStr), "Enter amount to withdraw:");
        if (sscanf(amtStr, "%lf", &amount) == 1 && amount > 0)
            break;
        printf("Invalid amount.\n");
    }
    if (amount > accounts[idx].balance) {
        printf("Insufficient funds.\n");
        return;
    }

    accounts[idx].balance -= amount;
    printf("New balance: %.2f\n", accounts[idx].balance);
}
/* --------------------------------------------------- */

void transfer(void)
{
    char from[ACCNO_LEN], to[ACCNO_LEN];
        getInput(from, ACCNO_LEN, "\nEnter source account number: ");
        getInput(to, ACCNO_LEN, "Enter destination account number: ");
    int src = findAccount(from);
    int dst = findAccount(to);
    if (src == -1 || dst == -1) {
        printf("One of the accounts does not exist.\n");
        return;
    }
    char amtStr[20];
    double amount = 0.0;
    while (1) {
        getInput(amtStr, sizeof(amtStr), "Enter amount to transfer:");
        if (sscanf(amtStr, "%lf", &amount) == 1 && amount > 0)
            break;

        printf("Invalid amount.\n");
    }
    if (amount > accounts[src].balance) {
        printf("Insufficient funds in source account.\n");
        return;
    }
    accounts[src].balance -= amount;
    accounts[dst].balance += amount;
    printf("Transfer successful.\n");
    printf("Source new balance: %.2f\n", accounts[src].balance);
    printf("Destination new balance: %.2f\n", accounts[dst].balance); }


/* --------------------------------------------------- */
void changePassword(const char *accNo)
{
    int idx = findAccount(accNo);     if (idx == -1) return;
    char oldPass[PASS_LEN];
    getInput(oldPass, PASS_LEN, "Enter current password: ");
    if (strcmp(oldPass, accounts[idx].password) != 0) {
        printf("Incorrect password.\n");
        return;
    }
    char newPass[PASS_LEN];
    getInput(newPass, PASS_LEN, "Enter new password: ");
    char confirm[PASS_LEN];
    getInput(confirm, PASS_LEN, "Confirm new password: ");
    if (strcmp(newPass, confirm) != 0) {
        printf("Passwords do not match.\n");
        return;
    }
    strcpy(accounts[idx].password, newPass);
    printf("Password changed successfully.\n");
}
/* --------------------------------------------------- */



void displayDetails(const char *accNo)
{
    int idx = findAccount(accNo);
    if (idx == -1) return;

    printf("\n--- Account Details ---");
    printf("\nName: %s", accounts[idx].name);
    printf("\nAccount Number: %s", accounts[idx].accNo);
    printf("\nBalance: %.2f", accounts[idx].balance);
    printf("\nPassword: %s", "********");   /* never show plain password */
    printf("\n------------------------\n");
}

/* --------------------------------------------------- */
void showMenuLoggedOut(void)
{
   printf("\n=== Michie E cash Ltd===");
    printf("\n=== Online Banking ===");
    printf("\n1. Register");
    printf("\n2. Login");
    printf("\n3. Exit");
    printf("\nChoose an option: ");
}


void showMenuLoggedIn(const char *accNo)
{
    int choice;
    while (1) {
        printf("\n=== Welcome %s ===", accNo);
        printf("\n1. Deposit");
        printf("\n2. Withdraw");
        printf("\n3. Transfer");
        printf("\n4. Change Password");
        printf("\n5. Display Details");
        printf("\n6. Logout");
        printf("\nSelect option: ");
        choice = getChoice(1, 6);

        switch (choice) {
            case 1: deposit(accNo); break;
            case 2: withdraw(accNo); break;
            case 3: transfer(); break;
            case 4: changePassword(accNo); break;
            case 5: displayDetails(accNo); break;
            case 6: printf("\nLogging outâ€¦\n"); return;
        }
    }
}

/* --------------------------------------------------- */

char *getInput(char *buf, int size, const char *prompt)
{
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, size, stdin) == NULL) {
        *buf = '\0';
        return buf;
    }

    buf[strcspn(buf, "\n")] = '\0';
    return buf;
}


int getChoice(int min, int max)
{
    char line[10];
    int choice;
    while (1) {
        getInput(line, sizeof(line), "");
        if (sscanf(line, "%d", &choice) == 1 && choice >= min && choice <= max)
            return choice;
        printf("Invalid choice, please enter a number between %d and %d: ", min, max);
    }
}

/* Helper: simple yes/no prompt*/
int yesNo(const char *prompt)
{
    char ans;
    while (1) {
        getInput(&ans, 2, prompt);
        ans = tolower(ans);
        if (ans == 'y' || ans == 'n')
            return ans == 'y';
        printf("Please answer y or n: ");
    }
}
