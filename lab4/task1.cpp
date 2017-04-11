#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    string str;
    getline(cin, str);

    for (int i = 0; i < int(str.length()) - 1; ++i){
        if (str[i] == str[i + 1] && str[i] == ' '){
            str.erase(i, 1);
            --i;
        }
    }
    string punctuationMarks = "?.:;,!";
    int findPosition;
    for (int i = 0; i < int(str.length()) - 1; ++i){
        findPosition = punctuationMarks.find(str[i]);
        if (findPosition < str.length() && findPosition >= 0 && str[i + 1] != ' ')
            str.insert(i + 1, " ");
    }
    for (int i = 0; i < int(str.length()) - 2; ++i){
        if ((str[i] == '!' || str[i] == '.' || str[i] == '?'))
            str[i + 2] = toupper(str[i + 2]);
    }

    cout << str;
    return 0;
}
