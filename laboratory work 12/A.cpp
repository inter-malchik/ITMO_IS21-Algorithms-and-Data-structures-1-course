#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    unsigned n;
    cin >> n;
    vector<int> arr(n);
    for (unsigned i = 0; i < n; ++i)
        cin >> arr[i];

    vector<int> d(n, 0);
    vector<int> pr(n, -1);
    for (int i = 0; i < n; i++) {
        d[i] = 1;
        for (int j = 0; j < i; j++)
            if (arr[j] < arr[i]) {
                d[i] = max(d[i], d[j] + 1);
                if (d[i] == d[j] + 1)
                    pr[i] = j;
            }
    }

    int maxi = d[0];
    int ind = 0;

    for (int i = 1; i < n; i++)
        if (d[i] > maxi) {
            maxi = d[i];
            ind = i;
        }

    cout << maxi << endl;
    vector<int> ans;
    while (ind != -1) {
        ans.push_back(ind);
        ind = pr[ind];
    }

    for (int i = ans.size() - 1; i >= 0; i--)
        cout << arr[ans[i]] << ' ';
}