#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1000000001

int main() {
    unsigned n;
    cin >> n;
    vector<int> arr(n);
    for (unsigned i = 0; i < n; ++i)
        cin >> arr[i];

    vector<int> d(n+1, INF);
    d[0] = -INF;
    vector<int> parent(n+1, -1);
    vector<int> lens(n+1, -1);

    int maxi = d[0];

    for (int i = 0; i<n; i++) {
        int j = (int) (upper_bound (d.begin(), d.end(), arr[i]) - d.begin());
        if (d[j-1] < arr[i] && arr[i] < d[j]) {
            d[j] = arr[i];
            lens[j] = i;
            parent[i] = lens[j - 1];
            maxi = max(j, maxi);
            }
    }

    int ind = lens[maxi];

    cout << maxi << endl;

    vector<int> ans;
    while (ind != -1) {
        ans.push_back(ind);
        ind = parent[ind];
    }

    for (int i = ans.size() - 1; i >= 0; i--)
        cout << arr[ans[i]] << ' ';
}