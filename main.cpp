#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void readFile(map<double, vector<string>>& transactionAmount, map<string, vector<vector<string>>>& transactionInfo) {
    string line, word;

    ifstream fin("FraudulentTransaction.csv");
    if (!fin.is_open()) {
        cerr << "Error opening file" << endl;
        cerr << strerror(errno) << endl;
        return;
    }

    getline(fin, line);
    while (getline(fin, line)) {
        stringstream s(line);
        // char last = line[line.length() - 2];
        // cout << last;
        // abc.push_back(line.back());
        int i = 0;
        string transactionID;
        string amount;
        vector<string> info;
        if(line[line.length() - 2] == '1') {
            info.push_back("Fraud");
        }
        while (getline(s, word, ',')) {
            if (i == 0) {
                transactionID = word;
            } else if (i == 2) {
                amount = word;
            } else {
                info.push_back(word);
            }
            i++;
        }

        transactionAmount[stod(amount)].push_back(transactionID);
        transactionInfo[transactionID].push_back(info);
    }
    fin.close();
}

void viewTop20Highest(map<double, vector<string>>& transactionAmount, map<string, vector<vector<string>>>& transactionInfo) {
    // cout << transactionAmount.size() << " " << transactionInfo.size() << endl;
    int count = 0;
    map<double, vector<string>>::reverse_iterator it;
    for (it = transactionAmount.rbegin(); it != transactionAmount.rend() && count < 20; it++) {
        double amount = it->first;
        for (auto transactionID: it->second) {
            if (transactionInfo.find(transactionID) != transactionInfo.end()) {
                for (auto t: transactionInfo[transactionID]) {
                    auto it = std::find(t.begin(), t.end(), "Fraud");
                    if (it != t.end()) {
                        cout << "Transaction Amount: " << amount << endl;
                        for(int i=0; i<t.size(); i++) {
                            if (i == 1) {
                                cout << "Customer ID: " << t[1] << endl;
                            } else if (i == 2) {
                                cout << "Transaction Date: " << t[2] << endl;
                            } else if (i == 3) {
                                cout << "Payment method: " << t[3] << endl;
                            } else if (i == 4) {
                                cout << "Product Category: " << t[4] << endl;
                            }
                        }
                        cout << endl;
                        ++count;
                    }
                }
            }
        }
    }
}

void viewTop20Lowest(map<double, vector<string>>& transactionAmount, map<string, vector<vector<string>>>& transactionInfo) {
    int count = 0;
    for (auto it = transactionAmount.begin(); it != transactionAmount.end() && count < 20; it++) {
        double amount = it->first;
        for (auto transactionID: it->second) {
            if (transactionInfo.find(transactionID) != transactionInfo.end()) {
                for (auto t : transactionInfo[transactionID]) {
                    auto it = std::find(t.begin(), t.end(), "Fraud");
                    if (it != t.end()) {
                        cout << "Transaction Amount: " << amount << endl;
                        for(int i=0; i<t.size(); i++) {
                            if (i == 1) {
                                cout << "Customer ID: " << t[1] << endl;
                            } else if (i == 2) {
                                cout << "Transaction Date: " << t[2] << endl;
                            } else if (i == 3) {
                                cout << "Payment method: " << t[3] << endl;
                            } else if (i == 4) {
                                cout << "Product Category: " << t[4] << endl;
                            }
                        }
                        cout << endl;
                    }
                }
            }
        }
    }
}

void searchByDate(map<double, vector<string>>& transactionAmount, map<string, vector<vector<string>>>& transactionInfo, string date) {
    cout << endl;
    for (auto it = transactionAmount.begin(); it != transactionAmount.end(); it++) {
        double amount = it->first;
        for (auto transactionID: it->second) {
            if (transactionInfo.find(transactionID) != transactionInfo.end()) {
                for (auto t : transactionInfo[transactionID]) {
                    auto it = std::find(t.begin(), t.end(), "Fraud");
                    if (it != t.end()) {
                        size_t checkDate = t[2].find(date);
                        if (checkDate != string::npos) {
                            cout << "Transaction Amount: " << amount << endl;
                            for(int i=0; i<t.size(); i++) {
                                if (i == 1) {
                                    cout << "Customer ID: " << t[1] << endl;
                                } else if (i == 2) {
                                    cout << "Transaction Date: " << t[2] << endl;
                                } else if (i == 3) {
                                    cout << "Payment method: " << t[3] << endl;
                                } else if (i == 4) {
                                    cout << "Product Category: " << t[4] << endl;
                                }
                            }
                            cout << endl;
                        }
                    }
                }
            }
        }
    }
}

void searchByCategory(map<double, vector<string>>& transactionAmount, map<string, vector<vector<string>>>& transactionInfo, string category) {
    for (auto it = transactionAmount.begin(); it != transactionAmount.end(); it++) {
        double amount = it->first;
        for (auto transactionID: it->second) {
            if (transactionInfo.find(transactionID) != transactionInfo.end()) {
                for (auto t : transactionInfo[transactionID]) {
                    auto it = std::find(t.begin(), t.end(), "Fraud");
                    if (it != t.end()) {
                        size_t productCategory = t[4].find(category);
                        if (productCategory != string::npos) {
                            cout << "Transaction Amount: " << amount << endl;
                            for(int i=0; i<t.size(); i++) {
                                if (i == 1) {
                                    cout << "Customer ID: " << t[1] << endl;
                                } else if (i == 2) {
                                    cout << "Transaction Date: " << t[2] << endl;
                                } else if (i == 3) {
                                    cout << "Payment method: " << t[3] << endl;
                                } else if (i == 4) {
                                    cout << "Product Category: " << t[4] << endl;
                                }
                            }
                            cout << endl;
                        }
                    }
                }
            }
        }
    }
}

void searchByPaymentMethod(map<double, vector<string>>& transactionAmount, map<string, vector<vector<string>>>& transactionInfo, string method) {
    for (auto it = transactionAmount.begin(); it != transactionAmount.end(); it++) {
        double amount = it->first;
        for (auto transactionID: it->second) {
            if (transactionInfo.find(transactionID) != transactionInfo.end()) {
                for (auto t : transactionInfo[transactionID]) {
                    auto it = std::find(t.begin(), t.end(), "Fraud");
                    if (it != t.end()) {
                        size_t paymentMethod = t[3].find(method);
                        if (paymentMethod != string::npos) {
                            cout << "Transaction Amount: " << amount << endl;
                            for(int i=0; i<t.size(); i++) {
                                if (i == 1) {
                                    cout << "Customer ID: " << t[1] << endl;
                                } else if (i == 2) {
                                    cout << "Transaction Date: " << t[2] << endl;
                                } else if (i == 3) {
                                    cout << "Payment method: " << t[3] << endl;
                                } else if (i == 4) {
                                    cout << "Product Category: " << t[4] << endl;
                                }
                            }
                            cout << endl;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    map<double, vector<string>> transactionAmount;
    map<string, vector<vector<string>>> transactionInfo;

    std::cout << "Let's analyze some fraudulent transactions!" << std::endl;
    while(true){
        std::cout << "*******************************************" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. View top 20 highest fraudulent transaction amount" << std::endl;
        std::cout << "2. View top 20 lowest fraudulent transaction amount" << std::endl;
        std::cout << "3. Search for fraudulent transactions by date" << std::endl;
        std::cout << "4. Search for fraudulent transactions by product category" << std::endl;
        std::cout << "5. Search for fraudulent transactions by payment method" << std::endl;
        std::cout << "*******************************************" << std::endl;
        std::cout << "Menu Choice: ";

        int command;
        cin >> command;

        if (command == 0) {
            std::cout << "Thank you and have a great day!" << std::endl;
            break;
        } else {
            readFile(transactionAmount, transactionInfo);

            if (command == 1) {
                cout<<endl;
                viewTop20Highest(transactionAmount, transactionInfo);
            } else if (command == 2) {
                cout<<endl;
                viewTop20Lowest(transactionAmount, transactionInfo);
            } else if (command == 3) {
                string date;
                cout << "Please enter the date (use this format: yyyy-mm-dd) on which you want to view the fraudulent transactions: " << endl;
                cin >> date;
                cout<<endl;
                searchByDate(transactionAmount, transactionInfo, date);
            } else if (command == 4) {
                int category;
                cout << "Product Categories:";
                cout << "[1] clothing, [2] electronics, [3] health & beauty, [4] home & garden, [5] toys & games" << endl;
                cout << "Please enter the number associated with the product category you want to view the fraudulent transactions: " << endl;
                cin >> category;
                cout<<endl;
                if (category == 1) {searchByCategory(transactionAmount, transactionInfo, "clothing");}
                else if (category == 2) {searchByCategory(transactionAmount, transactionInfo, "electronics");}
                else if (category == 3) {searchByCategory(transactionAmount, transactionInfo, "health & beauty");}
                else if (category == 4) {searchByCategory(transactionAmount, transactionInfo, "home & garden");}
                else if (category == 5) {searchByCategory(transactionAmount, transactionInfo, "toys & games");}
            } else if (command == 5) {
                int category;
                cout << "Payment Methods:";
                cout << "[1] bank transfer, [2] credit card, [3] debit card, [4] PayPal" << endl;
                cout << "Please enter the number associated with the payment method you want to view the fraudulent transactions: " << endl;
                cin >> category;
                cout<<endl;
                if (category == 1) {searchByPaymentMethod(transactionAmount, transactionInfo, "bank transfer");}
                else if (category == 2) {searchByPaymentMethod(transactionAmount, transactionInfo, "credit card");}
                else if (category == 3) {searchByPaymentMethod(transactionAmount, transactionInfo, "debit card");}
                else if (category == 4) {searchByPaymentMethod(transactionAmount, transactionInfo, "PayPal");}
            }
        }
    }

    return 0;
}
