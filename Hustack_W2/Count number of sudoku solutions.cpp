/* Write a program to compute the number of sudoku solutions (fill the zero elements of a given partial sudoku table)
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
64 */

#include <bits/stdc++.h>
using namespace std;

const int SIZE = 9;
const int FULL_MASK = (1 << 9) - 1;

int board[SIZE][SIZE];
int rowMask[SIZE], colMask[SIZE], boxMask[SIZE];
long long answer = 0;

void dfs() {
    int bestRow = -1, bestCol = -1;
    int bestChoices = 10;

    for (int r = 0; r < SIZE; ++r) {
        for (int c = 0; c < SIZE; ++c) {
            if (board[r][c] == 0) {
                int box = (r / 3) * 3 + (c / 3);
                int available = FULL_MASK & ~(rowMask[r] | colMask[c] | boxMask[box]);
                int choices = __builtin_popcount(available);
                if (choices < bestChoices) {
                    bestChoices = choices;
                    bestRow = r;
                    bestCol = c;
                    if (choices == 1) {
                        r = SIZE;
                        c = SIZE;
                        break;
                    }
                }
            }
        }
    }

    if (bestRow == -1 && bestCol == -1) {
        ++answer;
        return;
    }

    int box = (bestRow / 3) * 3 + (bestCol / 3);
    int available = FULL_MASK & ~(rowMask[bestRow] | colMask[bestCol] | boxMask[box]);

    while (available) {
        int bit = available & -available;
        int digit = __builtin_ctz(bit) + 1;

        board[bestRow][bestCol] = digit;
        rowMask[bestRow] |= bit;
        colMask[bestCol] |= bit;
        boxMask[box] |= bit;

        dfs();

        boxMask[box] ^= bit;
        colMask[bestCol] ^= bit;
        rowMask[bestRow] ^= bit;
        board[bestRow][bestCol] = 0;

        available -= bit;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> board[i][j];
            if (board[i][j] != 0) {
                int bit = 1 << (board[i][j] - 1);
                rowMask[i] |= bit;
                colMask[j] |= bit;
                int box = (i / 3) * 3 + (j / 3);
                boxMask[box] |= bit;
            }
        }
    }

    dfs();
    cout << answer << '\n';
    return 0;
}

