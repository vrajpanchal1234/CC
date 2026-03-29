#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>
using namespace std;

map<char, vector<string>> prod;
map<char, set<char>> FIRST, FOLLOW;

// store multiple rules (to detect conflict)
map<char, map<char, vector<string>>> table;

bool isNT(char c)
{
    return (c >= 'A' && c <= 'Z');
}

// ---------- FIRST of string ----------
set<char> firstOf(string s)
{
    set<char> res;

    if (s == "#")
    {
        res.insert('#');
        return res;
    }

    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i];

        if (!isNT(ch))
        {
            res.insert(ch);
            return res;
        }

        for (char c : FIRST[ch])
            if (c != '#')
                res.insert(c);

        if (!FIRST[ch].count('#'))
            return res;

        if (i == s.length() - 1)
            res.insert('#');
    }

    return res;
}

// ---------- Build Parsing Table ----------
bool buildTable()
{
    bool isLL1 = true;

    for (auto p : prod)
    {
        char A = p.first;

        for (auto rule : p.second)
        {

            set<char> f = firstOf(rule);

            for (char t : f)
            {
                if (t != '#')
                {
                    table[A][t].push_back(rule);

                    if (table[A][t].size() > 1)
                        isLL1 = false;
                }
            }

            if (f.count('#'))
            {
                for (char b : FOLLOW[A])
                {
                    table[A][b].push_back("#");

                    if (table[A][b].size() > 1)
                        isLL1 = false;
                }
            }
        }
    }

    return isLL1;
}

// ---------- Print Table ----------
void printTable()
{
    cout << "\nPredictive Parsing Table:\n";

    for (auto row : table)
    {
        for (auto col : row.second)
        {
            cout << "M[" << row.first << "," << col.first << "] = ";

            for (auto r : col.second)
                cout << row.first << "->" << r << "  ";

            cout << endl;
        }
    }
}

// ---------- Parse ----------
bool parse(string input)
{

    stack<char> st;
    st.push('$');
    st.push('S');

    input += '$';
    int i = 0;

    while (!st.empty())
    {

        char top = st.top();
        char cur = input[i];

        if (top == cur)
        {
            st.pop();
            i++;
        }
        else if (!isNT(top))
        {
            return false;
        }
        else
        {
            if (table[top][cur].empty())
                return false;

            // take first rule
            string rule = table[top][cur][0];
            st.pop();

            if (rule != "#")
            {
                for (int j = rule.length() - 1; j >= 0; j--)
                    st.push(rule[j]);
            }
        }
    }

    return (i == input.length());
}

// ---------- MAIN ----------
int main()
{

    // Grammar
    prod['S'] = {"ABC", "D"};
    prod['A'] = {"a", "#"};
    prod['B'] = {"b", "#"};
    prod['C'] = {"(S)", "c"};
    prod['D'] = {"AC"};

    // FIRST (from Practical 7)
    FIRST['S'] = {'a','b','(','c'};
    FIRST['A'] = {'a','#'};
    FIRST['B'] = {'b','#'};
    FIRST['C'] = {'(','c'};
    FIRST['D'] = {'a','(','c'};

    // FOLLOW (from Practical 7)
    FOLLOW['S'] = {')','$'};
    FOLLOW['A'] = {'b','(','c'};
    FOLLOW['B'] = {'(','c'};
    FOLLOW['C'] = {')','$'};
    FOLLOW['D'] = {')','$'};

    // Build table
    bool isLL1 = buildTable();

    printTable();

    cout << "\nGrammar is ";
    if (isLL1) cout << "LL(1)\n";
    else cout << "NOT LL(1)\n";

    // If NOT LL(1), stop
    if (!isLL1)
    {
        cout << "\nParsing cannot be performed because grammar is not LL(1)\n";
        return 0;
    }

    // Input loop (only if LL1)
    string input;

    while (true)
    {
        cout << "\nEnter string (type 'exit' to stop): ";
        cin >> input;

        if (input == "exit")
            break;

        if (parse(input))
            cout << "Valid string\n";
        else
            cout << "Invalid string\n";
    }

    return 0;
}
