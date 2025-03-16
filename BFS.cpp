#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
 
class Graph {
  std::vector<std::vector<size_t>> v_;
 
 public:
  explicit Graph(size_t v) : v_(v) {
  }
 
  void AddEdge(size_t a, size_t b) {
    v_[a].emplace_back(b);
    v_[b].emplace_back(a);
  }
 
  std::vector<size_t> ShortestsPathsBFS(size_t start) const {
    std::vector<size_t> dist(v_.size(), SIZE_MAX);
    dist[start] = 0;
 
    std::queue<size_t> queue;
    queue.emplace(start);
    while (!queue.empty()) {
      size_t index = queue.front();
      queue.pop();
      for (auto i : v_[index]) {
        if (dist[i] == SIZE_MAX) {
          queue.emplace(i);
          dist[i] = dist[index] + 1;
        }
      }
    }
    return dist;
  }
};
 
int main() {
  size_t v, e, start;
  std::ifstream in("graph.txt");
  in >> v >> e;
  Graph g(v);
  for (size_t i = 0; i < e; ++i) {
    size_t x, y;
    in >> x >> y;
    g.AddEdge(x, y);
  }
  in >> start;
  in.close();
  auto dists = g.ShortestsPathsBFS(start);
  for (size_t i = 0; i < v; ++i) {
    std::cout << dists[i] << '\n';
  }
}