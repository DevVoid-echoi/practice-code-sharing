/*A knight starts from a cell (r, c) (row r and column c) in a chessboard of size NxN (rows and columns are indexed from 1, 2, ..., N). Each cell of a chessboard has an integer: G_{r,c} is the integer at the cell row r column c (1 <= r,c <= N). It wants to move to some cells (each cell is visited exactly once) of the chessboard. Find the route for the knight so that the sum of integers in cells of the route is maximal.

Input
Line 1: contains 3 integers N, r and c (1 <= N <= 10, 1 <= r,c <= N)
Line i+1 (i = 1, 2, ..., N): contains the ith row of the matrix G

Output
Write the sum of the numbers of the cells visited by the knight in the route found.

Example
Input
4 1 1 
3  4  8  7    
0  3  0  0   
2  0 -10 0  
0 -4  0 10    


Output
31

Explanation: the route found is: (1,1) (2,3) (4,4) (3,2) (1,3) (3,4) (2,2) (1,4)*/

#include <iostream>
#include <algorithm>

using namespace std;

const int dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

int N;
int G[12][12];
bool visited[12][12];
bool seen[12][12];
long long best;
long long target;
bool done = false;
int qr[150], qc[150];

bool inside(int r, int c) {
    return r >= 1 && r <= N && c >= 1 && c <= N;
}

long long reachablePositive(int r, int c) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            seen[i][j] = false;

    int head = 0, tail = 0;
    qr[tail] = r; qc[tail] = c; tail++;
    seen[r][c] = true;
    long long s = 0;
    while (head < tail) {
        int ur = qr[head], uc = qc[head]; head++;
        for (int d = 0; d < 8; d++) {
            int vr = ur + dr[d], vc = uc + dc[d];
            if (!inside(vr, vc) || visited[vr][vc] || seen[vr][vc]) continue;
            seen[vr][vc] = true;
            if (G[vr][vc] > 0) s += G[vr][vc];
            qr[tail] = vr; qc[tail] = vc; tail++;
        }
    }
    return s;
}

int degree(int r, int c) {
    int k = 0;
    for (int d = 0; d < 8; d++) {
        int vr = r + dr[d], vc = c + dc[d];
        if (inside(vr, vc) && !visited[vr][vc]) k++;
    }
    return k;
}

void Try(int r, int c, long long cur) {
    if (done) return;
    if (cur > best) {
        best = cur;
        if (best == target) {
            done = true;
            return;
        }
    }
    if (cur + reachablePositive(r, c) <= best) return;

    int nr[8], nc[8], deg[8], cnt = 0;
    for (int d = 0; d < 8; d++) {
        int vr = r + dr[d], vc = c + dc[d];
        if (!inside(vr, vc) || visited[vr][vc]) continue;
        nr[cnt] = vr; nc[cnt] = vc; cnt++;
    }
    for (int i = 0; i < cnt; i++) {
        visited[nr[i]][nc[i]] = true;
        deg[i] = degree(nr[i], nc[i]);
        visited[nr[i]][nc[i]] = false;
    }

    int idx[8];
    for (int i = 0; i < cnt; i++) idx[i] = i;
    sort(idx, idx + cnt, [&](int a, int b) {
        if (deg[a] != deg[b]) return deg[a] < deg[b];
        return G[nr[a]][nc[a]] > G[nr[b]][nc[b]];
    });

    for (int j = 0; j < cnt; j++) {
        int i = idx[j];
        visited[nr[i]][nc[i]] = true;
        Try(nr[i], nc[i], cur + G[nr[i]][nc[i]]);
        visited[nr[i]][nc[i]] = false;
        if (done) return;
    }
}

int main () {
    int r, c;
    cin >> N >> r >> c;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> G[i][j];

    visited[r][c] = true;
    best = G[r][c];
    target = G[r][c] + reachablePositive(r, c);
    Try(r, c, G[r][c]);

    cout << best;

    return 0;
}
