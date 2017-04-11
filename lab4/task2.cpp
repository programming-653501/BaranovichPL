#include <iostream>

using namespace std;

bool check_balance(string &str){
    int balance = 0;
    for (int i = 0; i < str.length(); ++i){
        if (str[i] == '(') ++balance;
        else --balance;
        if (balance < 0) return false;
    }
    if (balance) return false;
    else return true;
}

int main()
{
    string str;
    cin >> str;
    int n = str.length(), amount = 0;
    int *bracketsPosition = new int[n];

    if (check_balance(str)){
        for (int i = 0; i < n; ++i){
            if (str[i] == '(') bracketsPosition[amount++] = i;
            else{
                if (amount == 2){
                    str[bracketsPosition[--amount]] = '[';
                    str[i] = ']';
                }
                else if (amount > 2){
                    str[bracketsPosition[--amount]] = '{';
                    str[i] = '}';
                }
                else --amount;
            }
        }
    }

    cout << str;
    delete[] bracketsPosition;
    return 0;
}
