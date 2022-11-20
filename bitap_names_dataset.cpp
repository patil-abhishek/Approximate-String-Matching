#include <bits/stdc++.h>
using namespace std;

bool bitap(string name, string query, int dist)
{
    int nameLen = name.length();
    int queryLen = query.length();

    //* pre-processing
    unordered_map<char, int> alphabet;
    int pos;
    for(char i : name)
    {
        if (alphabet.find(i) == alphabet.end())
        {
            pos = 0;
            for (char j : query)
            {
                pos = pos << 1;
                pos |= int(i != j);
            }
            alphabet[i] = pos;
        }
    }
    int initVal = pow(2, queryLen) - 1;
    vector<vector<int>> table;
    table.push_back(vector<int>(nameLen + 1, initVal));
    table.push_back({initVal});
    int k = 1;
    int prev;
    int lp;
    int curr;
    string result;

    //*check exact matching  
    for (int i = 1; i < nameLen + 1; i++)
    {
        prev = (table[k][i - 1]) >> 1;
        lp = alphabet[name[i - 1]];
        curr = prev | lp;
        table[k].push_back(curr);
        if ((curr & 0x1) == 0)
            return true;
    }
    int ins, del, rep, res;
    int start, end;

    //*check matching with k-1 error in each iteration
    for (int k = 2; k < dist + 2; k++)
    {
        table.push_back({initVal});
        for (int i = 1; i < nameLen + 1; i++)
        {
            prev = (table[k][i - 1]) >> 1;
            lp = alphabet[name[i - 1]];
            curr = prev | lp;
            //*check if any of insertion, deletion or replacement solves the mismatch
            ins = curr & (table[k - 1][i - 1]);
            del = curr & (table[k - 1][i] >> 1);
            rep = curr & (table[k - 1][i - 1] >> 1);
            res = ins & del & rep;
            table[k].push_back(res);
            if ((res & 0x1) == 0)
                return true;
        }
    }
    return false;
}

int main()
{
    vector<string> names = {"Mehta", "Agarwal", "Gupta", "Aggarwal", "Sourav", "Abishek"};
    string query_string;
    int edit_dist_limit;
    cout << "the database is :" << endl;
    for (auto i : names)
    {
        cout << i << ", ";
    }
    cout << endl;
    cout << "enter name:" << endl;
    cin >> query_string;
    transform(query_string.begin(), query_string.end(), query_string.begin(), ::tolower);
    cout << "enter max error allowed (in terms of levenshtein distance):" << endl;
    cin >> edit_dist_limit;
    cout << "Results:\n";
    for (auto i : names)
    {
        string in_dataset = i;
        transform(in_dataset.begin(), in_dataset.end(), in_dataset.begin(), ::tolower);
        if(bitap(in_dataset, query_string, edit_dist_limit))
            cout << i << endl;
    }
    cout << "--End of Results--" << endl;
    return 0;
}