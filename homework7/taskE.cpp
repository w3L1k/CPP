#include <iostream>
#include <vector>
#include <algorithm>

struct Team {
  int id;
  int solved;
  int penalty;
};

bool CompareTeams(const Team& a, const Team& b) {
  if (a.solved != b.solved) {
    return a.solved > b.solved;
  }
  if (a.penalty != b.penalty) {
    return a.penalty < b.penalty;
  }
  return a.id < b.id;
}

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<Team> teams(n);
  for (int i = 0; i < n; ++i) {
    int solved = 0;
    int penalty = 0;
    std::cin >> solved >> penalty;
    teams[i] = {i + 1, solved, penalty};
  }

  std::sort(teams.begin(), teams.end(), CompareTeams);

  for (const Team& team : teams) {
    std::cout << team.id << "\n";
  }

  return 0;
}
