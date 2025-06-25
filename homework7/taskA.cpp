#include <iostream>
#include <vector>
#include <list>

int main() {
  int vertex_count = 0;
  int operation_count = 0;
  std::cin >> vertex_count >> operation_count;

  std::vector<std::vector<int>> adjacency_list(vertex_count + 1);

  for (int i = 0; i < operation_count; ++i) {
    int operation = 0;
    std::cin >> operation;

    if (operation == 1) {
      int u = 0;
      int v = 0;
      std::cin >> u >> v;
      adjacency_list[u].push_back(v);
      adjacency_list[v].push_back(u);
    } else if (operation == 2) {
      int u = 0;
      std::cin >> u;
      for (const int neighbor : adjacency_list[u]) {
        std::cout << neighbor << " ";
      }
      std::cout << "\n";
    }
  }

  return 0;
}
