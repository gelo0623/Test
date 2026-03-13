if(choice == 2){

    cout << "===== WITHDRAWAL PANEL =====\n" << endl;

    int wdrawAmount1, wdrawAmount2, amount = 0;

    cout << "1. 500Php";
    cout << "      2. 1000Php\n";
    cout << "3. 5,000Php";
    cout << "    4. 10,000Php\n";
    cout << "   5. Enter an Amount." << endl;
    cout << "\nEnter your choice (1-5): ";
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

    // Determine bank index for fee and daily limit
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
    logTransaction("Withdrawal", amount, fee);

    cout << "Please Wait..." << endl;
    cout << "\nCollect your cash: PHP " << amount << endl;
    cout << "Fee deducted: PHP " << fee << endl;

    time_t now = time(0);
    cout << "Transaction time: " << ctime(&now);

    cout << "\nPress any key to continue: ";
    string temp;
    cin >> temp;
}
