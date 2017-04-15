#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct listItem{
    listItem *prev;
    listItem *next;
    int digit;
};

struct myList{
    listItem *head;
    listItem *tail;
};

void Init(myList *List){
    List->head = NULL;
    List->tail = NULL;
}

void Add(myList *List, int numb){
    listItem *temp = (listItem*)malloc (sizeof(listItem));
    temp->next = NULL;
    temp->prev = List->tail;
    temp->digit = numb;
    if (!List->head) List->head = temp;
    else List->tail->next = temp;
    List->tail = temp;
}

void Clear(myList* List){
    listItem *deleteList = List->head, *temp;
    while (deleteList){
        temp = deleteList;
        deleteList = deleteList->next;
        free(temp);
    }
    Init(List);
}

bool Check(myList *List){
    listItem *left = List->head, *right = List->tail;
    while (left){
        if (left->digit != right->digit) return false;
        left = left->next;
        right = right->prev;
    }
    return true;
}

int main(){
    setlocale(LC_ALL, "Russian");

    cout << "Введите строку:\n";
    string s;
    getline(cin, s);

    int n = s.length();
    myList List;
    Init(&List);
    for (int i = 0; i < n; ++i){
        if (s[i] != ' ' && s[i] != '.' && s[i] != ',' && s[i] != '!' && s[i] != '?' && s[i] != ';' && s[i] != ':' && s[i] != '-')
            Add(&List, int(s[i]));
    }
    if (Check(&List)) cout << "Строка является палиндромом";
    else cout << "Строка не является палиндромом";

    Clear(&List);
    return 0;
}
