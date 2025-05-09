#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

int W, H, N;

// Получить все клетки прямоугольника
vector<pair<int, int>> get_cells(int x1, int y1, int x2, int y2) {
    vector<pair<int, int>> cells;
    for (int x = x1; x <= x2; ++x) {
        for (int y = y1; y <= y2; ++y) {
            cells.emplace_back(x, y);
        }
    }
    return cells;
}

// Проверка, можно ли перейти из одного множества клеток в другое за один ход
bool can_move(const vector<pair<int, int>>& from, const vector<pair<int, int>>& to) {
    set<pair<int, int>> to_set(to.begin(), to.end());
    for (auto& [x1, y1] : from) {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (abs(dx) + abs(dy) != 1) continue;
                int nx = x1 + dx, ny = y1 + dy;
                if (to_set.count({nx, ny})) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    cin >> W >> H >> N;
    vector<vector<pair<int, int>>> shots(N);

    for (int i = 0; i < N; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        shots[i] = get_cells(x1, y1, x2, y2);
    }

    bool possible = true;
    for (int i = 1; i < N; ++i) {
        if (!can_move(shots[i - 1], shots[i])) {
            possible = false;
            break;
        }
    }

    cout << (possible ? "Yes" : "No") << endl;
    return 0;
}
