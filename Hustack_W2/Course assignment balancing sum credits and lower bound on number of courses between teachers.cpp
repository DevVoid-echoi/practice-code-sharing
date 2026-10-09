/* At the beginning of the semester, the head of a computer science department D have to assign courses to teachers in a balanced way. The department D has m teachers T={1,2,...,m} and n courses C={1,2,...,n}. Each course i has credit crd(i) (i = 1,2,...,n). Each teacher t∈T has a preference list which is a list of courses he/she can teach depending on his/her specialization. 
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
8 */

#include <bits/stdc++.h>
using namespace std;

class CourseAssignment {
private:
    int m, n;
    vector<int> credits;
    vector<vector<int>> allowed;
    vector<int> LB;
    vector<int> conflictMask;
    int limit;

    vector<int> load, cnt, used;
    vector<bool> assigned;

    bool canPlace(int teacher, int course) const {
        if (!(allowed[teacher][course])) return false;
        if (load[teacher] + credits[course] > limit) return false;
        if ((used[teacher] & conflictMask[course]) != 0) return false;
        return true;
    }

    int remainingPossibleCourses(int teacher) const {
        int res = 0;
        for (int c = 0; c < n; ++c) {
            if (!assigned[c]) {
                if (allowed[teacher][c] && (used[teacher] & conflictMask[c]) == 0) {
                    ++res;
                }
            }
        }
        return res;
    }

    bool dfs() {
        bool allAssigned = true;
        int bestCourse = -1;
        int bestOptions = INT_MAX;

        for (int c = 0; c < n; ++c) {
            if (assigned[c]) continue;
            allAssigned = false;

            vector<int> options;
            for (int t = 0; t < m; ++t) {
                if (canPlace(t, c)) {
                    options.push_back(t);
                }
            }

            if (options.empty()) return false;
            if ((int)options.size() < bestOptions) {
                bestOptions = (int)options.size();
                bestCourse = c;
                if (bestOptions == 1) break;
            }
        }

        if (allAssigned) {
            for (int t = 0; t < m; ++t) {
                if (cnt[t] < LB[t]) return false;
            }
            return true;
        }

        for (int t = 0; t < m; ++t) {
            if (cnt[t] + remainingPossibleCourses(t) < LB[t]) {
                return false;
            }
        }

        vector<int> options;
        for (int t = 0; t < m; ++t) {
            if (canPlace(t, bestCourse)) options.push_back(t);
        }

        for (int t : options) {
            assigned[bestCourse] = true;
            load[t] += credits[bestCourse];
            cnt[t]++;
            used[t] |= (1 << bestCourse);

            if (dfs()) return true;

            used[t] &= ~(1 << bestCourse);
            cnt[t]--;
            load[t] -= credits[bestCourse];
            assigned[bestCourse] = false;
        }

        return false;
    }

public:
    bool possible(int cap) {
        limit = cap;
        load.assign(m, 0);
        cnt.assign(m, 0);
        used.assign(m, 0);
        assigned.assign(n, false);
        return dfs();
    }

    void readInput() {
        cin >> m >> n;
        allowed.assign(m, vector<int>(n, 0));
        int k;
        for (int i = 0; i < m; ++i) {
            cin >> k;
            for (int j = 0; j < k; ++j) {
                int x;
                cin >> x;
                x--;
                allowed[i][x] = 1;
            }
        }

        credits.resize(n);
        for (int i = 0; i < n; ++i) cin >> credits[i];

        LB.resize(m);
        for (int i = 0; i < m; ++i) cin >> LB[i];

        int conflictCount;
        cin >> conflictCount;
        conflictMask.assign(n, 0);
        for (int i = 0; i < conflictCount; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            conflictMask[a] |= (1 << b);
            conflictMask[b] |= (1 << a);
        }
    }

    int totalCredits() const {
        int sum = 0;
        for (int x : credits) sum += x;
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    CourseAssignment solver;
    solver.readInput();

    int totalCredits = solver.totalCredits();

    int lo = 0, hi = totalCredits;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (solver.possible(mid)) hi = mid;
        else lo = mid + 1;
    }

    if (solver.possible(lo)) {
        cout << lo << '\n';
    } else {
        cout << -1 << '\n';
    }

    return 0;
}

