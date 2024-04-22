
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include "Heap.h"
using namespace std;
using namespace std::chrono;

void readFile(map<double, vector<string>>& transactionAmount, map<string, vector<vector<string>>>& transactionInfo) {
    string line, word;

    // csv file to read in the data
    ifstream fin("/Users/ngocnguyen/Documents/UF/24spring/COP3530 - DSA/Project 3/FraudulentTransaction.csv");
    if (!fin.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    getline(fin, line);
    // handle each row of the csv source file
    while (getline(fin, line)) {
        stringstream s(line);
        int i = 0;
        string transactionID;
        string amount;
        vector<string> info;
        // if it's "1" in column "Is Fraud"
        if(line[line.length() - 2] == '1') {
            info.push_back("Fraud");
        }
        // handle each column in a row/tuple
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
        // transactionAmount map to store transaction's amount as key, and transaction ID as values
        transactionAmount[stod(amount)].push_back(transactionID);
        // transactionInfo map to store transaction ID as key, and other info (customer ID, date, payment method, and product category) as values
        transactionInfo[transactionID].push_back(info);
    }
    fin.close();
}

void readFileHeap(Heap<double, vector<string>*>& AmountMax, Heap<double, vector<string>*>& AmountMin, Heap<string, vector<string>*>& AgeMax, Heap<string, vector<string>*>& AgeMin, Heap<string, vector<string>*>& CategoryMax, Heap<string, vector<string>*>& CategoryMin, Heap<string, vector<string>*>& MethodMax, Heap<string, vector<string>*>& MethodMin) {
    string line, word;

    ifstream fin("/Users/ngocnguyen/Documents/UF/24spring/COP3530 - DSA/Project 3/FraudulentTransaction.csv");
    if (!fin.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    getline(fin, line);
    while (getline(fin, line)) {
        stringstream s(line);
        int i = 0;
        string transactionID;
        string amount;
        string age;
        string category;
        string method;
        vector<string>& info = *(new vector<string>());
        if(line[line.length() - 2] == '1') {
            info.push_back("Fraud");
        }
        while (getline(s, word, ',')) {
            if (i == 0) {
                transactionID = word;
            } else if (i == 2) {
                amount = word;
            } else if (i == 3) {
                age = word;
            } else if (i == 4) {
                method = word;
            } else if (i == 5) {
                category = word;
            } 
            info.push_back(word);
            i++;
        }

        AmountMax.enqueue(stod(amount),&info);
        AmountMin.enqueue(stod(amount),&info);
        AgeMax.enqueue(age,&info);
        AgeMin.enqueue(age,&info);
        CategoryMax.enqueue(category,&info);
        CategoryMin.enqueue(category,&info);
        MethodMax.enqueue(method,&info);
        MethodMin.enqueue(method,&info);
    }
    fin.close();
}


void viewTop20Highest(map<double, vector<string>>& transactionAmount, map<string, vector<vector<string>>>& transactionInfo) {
    // cout << transactionAmount.size() << " " << transactionInfo.size() << endl;

    // set up a counter to print only 20 transactions
    int count = 0;
    // reverse amounts in the transactionAmount map
    map<double, vector<string>>::reverse_iterator it;
    for (it = transactionAmount.rbegin(); it != transactionAmount.rend() && count < 20; it++) {
        double amount = it->first;
        // use transaction ID to search for the info in transactionInfo map
        for (auto transactionID: it->second) {
            if (transactionInfo.find(transactionID) != transactionInfo.end()) {
                for (auto t: transactionInfo[transactionID]) {
                    // search for fraudulent transactions
                    auto it = find(t.begin(), t.end(), "Fraud");
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
    // set up a counter to print only 20 transactions
    int count = 0;
    // traverse transactionAmount map
    for (auto it = transactionAmount.begin(); it != transactionAmount.end() && count < 20; it++) {
        double amount = it->first;
        // use transaction ID to search for the info in transactionInfo map
        for (auto transactionID: it->second) {
            if (transactionInfo.find(transactionID) != transactionInfo.end()) {
                for (auto t : transactionInfo[transactionID]) {
                    // search for fraudulent transactions
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
    // traverse transactionAmount map
    for (auto it = transactionAmount.begin(); it != transactionAmount.end(); it++) {
        double amount = it->first;
        // use transaction ID to search for the info in transactionInfo map
        for (auto transactionID: it->second) {
            if (transactionInfo.find(transactionID) != transactionInfo.end()) {
                for (auto t : transactionInfo[transactionID]) {
                    // search for fraudulent transactions
                    auto it = std::find(t.begin(), t.end(), "Fraud");
                    if (it != t.end()) {
                        // search for a certain date
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
        // use transaction ID to search for the info in transactionInfo map
        for (auto transactionID: it->second) {
            if (transactionInfo.find(transactionID) != transactionInfo.end()) {
                for (auto t : transactionInfo[transactionID]) {
                    // search for fraudulent transactions
                    auto it = std::find(t.begin(), t.end(), "Fraud");
                    if (it != t.end()) {
                        // search for a certain product category
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
        // use transaction ID to search for the info in transactionInfo map
        for (auto transactionID: it->second) {
            if (transactionInfo.find(transactionID) != transactionInfo.end()) {
                for (auto t : transactionInfo[transactionID]) {
                    // search for fraudulent transactions
                    auto it = std::find(t.begin(), t.end(), "Fraud");
                    if (it != t.end()) {
                        // search for a certain payment method
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

bool intGreater(double a, double b) {
    return a > b;
}
bool intLesser(double a, double b) {
    return a < b;
}
bool stringGreater(string a, string b) {
    return a > b;
}
bool stringLesser(string a, string b) {
    return a < b;
}

int main() {
    map<double, vector<string>> transactionAmount;
    map<string, vector<vector<string>>> transactionInfo;
    Heap<double,vector<string>*> AmountMax(intGreater);
    Heap<double,vector<string>*> AmountMin(intLesser);
    Heap<string,vector<string>*> AgeMax(stringGreater);
    Heap<string,vector<string>*> AgeMin(stringLesser);
    Heap<string,vector<string>*> CategoryMax(stringGreater);
    Heap<string,vector<string>*> CategoryMin(stringLesser);
    Heap<string,vector<string>*> MethodMax(stringGreater);
    Heap<string,vector<string>*> MethodMin(stringLesser);

    // Prompt user for command to start
    // Then print results along with how long it takes to run the execution
    cout << "Let's analyze some fraudulent transactions!" << endl;
    while(true){
        cout << "*******************************************" << endl;
        cout << "0. Exit" << endl;
        cout << "1. View top 20 highest fraudulent transaction amount" << endl;
        cout << "2. View top 20 lowest fraudulent transaction amount" << endl;
        cout << "3. Search for fraudulent transactions by date" << endl;
        cout << "4. Search for fraudulent transactions by product category" << endl;
        cout << "5. Search for fraudulent transactions by payment method" << endl;
        cout << "*******************************************" << endl;
        cout << "Menu Choice: ";

        int command;
        cin >> command;

        if (command == 0) {
            cout << "Thank you and have a great day!" << endl;
            break;
        } else {
            cout << "Which data structure you would like to use?" << endl;
            cout << "[1] Map" << endl;
            cout << "[2] Heap" << endl;

            int dataStructureChoice;
            cin >> dataStructureChoice;

            if (dataStructureChoice == 1) {
                readFile(transactionAmount, transactionInfo);
                if (command == 1) {
                    cout<<endl;
                    auto start = high_resolution_clock::now();
                    viewTop20Highest(transactionAmount, transactionInfo);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "This function execution took: " << duration.count() << " microsecond(s)" << endl;
                    cout<<endl;
                } else if (command == 2) {
                    cout<<endl;
                    auto start = high_resolution_clock::now();
                    viewTop20Lowest(transactionAmount, transactionInfo);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "This function execution took: " << duration.count() << " microsecond(s)" << endl;
                    cout<<endl;
                } else if (command == 3) {
                    string date;
                    cout << "Please enter the date (use this format: yyyy-mm-dd) on which you want to view the fraudulent transactions: " << endl;
                    cin >> date;
                    cout<<endl;
                    auto start = high_resolution_clock::now();
                    searchByDate(transactionAmount, transactionInfo, date);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "This function execution took: " << duration.count() << " microsecond(s)" << endl;
                    cout<<endl;
                } else if (command == 4) {
                    int category;
                    cout << "Product Categories:";
                    cout << "[1] clothing, [2] electronics, [3] health & beauty, [4] home & garden, [5] toys & games" << endl;
                    cout << "Please enter the number associated with the product category you want to view the fraudulent transactions: " << endl;
                    cin >> category;
                    cout<<endl;
                    auto start = high_resolution_clock::now();
                    if (category == 1) {searchByCategory(transactionAmount, transactionInfo, "clothing");}
                    else if (category == 2) {searchByCategory(transactionAmount, transactionInfo, "electronics");}
                    else if (category == 3) {searchByCategory(transactionAmount, transactionInfo, "health & beauty");}
                    else if (category == 4) {searchByCategory(transactionAmount, transactionInfo, "home & garden");}
                    else if (category == 5) {searchByCategory(transactionAmount, transactionInfo, "toys & games");}
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "This function execution took: " << duration.count() << " microsecond(s)" << endl;
                    cout<<endl;
                } else if (command == 5) {
                    int payment;
                    cout << "Payment Methods:";
                    cout << "[1] bank transfer, [2] credit card, [3] debit card, [4] PayPal" << endl;
                    cout << "Please enter the number associated with the payment method you want to view the fraudulent transactions: " << endl;
                    cin >> payment;
                    cout<<endl;
                    auto start = high_resolution_clock::now();
                    if (payment == 1) {searchByPaymentMethod(transactionAmount, transactionInfo, "bank transfer");}
                    else if (payment == 2) {searchByPaymentMethod(transactionAmount, transactionInfo, "credit card");}
                    else if (payment == 3) {searchByPaymentMethod(transactionAmount, transactionInfo, "debit card");}
                    else if (payment == 4) {searchByPaymentMethod(transactionAmount, transactionInfo, "PayPal");}
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "This function execution took: " << duration.count() << " microsecond(s)" << endl;
                    cout<<endl;
                }
            } else if (dataStructureChoice == 2) {
                readFileHeap(AmountMax, AmountMin, AgeMax, AgeMin, CategoryMax, CategoryMin, MethodMax, MethodMin);
                if (command == 1) {
                    cout<<endl;
                    auto start = high_resolution_clock::now();
                    AmountMax.print20();
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "This function execution took: " << duration.count() << " microsecond(s)" << endl;
                    cout<<endl;
                } else if (command == 2) {
                    cout<<endl;
                    auto start = high_resolution_clock::now();
                    AmountMin.print20();
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "This function execution took: " << duration.count() << " microsecond(s)" << endl;
                    cout<<endl;
                } else if (command == 3) {
                    string date;
                    cout << "Please enter the date (use this format: yyyy-mm-dd) on which you want to view the fraudulent transactions: " << endl;
                    cin >> date;
                    cout<<endl;
                    auto start = high_resolution_clock::now();
                    searchByDate(transactionAmount, transactionInfo, date);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "This function execution took: " << duration.count() << " microsecond(s)" << endl;
                    cout<<endl;
                } else if (command == 4) {
                    cout<<endl;
                    auto start = high_resolution_clock::now();
                    if(CategoryMax.peek()->at(5) == "electronics") cout << CategoryMax.pop();
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    cout << "This function execution took: " << duration.count() << " microsecond(s)" << endl;
                    cout<<endl;
                }
            }
        }
    }
    return 0;
}
