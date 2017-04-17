#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct treeItem {
    treeItem *left;
    treeItem *right;
    int digit;
};

void TreeClear(treeItem *root) {
    if(!root) return;
    TreeClear(root->left);
    TreeClear(root->right);
    delete root;
}

int GetSum(treeItem *root) {
    if(!root) return 0;
    int sum = root->digit;
    sum += GetSum(root->left);
    sum += GetSum(root->right);
    return sum;
}

treeItem *CreateTreeItem(int digit) {
    treeItem *item = new treeItem;
    item->left = NULL;
    item->right = NULL;
    item->digit = digit;
    return item;
}

treeItem *TreeAdd(treeItem *tree, int digit) {
    if(!tree) return CreateTreeItem(digit);
    treeItem *root = tree;
    while(1) {
        if (root->digit == digit) return tree;
        if(digit < root->digit) {
            if (root->left) root = root->left;
            else {
                root->left = CreateTreeItem(digit);
                return tree;
            }
        }
        else {
            if (root->right) root = root->right;
            else {
                root->right = CreateTreeItem(digit);
                return tree;
            }
        }
    }
}

void TreePrint(treeItem *root) {
    if(!root) return;
    cout << root->digit << "(";
    TreePrint(root->left);
    cout << ",";
    TreePrint(root->right);
    cout << ")";
}

int main() {
    setlocale(LC_ALL, "Russian");
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    treeItem *root[1111] = {NULL};
    int n, count = 0, number, value;

    cout << "Введите количество чисел в стеке: ";
    cin >> n;
    cout << "Введите элементы стека:\n";
    for (int i = 0; i < n; ++i) {
        cin >> number >> value;
        count = max(number, count);
        root[number] = TreeAdd(root[number], value);
    }

    for (int i = 1; i <= count; ++i) {
        cout << "Сумма чисел в дереве номер " << i << " равна: ";
        cout << GetSum(root[i]) << endl;
    }

 /*   for (int i = 1; i <= count; ++i) {
        TreePrint(root[i]);
        cout << endl;
    } */

    for (int i = 0; i <= count; ++i)
        TreeClear(root[i]);
    return 0;
}
