#include <bits/stdc++.h>
using namespace std;

bool isKeyword(const string &s)
{
    static set<string> keywords = {
        "auto","break","case","char","const","continue","default","do",
        "double","else","enum","extern","float","for","goto","if",
        "int","long","register","return","short","signed","sizeof","static",
        "struct","switch","typedef","union","unsigned","void","volatile","while"};
    return keywords.count(s);
}

int main()
{
    ifstream file("test1.c");
    if (!file)
    {
        cout << "File not found!" << endl;
        return 1;
    }

    vector<string> tokens;
    vector<string> lexicalErrors;
    set<string> symbolTable;

    string operators = "+-*/%=&|^~<>!";
    string punctuations = ".,;:(){}[]#";

    string line;
    int lineNo = 0;

    while (getline(file, line))
    {
        lineNo++;

        /* Remove single-line comments */
        size_t pos = line.find("//");
        if (pos != string::npos)
            line = line.substr(0, pos);

        for (size_t i = 0; i < line.size();)
        {
            if (isspace(line[i]))
            {
                i++;
                continue;
            }

            /* Identifier or Keyword */
            if (isalpha(line[i]) || line[i] == '_')
            {
                size_t j = i;
                while (j < line.size() && (isalnum(line[j]) || line[j] == '_'))
                    j++;

                string word = line.substr(i, j - i);

                if (isKeyword(word))
                    tokens.push_back("Keyword: " + word);
                else
                {
                    tokens.push_back("Identifier: " + word);
                    symbolTable.insert(word);
                }

                i = j;
            }

            /* Numeric Constant or Invalid Lexeme */
            else if (isdigit(line[i]))
            {
                size_t j = i;
                while (j < line.size() && isalnum(line[j]))
                    j++;

                string num = line.substr(i, j - i);

                if (all_of(num.begin(), num.end(), ::isdigit))
                    tokens.push_back("Constant: " + num);
                else
                    lexicalErrors.push_back("Line " + to_string(lineNo) +
                                             " : " + num + " invalid lexeme");

                i = j;
            }

            else if (line[i] == '\'')
            {
                size_t j = i + 1;
                while (j < line.size() && line[j] != '\'')
                    j++;
                j++;

                tokens.push_back("Constant: " + line.substr(i, j - i));
                i = j;
            }

            else if (operators.find(line[i]) != string::npos)
            {
                tokens.push_back("Operator: " + string(1, line[i]));
                i++;
            }

            else if (punctuations.find(line[i]) != string::npos)
            {
                tokens.push_back("Punctuation: " + string(1, line[i]));
                i++;
            }

            else
            {
                i++;
            }
        }
    }

    /* OUTPUT FORMAT */

    cout << "TOKENS\n";
    for (auto &t : tokens)
        cout << t << endl;

    cout << "\nLEXICAL ERRORS\n";
    if (lexicalErrors.empty())
        cout << "None\n";
    else
        for (auto &e : lexicalErrors)
            cout << e << endl;

    cout << "\nSYMBOL TABLE ENTRIES\n";
    int idx = 1;
    for (auto &s : symbolTable)
        cout << idx++ << ") " << s << endl;

    return 0;
}