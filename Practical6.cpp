#include <bits/stdc++.h>
using namespace std;

string input;
int pos = 0;

void L();
void L_dash();
void S();

void match(char t) {
    if (input[pos] == t) {
        pos++;
    } else {
        cout << "Invalid Expression" << endl;
        exit(0);
    }
}

void S() {
    if (input[pos] == '(') {
        match('(');
        L();
        match(')');
    } 
    else if (input[pos] == 'a') {
        match('a');
    } 
    else {
        cout << "Invalid Expression" << endl;
        exit(0);
    }
}

void L_dash() {
    if (input[pos] == ',') {
        match(',');
        S();
        L_dash();
    } else {
        return;
    }
}

void L(){
    S();
    L_dash();
}



int main() {
    cin >> input;
    input += '$'; 

    S();

    if (input[pos] == '$') {
        cout << "Valid Expression" << endl;
    } else {
        cout << "Invalid Expression" << endl;
    }

    return 0;
}
