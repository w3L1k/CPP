#include <iostream>
#include <unordered_map>
#include <queue>
#include <set>
#include <string>
#include <sstream>

struct Track {
  int score = 0;
  int track_id = 0;
  bool operator<(const Track& other) const {
    if (score != other.score) {
      return score < other.score;
    }
    return track_id > other.track_id;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::unordered_map<std::string, int> ip_last_vote;
  std::unordered_map<int, int> track_scores;
  std::priority_queue<Track> pq;
  std::set<int> known_tracks;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    std::stringstream ss(line);
    std::string command;
    ss >> command;

    if (command == "VOTE") {
      std::string ip;
      int track_id = 0;
      int score = 0;
      int time = 0;
      ss >> ip >> track_id >> score >> time;

      known_tracks.insert(track_id);

      if (ip_last_vote.find(ip) == ip_last_vote.end() || time - ip_last_vote[ip] >= 600) {
        ip_last_vote[ip] = time;
        track_scores[track_id] += score;
        pq.push({track_scores[track_id], track_id});
      }
      std::cout << track_scores[track_id] << "\n";

    } else if (command == "GET") {
      if (known_tracks.empty()) {
        known_tracks.insert(1);
        track_scores[1] = 0;
        pq.push({0, 1});
      }

      while (!pq.empty()) {
        Track top = pq.top();
        pq.pop();
        if (track_scores[top.track_id] == top.score) {
          std::cout << top.track_id << " " << top.score << "\n";
          track_scores[top.track_id] = -1;
          pq.push({-1, top.track_id});
          break;
        }
      }
    } else if (command == "EXIT") {
      std::cout << "OK\n";
      break;
    }
  }
  return 0;
}
