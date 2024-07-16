#include <bits/stdc++.h>
using namespace std;

int maxProjectValue(int N, vector<int>& values, vector<vector<string>>& required_languages, set<string>& known_languages) {
    int max_value = 0;
    
    for (int i = 0; i < N; ++i) {
        bool can_complete = true;
        for (const string& lang : required_languages[i]) {
            if (known_languages.find(lang) == known_languages.end()) {
                can_complete = false;
                break;
            }
        }
        if (can_complete) {
            max_value += values[i];
        }
    }
    
    return max_value;
}

int main() {
    int N;
    cin >> N;  // Number of projects

    vector<int> values(N);
    for (int i = 0; i < N; ++i) {
        cin >> values[i];  // Values of the projects
    }

    vector<vector<string>> required_languages(N);
    for (int i = 0; i < N; ++i) {
        int num_languages;
        cin >> num_languages;  // Number of languages required for the i-th project
        required_languages[i].resize(num_languages);
        for (int j = 0; j < num_languages; ++j) {
            cin >> required_languages[i][j];
        }
    }

    int num_known_languages;
    cin >> num_known_languages;  // Number of languages you know
    set<string> known_languages;
    for (int i = 0; i < num_known_languages; ++i) {
        string lang;
        cin >> lang;
        known_languages.insert(lang);
    }

    int result = maxProjectValue(N, values, required_languages, known_languages);
    cout << "Maximum Project Value: " << result << endl;

    return 0;
}
