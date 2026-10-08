/*At the beginning of the semester, the head of a computer science department D have to assign courses to teachers in a balanced way. The department D has m teachers T={1,2,...,m} and n courses C={1,2,...,n}. Each course i has credit crd(i) (i = 1,2,...,n). Each teacher t∈T has a preference list which is a list of courses he/she can teach depending on his/her specialization. 
Each teacher j has LB(j) which is the minimum number of courses assigned to her/him.
We known a list of pairs of conflicting two courses that cannot be assigned to the same teacher as these courses have been already scheduled in the same slot of the timetable. The load of a teacher is the sum of credits of courses assigned to her/him. How to assign nn courses to mm teacher such that each course assigned to a teacher is in his/her preference list, no two conflicting courses are assigned to the same teacher, and the maximal load is minimal.
Input
The input consists of following lines
Line 1: contains two integer m and n (1≤m≤10, 1≤n≤30)
Line i+1: contains an positive integer k and k positive integers indicating the courses that teacher i can teach (∀i=1,…,m)
Line m+2: contains crd(1), crd(2), . . ., crd(n) (1 <= crd(i) <= 10)
Line m+3: contains m integers LB(1), LB(2), . . ., LB(m);
Line m+4: contains an integer k
Line i+m+4: contains two integer i and j indicating two conflicting courses (∀i=1,…,k)
Output
The output contains a unique number which is the maximal load of the teachers in the solution found and the value -1 if not solution found.
Example
Input
4 12
5 1 3 5 10 12
5 9 3 4 8 12
6 1 2 3 4 9 7
7 1 2 3 5 6 10 11
2 3 3 2 1 2 3 2 2 2 3 1
3 1 1 1
25
1 2
1 3
1 5
2 4
2 5
2 6
3 5
3 7
3 10
4 6
4 9
5 6
5 7
5 8
6 8
6 9
7 8
7 10
7 11
8 9
8 11
8 12
9 12
10 11
11 12


Output
8
*/
#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int m, n, K;
bool canTeach[15][35];
int crd[35], LB[15];
long long conflict[35];

int order[35];
int canRem[15][35];
int sufCrd[35];

long long assigned[15];
int load[15], cnt[15];
int best = INF;
bool same[15][15];

void Try(int i, int curMax, int sumLoad) {
    if (curMax >= best) return;

    if ((sumLoad + sufCrd[i] + m - 1) / m >= best) return;

    int need = 0;
    for (int t = 0; t < m; t++) {
        int d = LB[t] - cnt[t];
        if (d <= 0) continue;
        if (d > canRem[t][i]) return;
        need += d;
    }
    if (need > n - i) return;

    if (i == n) {
        best = curMax;
        return;
    }

    int c = order[i];

    int cand[15], numCand = 0;
    for (int t = 0; t < m; t++) {
        if (!canTeach[t][c]) continue;
        if (conflict[c] & assigned[t]) continue;
        if (load[t] + crd[c] >= best) continue;

        bool skip = false;
        if (cnt[t] == 0) {
            for (int u = 0; u < t; u++) {
                if (same[u][t] && cnt[u] == 0) {
                    skip = true;
                    break;
                }
            }
        }
        if (!skip) cand[numCand++] = t;
    }
    sort(cand, cand + numCand, [](int a, int b) { return load[a] < load[b]; });

    for (int j = 0; j < numCand; j++) {
        int t = cand[j];

        assigned[t] |= 1LL << c;
        load[t] += crd[c];
        cnt[t]++;
        Try(i + 1, max(curMax, load[t]), sumLoad + crd[c]);
        assigned[t] &= ~(1LL << c);
        load[t] -= crd[c];
        cnt[t]--;
    }
}

int main () {
    cin >> m >> n;
    for (int t = 0; t < m; t++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int c;
            cin >> c;
            canTeach[t][c - 1] = true;
        }
    }
    for (int i = 0; i < n; i++) cin >> crd[i];
    for (int t = 0; t < m; t++) cin >> LB[t];
    cin >> K;
    for (int j = 0; j < K; j++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        conflict[a] |= 1LL << b;
        conflict[b] |= 1LL << a;
    }

    int numTeachers[35] = {0};
    for (int i = 0; i < n; i++) {
        order[i] = i;
        for (int t = 0; t < m; t++) numTeachers[i] += canTeach[t][i];
        if (numTeachers[i] == 0) {
            cout << -1;
            return 0;
        }
    }
    sort(order, order + n, [&](int a, int b) {
        if (numTeachers[a] != numTeachers[b]) return numTeachers[a] < numTeachers[b];
        return crd[a] > crd[b];
    });

    for (int i = n - 1; i >= 0; i--) {
        sufCrd[i] = sufCrd[i + 1] + crd[order[i]];
        for (int t = 0; t < m; t++) canRem[t][i] = canRem[t][i + 1] + canTeach[t][order[i]];
    }

    for (int u = 0; u < m; u++) {
        for (int t = 0; t < m; t++) {
            same[u][t] = (LB[u] == LB[t]);
            for (int c = 0; c < n && same[u][t]; c++) {
                if (canTeach[u][c] != canTeach[t][c]) same[u][t] = false;
            }
        }
    }

    Try(0, 0, 0);

    cout << (best == INF ? -1 : best);

    return 0;
}
