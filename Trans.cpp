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
    logTransaction("Transfer", amount, fee);

    time_t now = time(0);
    cout << "Transfer successful!\n";
    cout << "Amount: PHP " << amount << endl;
    cout << "Fee: PHP " << fee << endl;
    cout << "Transaction time: " << ctime(&now);
}
