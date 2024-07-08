#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct Cell {
    int x, y, z, dist;
};

bool isValid(int x, int y, int z, int X, int Y, int Z, vector<vector<vector<int>>>& grid, vector<vector<vector<bool>>>& visited) {
    return (x >= 0 && x < X && y >= 0 && y < Y && z >= 0 && z < Z && grid[x][y][z] == 0 && !visited[x][y][z]);
}

int shortestPath3DGrid(vector<vector<vector<int>>>& grid, int xs, int ys, int zs, int xd, int yd, int zd) {
    int X = grid.size();
    int Y = grid[0].size();
    int Z = grid[0][0].size();

    vector<vector<vector<bool>>> visited(X, vector<vector<bool>>(Y, vector<bool>(Z, false)));
    vector<int> dx = {1, -1, 0, 0, 0, 0};
    vector<int> dy = {0, 0, 1, -1, 0, 0};
    vector<int> dz = {0, 0, 0, 0, 1, -1};

    queue<Cell> q;
    q.push({xs, ys, zs, 0});
    visited[xs][ys][zs] = true;

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();

        int x = current.x;
        int y = current.y;
        int z = current.z;
        int dist = current.dist;

        if (x == xd && y == yd && z == zd) {
            return dist;
        }

        for (int i = 0; i < 6; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            int newZ = z + dz[i];

            if (isValid(newX, newY, newZ, X, Y, Z, grid, visited)) {
                visited[newX][newY][newZ] = true;
                q.push({newX, newY, newZ, dist + 1});
            }
        }
    }

    return -1;
}

int main() {
    int X, Y, Z;
    cin >> X >> Y >> Z;

    int xs, ys, zs, xd, yd, zd;
    cin >> xs >> ys >> zs >> xd >> yd >> zd;

    vector<vector<vector<int>>> grid(X, vector<vector<int>>(Y, vector<int>(Z)));

    for (int i = 0; i < X; ++i) {
        for (int j = 0; j < Y; ++j) {
            for (int k = 0; k < Z; ++k) {
                cin >> grid[i][j][k];
            }
        }
    }

    int result = shortestPath3DGrid(grid, xs, ys, zs, xd, yd, zd);

    if (result != -1) {
        cout << "Shortest Path Distance: " << result << endl;
    } else {
        cout << "No Path Found" << endl;
    }

    return 0;
}
