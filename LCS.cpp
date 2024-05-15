#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// Function to compute the lengths of Longest Common Subsequences (LCS)
vector<vector<int>> LCSLengths(const string& s1, const string& s2) {
    int a = s1.length();
    int b = s2.length();
//To store the lengths of LCS
    vector<vector<int>> c(a + 1, vector<int>(b + 1, 0));

    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
            } else {
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
            }
        }
    }

    return c;
}
//Function to construct LCS from LCS lengths
string constructLCS(const string& s1, const string& s2, const vector<vector<int>>& c) {
    int i = s1.length();
    int j = s2.length();
    int index = c[i][j] - 1;
    string lcs(c[i][j], ' ');

    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs[index] = s1[i - 1];
            i--;
            j--;
            index--;
        } else if (c[i - 1][j] > c[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return lcs;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: LCS <input-string1> <input-string2>" << endl;
        return 1;
    }

    string s1 = argv[1];
    string s2 = argv[2];
//compute the LCS lengths for the input strings
    vector<vector<int>> c = LCSLengths(s1, s2);

    int lcsLength = c[s1.length()][s2.length()];
    string lcs = constructLCS(s1, s2, c);
//output the length of LCS and lcs
    cout << "Length of LCS: " << lcsLength << endl;
    cout << "LCS: " << lcs << endl;

    return 0;
}
