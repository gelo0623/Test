#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

// Part 1 A
const int NUM_BANKS = 4;
string bankNames[NUM_BANKS] = {"BDO", "BPI", "Metrobank", "Security Bank"};
double localFees[NUM_BANKS] = {25, 20, 30, 15};
double intlFees[NUM_BANKS] = {150, 125, 200, 100};
double dailyLimits[NUM_BANKS] = {50000, 75000, 100000, 60000};

// Part 1 B
const int NUM_DENOMINATIONS = 2;
int denominations[NUM_DENOMINATIONS] = {500, 1000};
int billCount[NUM_DENOMINATIONS] = {500, 500}; // Current count of each 


// Admin
vector<string> adminUsers = {"admin"};


// Part 1 c
vector<string> cardNumbers;
vector<string> encodedPINs;     
vector<double> balances;        
vector<string> userBanks;        
vector<string> accountTypes;    

void addAccount(string card, string pin, double balance, string bank, string type) {

cardNumbers.push_back(card);
encodedPINs.push_back(pin);
balances.push_back(balance);
userBanks.push_back(bank);
accountTypes.push_back(type);

}


// Part 1 D
vector<string> transactionTypes;    
vector<double> transactionAmounts;
vector<double> transactionFees;
vector<int> transactionQuantities;  

void logTransaction(const string& cardNum, const string& type, double amount, double fee) {

    bool found = false;

    for (int i = 0; i < transactionTypes.size(); i++) {

        if (transactionTypes[i] == type) {

            transactionAmounts[i] += amount;
            transactionFees[i] += fee;
            transactionQuantities[i]++;
            found = true;
            break;

        }

    }
    
    if (!found) {

        transactionTypes.push_back(type);  
        transactionAmounts.push_back(amount);
        transactionFees.push_back(fee);
        transactionQuantities.push_back(1);
        
    }
    
    // PART 7 BONUS 
    ofstream file("transaction.csv", ios::app); 
    if (file.is_open()){
        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        
        file << (timeinfo->tm_mon + 1) << "/" << timeinfo->tm_mday << "/" << (timeinfo->tm_year + 1900) << "," << timeinfo->tm_hour << ":" << timeinfo->tm_min << "," << cardNum << "," << type << "," << amount << "," << fee << endl;
        file.close();
    }
    else {
        cerr << "Error: Could not open transaction.csv" << endl;
    }

}



// Overloading function
void logTransaction(string type, double amount) {
    logTransaction(type, amount, 0);
}


// Functions
int login();
void clientMenu();
void adminMenu();

// =======PART 6========= //

// Recursive function to calculate number of bills for a given amount
void calculateBills(double amount, int& bills1000, int& bills500) {
    if (amount >= 1000){
        bills1000++; //idk why 5000 sayo sir
        calculateBills(amount - 1000, bills1000, bills500);
    }

    else if (amount >= 500) {
        bills500++;
        calculateBills(amount - 500, bills1000, bills500);
    }

}



// DATE AND FRICKING TIME 
void displayDateTime() {
    time_t now = time(0);
    tm* timeinfo = localtime(&now); 

    cout << "Date: " << (timeinfo->tm_mon + 1) << "/" << timeinfo->tm_mday << "/" << (timeinfo->tm_year + 1900);
    cout << " Time: " << timeinfo->tm_hour << ":" << timeinfo->tm_min << endl;
}




// encoding functions
string encodeString(string plain){
    return "encodedPIN: " + plain;
}

bool verifyPIN(string input, string stored){
    return encodeString(input) == stored;
}


// Main function
int main () {
    
    addAccount("1234567890123456", "encodedPIN: 1234", 10000, "BDO", "Local");
    logTransaction("Deposit", 5000, 0);
    
    login();

    // Part 6 Fstream clear shinanigans Vector Clear
    cardNumbers.clear();
    encodedPINs.clear();
    balances.clear();
    userBanks.clear();
    accountTypes.clear();
    transactionTypes.clear();
    transactionAmounts.clear();
    transactionFees.clear();
    transactionQuantities.clear();
    
    return 0;
}



//where to do code
int login() {
    int role;

    cout << "======= WELCOME TO ATM SYSTEM =======" << endl;
    cout << "[1] Client Menu" << endl;
    cout << "[2] Admin Menu" << endl;
    cout << "Select Role: ";
    cin >> role;

    if (role == 1){
        clientMenu();
    }
    else if (role == 2){
        adminMenu();
    }
    else {
        cout << "Invalid Choice!";
    }


    
    return 0;
}


void clientMenu () {

    string card, pin;

    cout << "\nInsert your Card Number: ";
    cin >> card;

    int accountIndex = -1;

        for(int i = 0; i < cardNumbers.size(); i++){
            if(cardNumbers[i] == card){
                accountIndex = i;
                break;
            }
        }

        if(accountIndex == -1){
            cout << "Your card number cannot be found.\n";
            return;
        }

        cout << "Enter your PIN number: ";
        cin >> pin;

        if(encodeString(pin) != encodedPINs[accountIndex]){
            cout << "Wrong PIN number.\n";
            return;
        }

    int choice;

    do{

            cout << "===== CLIENT MENU =====" << endl;
            cout << "Bank: " << userBanks[accountIndex] << endl;
            cout << "Account Type: " << accountTypes[accountIndex] << endl;
            cout << "Current Balance: " << balances[accountIndex] << endl;
            
            displayDateTime();
            
            cout << "1. Check Balance." << endl;
            cout << "2. Withdraw." << endl;
            cout << "3. Transfer." << endl;
            cout << "4. View Transaction History." << endl;
            cout << "5. Change your PIN number." << endl;
            cout << "6. Logout" << endl;
            cout << "======================" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

                if(choice == 1){

                    cout << "===== BALANCE CHECK PANEL =====\n";
                    cout << "\nBalance: " << balances[accountIndex] << endl;
                    
                

                    cout << "\nPress any key to continue another transaction: ";
                    string temp;
                    cin >> temp;

                }

                if(choice == 2){
                    
            
            cout << "===== WITHDRAWAL PANEL =====\n" << endl;
            
            int wdrawAmount1, wdrawAmount2, amount = 0;
            
            cout << "[1] 500Php" << endl;
            cout << "[2] 1000Php" << endl;
            cout << "[3] 5,000Php";
            cout << "[4] 10,000Php\n";
            cout << "[5] Enter an Amount." << endl;
            cout << "===========================" << endl;
            cout << "Enter your choice (1-5): ";
            cin >> wdrawAmount1;
            
            
            
            if(wdrawAmount1 == 1) amount = 500;
            else if(wdrawAmount1 == 2) amount = 1000;
            else if(wdrawAmount1 == 3) amount = 5000;
            else if(wdrawAmount1 == 4) amount = 10000;
            else if(wdrawAmount1 == 5){
                
                cout << "\nEnter amount to Withdraw: ";
                cin >> wdrawAmount2;
                
                amount = wdrawAmount2;
    }
    
    if(amount % 500 != 0){
        cout << "Invalid  Amount. Amount must be divisible by 500";
        continue;
    }

    // Determine bank index fee and daily limit
    int bankIndex = -1;
    for(int i = 0; i < NUM_BANKS; i++){
        if(userBanks[accountIndex] == bankNames[i]){
            bankIndex = i;
            break;
        }
    }
    
    if(bankIndex == -1){
        cout << "Bank not recognized.\n";
        continue;
    }
    
    double fee = 0;
    if(accountTypes[accountIndex] == "Local") fee = localFees[bankIndex];
    else fee = intlFees[bankIndex];

    double totalDeduction = amount + fee;

    // Check balance
    if(totalDeduction > balances[accountIndex]){
        cout << "\nInsufficient balance including fees.\n";
        continue;
    }

    // Check daily limit
    if(amount > dailyLimits[bankIndex]){
        cout << "\nWithdrawal exceeds daily limit of " << dailyLimits[bankIndex] << " PHP.\n";
        continue;
    }

    // Check ATM cash availability
    int totalCashAvailable = 0;
    for(int i = 0; i < NUM_DENOMINATIONS; i++) totalCashAvailable += denominations[i] * billCount[i];
    if(amount > totalCashAvailable){
        cout << "\nATM does not have sufficient cash.\n";
        continue;
    }

    // Deduct amount and fee
    balances[accountIndex] -= totalDeduction;
    logTransaction(cardNumbers[accountIndex], "Withdrawal", amount, fee);


    cout << "Please Wait..." << endl;
    cout << "\nCollect your cash: PHP " << amount << endl;
    cout << "Fee deducted: PHP " << fee << endl;

    // deduction shinanigans apply here
    int bills1000 = 0;
    int bills500 = 0;

    calculateBills(amount, bills1000, bills500);
    cout << "1000 Bills: " << bills1000 << endl;
    cout << "500 Bills: " << bills500 <<  endl;

    displayDateTime();

    cout << "\nPress any key to continue: ";
    string temp;
    cin >> temp;
}



                if(choice == 3){

    string receiver;
    double amount;

    cout << "===== TRANSFER PANEL =====\n";
    cout << "Enter receipient card number: ";
    cin >> receiver;

    int receiverIndex = -1;
    for(int i = 0; i < cardNumbers.size(); i++){
        if(cardNumbers[i] == receiver){
            receiverIndex = i;
            break;
        }
    }

    if(receiverIndex == -1){
        cout << "Sorry, Recipient not found.\n";
        continue;
    }

    cout << "Enter amount to transfer: ";
    cin >> amount;

    // Determine fee: local vs international
    int senderBankIndex = -1;
    int receiverBankIndex = -1;
    for(int i = 0; i < NUM_BANKS; i++){
        if(userBanks[accountIndex] == bankNames[i]) senderBankIndex = i;
        if(userBanks[receiverIndex] == bankNames[i]) receiverBankIndex = i;
    }

    double fee = 0;
    if(senderBankIndex != -1 && receiverBankIndex != -1){
        if(senderBankIndex == receiverBankIndex) fee = localFees[senderBankIndex];
        else fee = intlFees[senderBankIndex];
    }

    double totalDeduction = amount + fee;
    if(totalDeduction > balances[accountIndex]){
        cout << "Insufficient balance including transfer fee.\n";
        continue;
    }

    balances[accountIndex] -= totalDeduction;
    balances[receiverIndex] += amount;
    logTransaction(cardNumbers[accountIndex], "Transfer", amount, fee);

    time_t now = time(0);
    cout << "Transfer successful!\n";
    cout << "Amount: PHP " << amount << endl;
    cout << "Fee: PHP " << fee << endl;
    cout << "Transaction time: " << ctime(&now);
}

                if(choice == 4){

                        cout << "===== VIEWING TRANSACTION HISTORY =====" << endl;

                        if(transactionTypes.empty()){
                            cout << "Oops, you do not have transactions yet.\n";
                        }

                        for(int i = 0; i < transactionTypes.size(); i++){
                            cout << transactionTypes[i] << " | Amount: " << transactionAmounts[i] << " | Fee: " << transactionFees[i] << " | Count: " << transactionQuantities[i] << endl;
                        }

                        cout << "\nPress any key to continue: ";
                        string temp;
                        cin >> temp;
                    
                }

                if(choice == 5){

                    string oldPIN, newPIN;

                    cout << "Enter your current PIN number: ";
                    cin >> oldPIN;

                    if(encodeString(oldPIN) != encodedPINs[accountIndex]){
                        cout << "Incorrect PIN.\n";
                        continue;
                    }

                    cout << "Enter your NEW PIN number: ";
                    cin >> newPIN;

                    encodedPINs[accountIndex] = encodeString(newPIN);

                    cout << "\nSuccessfully changed your PIN number.\n";

                }

    }while(choice != 6);

    cout << "Logging you out...\n";

}



void adminMenu () {
    int choice;
    
    do {
        cout << "======== ADMIN MENU ========" << endl;
        cout << "[1] Add Account" << endl;
        cout << "[2] View Accounts" << endl;
        cout << "[3] Delete/Deactivate Account" << endl;
        cout << "[4] ATM Cash Refill" << endl;
        cout << "[5] ATM Status" << endl;
        cout << "[6] Change Admin Passcode" << endl;
        cout << "[7] View list of Admin Users" << endl;
        cout << "[8] Reset Account Password" << endl;
        cout << "[9] Exit" << endl;
        cout << "Select Choice: ";
        cin >> choice;
        cout << "============================" << endl;
        
        
        if (choice == 1) {
            string card, pin, bank, type;
            double balance;
            
            cout << "Enter Card Number: ";
            cin >> card;
            
            cout << "Enter Pin Number: ";
            cin >> pin;
            
            cout << "Enter Bank: ";
            cin >> bank;
            
            cout << "Enter Balance Amount: ";
            cin >> balance;
            
            cout << "Enter Account Type: ";
            cin >> type;
            
            addAccount(card, encodeString(pin), balance, bank, type);
            
            cout << "Account Added Successfully.\n";
            
            
        }
        
        else if (choice == 2){
            cout << "======== View Accounts ========" << endl;
            
            if(cardNumbers.empty()) {
                cout << "No accounts available.\n";
            }
            else {
                for(int i = 0; i < cardNumbers.size(); i++){
                    cout << "Account " << i + 1 << endl;
                    cout << "Card Number: " << cardNumbers[i] << endl;
                    cout << "Bank: " << userBanks[i] << endl;
                    cout << "Account Type: " << accountTypes[i] << endl;
                    cout << "Balance: " << balances[i] << endl;
                    cout << "--------------------------" << endl;
                }
            }
            
            
        }
        
        else if(choice == 3){
            string card;
            cout << "Enter Card Number to delete/deactivate: ";
            cin >> card;

            bool found = false;
            for(int i = 0; i < cardNumbers.size(); i++){
                if(cardNumbers[i] == card){
                    cardNumbers.erase(cardNumbers.begin() + i);
                    encodedPINs.erase(encodedPINs.begin() + i);
                    balances.erase(balances.begin() + i);
                    userBanks.erase(userBanks.begin() + i);
                    accountTypes.erase(accountTypes.begin() + i);

                    cout << "Account deleted/deactivated successfully.\n";
                    found = true;
                    break;
                }
            }
            if(!found) cout << "Account not found. Try another number\n";
        }
        
        else if (choice == 4){
            time_t now = time(0);
            tm* localTime = localtime(&now);

            if(localTime->tm_hour != 8 || localTime->tm_min > 15) {
                cout << "Refill allowed only from 8:00 AM to 8:15 AM.\n";
            }
            else{
                cout << "======== ATM CASH REFILL ========\n";
                for(int i = 0; i < NUM_DENOMINATIONS; i++){
                    int addBills;
                    cout << "Enter number of " << denominations[i] << " Php bills to add: ";
                    cin >> addBills;
                    billCount[i] += addBills;
                }
                cout << "ATM Cash Refilled Successfully.\n";
            }
            
            
        }
        
        else if (choice == 5){
            cout << "======== ATM STATUS ========\n";
            double totalCash = 0;
            for(int i = 0; i < NUM_DENOMINATIONS; i++){
                cout << "Denomination: " << denominations[i] << " | Bills: " << billCount[i] << " | Subtotal: " << denominations[i] * billCount[i] << endl;
                totalCash += denominations[i] * billCount[i];
            }
            cout << "Total Cash in ATM: PHP " << totalCash << endl;
            
            
        }

        else if (choice == 6) {
            string adminPasscode = "6767";
            string currentPass, newPass;


            cout << "Enter Admin Passcode: ";
            cin >> currentPass;

            if (currentPass != adminPasscode){
                cout << "Incorrect Passcode" << endl;
            }

            else {
                cout << "Enter New Admin Passcode: ";
                cin >> newPass;
                adminPasscode = newPass;


                cout << "Admin Passcode Changed Successfully!" << endl;
            }
        }

        else if (choice == 7){
            cout << "========= LIST OF ADMIN USERS =========" << endl;
            for(const auto &admin : adminUsers){
                cout << admin << endl;
            }
        }

        else if (choice == 8){
            string card;
            cout << "Enter Card Number of Accout to Reset PIN: ";
            cin >> card;

            int accountIndex = -1;
            for (int i = 0; i < cardNumbers.size(); i++){
                if(cardNumbers[i] == card){
                    accountIndex = i;
                    break;
                }
            }
            if (accountIndex == -1){
                cout << "Account Not Found" << endl;
            }

            else {
                string newPIN;
                cout << "Enter New PIN: ";
                cin >> newPIN;
                encodedPINs[accountIndex] = encodeString(newPIN);
                cout << "Account PIN  has been reset Successfully!" << endl;
            }

        }


    
    } while (choice != 9);
    
}




















