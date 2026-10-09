/* A knight starts from a cell (r, c) (row r and column c) in a chessboard of size NxN (rows and columns are indexed from 1, 2, ..., N). Each cell of a chessboard has an integer: G_{r,c} is the integer at the cell row r column c (1 <= r,c <= N). It wants to move to some cells (each cell is visited exactly once) of the chessboard. Find the route for the knight so that the sum of integers in cells of the route is maximal.

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
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

static const int dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
static const int dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

int main() {
    int N, r, c;
    cin >> N >> r >> c;

    vector<vector<int>> G(N + 1, vector<int>(N + 1, 0));
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> G[i][j];
        }
    }

    vector<vector<bool>> visited(N + 1, vector<bool>(N + 1, false));
    long long best = G[r][c];

    function<void(int, int, long long)> dfs = [&](int x, int y, long long sum) {
        best = max(best, sum);

        for (int k = 0; k < 8; ++k) {
            int nx = x + dr[k];
            int ny = y + dc[k];
            if (nx < 1 || nx > N || ny < 1 || ny > N) continue;
            if (visited[nx][ny]) continue;

            visited[nx][ny] = true;
            dfs(nx, ny, sum + G[nx][ny]);
            visited[nx][ny] = false;
        }
    };

    visited[r][c] = true;
    dfs(r, c, G[r][c]);

    cout << best << endl;
    return 0;
}
