#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minimum_platforms(vector<int> &a, vector<int> &d) {
    vector<int> tot(a);
    tot.insert(tot.end(), d.begin(), d.end());
    int pt = 0,mx=0;
    sort(tot.begin(), tot.end());
    for (int i = 0; i < tot.size(); i++) {
        if (find(a.begin(), a.end(), tot[i]) != a.end()) {
            
            pt++;
            mx = max(mx,pt);
        } else {
            
            pt--;
        }
    }
    return mx;
}

int main() {
    vector<int> a;
    vector<int> d;
    int n, m;
    
    cout << "Enter number of arrival and deprture times: ";
    cin >> n;
    cout << "Enter arrival times of trains: ";
    for (int i = 0; i < n; i++) {
        int time;
        cin >> time;
        a.push_back(time);
    }

    cout << "Enter departure times of trains: ";
    for (int i = 0; i < n; i++) {
        int time;
        cin >> time;
        d.push_back(time);
    }
    
    cout << "The minimum number of platforms required are: " << minimum_platforms(a, d) << endl;
    
    return 0;
}
