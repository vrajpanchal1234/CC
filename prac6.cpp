#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

string l;
int pos = 0;

// function declarations
void S();
void L();
void L_();

// match function
void match(char t) {
    if (l[pos] == t) {
        pos++;
    } else {
        cout << "Invalid string";
        exit(0);
    }
}

// S → ( L ) | a
void S() {
    if (l[pos] == 'a') {
        match('a');
    }
    else if (l[pos] == '(') {
        match('(');
        L();
        match(')');
    }
    else {
        cout << "Invalid string";
        exit(0);
    }
}

// L → S L’
void L() {
    S();
    L_();
}

// L’ → , S L’ | ε
void L_() {
    if (l[pos] == ',') {
        match(',');
        S();
        L_();
    }
    // ε → do nothing
}

int main() {
    cout << "Enter string: ";
    cin >> l;

    l += '$';   // End marker
    S();

    if (l[pos] == '$')
        cout << "Valid string";
    else
        cout << "Invalid string";

    return 0;
}
