/*Write a program to compute the number of sudoku solutions (fill the zero elements of a given partial sudoku table)
Fill numbers from 1, 2, 3, .., 9 to 9 x 9 table so that:
Numbers of each row are distinct
Numbers of each column are distinct
Numbers on each sub-square 3 x 3 are distinct
Input
Each line i (i = 1, 2, ..., 9) contains elements of the i
th
 row of the Sudoku table: elements are numbers from 0 to 9 (value 0 means the empty cell of the table)
Output
Write the number of solutions found

Example
Input
0 0 3 4 0 0 0 8 9
0 0 6 7 8 9 0 2 3
0 8 0 0 2 3 4 5 6
0 0 4 0 6 5 0 9 7
0 6 0 0 9 0 0 1 4
0 0 7 2 0 4 3 6 5
0 3 0 6 0 2 0 7 8
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
Output
64
*/
#include <iostream>

using namespace std;

int a[9][9];
int rowMask[9], colMask[9], boxMask[9];
long long cnt = 0;

int box(int i, int j) {
    return (i / 3) * 3 + j / 3;
}

void Try() {
    int bi = -1, bj = -1, best = 10;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (a[i][j] != 0) continue;
            int used = rowMask[i] | colMask[j] | boxMask[box(i, j)];
            int c = 9 - __builtin_popcount(used >> 1);
            if (c < best) {
                best = c;
                bi = i;
                bj = j;
            }
        }
    }

    if (bi == -1) {
        cnt++;
        return;
    }
    if (best == 0) return;

    int b = box(bi, bj);
    int used = rowMask[bi] | colMask[bj] | boxMask[b];
    for (int v = 1; v <= 9; v++) {
        if (used & (1 << v)) continue;
        a[bi][bj] = v;
        rowMask[bi] |= 1 << v;
        colMask[bj] |= 1 << v;
        boxMask[b] |= 1 << v;
        Try();
        rowMask[bi] &= ~(1 << v);
        colMask[bj] &= ~(1 << v);
        boxMask[b] &= ~(1 << v);
        a[bi][bj] = 0;
    }
}

int main () {
    bool valid = true;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> a[i][j];
            int v = a[i][j];
            if (v == 0) continue;
            int b = box(i, j);
            if ((rowMask[i] | colMask[j] | boxMask[b]) & (1 << v)) valid = false;
            rowMask[i] |= 1 << v;
            colMask[j] |= 1 << v;
            boxMask[b] |= 1 << v;
        }
    }

    if (valid) Try();
    cout << cnt;

    return 0;
}
