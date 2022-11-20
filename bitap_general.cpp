#include <bits/stdc++.h>
using namespace std;

pair<string, int> bitap(string name, string query, int dist)
{
    int nameLen = name.length();
    int queryLen = query.length();
    unordered_map<char, int> alphabet;
    int pos;
    for (char i : name)
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
    for (int i = 1; i < nameLen + 1; i++)
    {
        prev = (table[k][i - 1]) >> 1;
        lp = alphabet[name[i - 1]];
        curr = prev | lp;
        table[k].push_back(curr);
        if ((curr & 0x1) == 0)
            return (make_pair(name.substr(i - queryLen, queryLen), k - 1));
    }
    int ins, del, rep, res;
    int start, end;
    for (int k = 2; k < dist + 2; k++)
    {
        table.push_back({initVal});
        for (int i = 1; i < nameLen + 1; i++)
        {
            prev = (table[k][i - 1]) >> 1;
            lp = alphabet[name[i - 1]];
            curr = prev | lp;
            ins = curr & (table[k - 1][i - 1]);
            del = curr & (table[k - 1][i] >> 1);
            rep = curr & (table[k - 1][i - 1] >> 1);
            res = ins & del & rep;
            table[k].push_back(res);
            if ((res & 0x1) == 0)
            {
                start = max(0, i - queryLen - 1);
                end = min(i + 1, nameLen);
                return (make_pair(name.substr(start, end - start), k - 1));
            }
        }
    }
    return make_pair("", -1);
}

int main()
{
    string text = "AbCDeFghiJklMnOpQRstuVwxyZ";
    string query_string;
    int edit_dist_limit;
    cout << "enter string to be searched:" << endl;
    cin >> query_string;
    cout << "enter max error allowed (in terms of levenshtein distance):" << endl;
    cin >> edit_dist_limit;
    pair<string, int> result;
    transform(query_string.begin(), query_string.end(), query_string.begin(), ::tolower);
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    result = bitap(text, query_string, edit_dist_limit);
    if (result.second != -1)
        cout << "found - " << result.first << "\nerror = "<<result.second;
    else
        cout << "Not found" << endl;
    return 0;
}