#include <iostream>

using namespace std;

long long pre[100001];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    int x, y, z, t;
    cin >> n;
    pre[0] = 0;
    for (int i=1; i<=n; i++){
        long long v;
        cin >> v;
        pre[i] = pre[i-1] + v;
    }
    cin >> m;
    for(int i=0; i<m; i++){
        cin >> x >> y >> z >> t;
        long long sum1 = pre[y] - pre[x-1];
        long long sum2 = pre[t] - pre[z-1];
        cout << (sum1 < sum2 ? 1 : 0) << '\n';
    }
}
