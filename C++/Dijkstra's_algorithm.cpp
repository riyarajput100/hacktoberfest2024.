#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

typedef pair<int, char> Pair;

unordered_map<char, int> dijkstra(unordered_map<char, vector<Pair>>& graph, char start) {
    unordered_map<char, int> shortest_distances;

    for (auto& node : graph) {
        shortest_distances[node.first] = INT_MAX;
    }
    shortest_distances[start] = 0;

    priority_queue<Pair, vector<Pair>, greater<Pair>> priority_queue;
    priority_queue.push({0, start});

    while (!priority_queue.empty()) {
        int current_distance = priority_queue.top().first;
        char current_node = priority_queue.top().second;
        priority_queue.pop();

        if (current_distance > shortest_distances[current_node]) {
            continue;
        }

        for (auto& neighbor : graph[current_node]) {
            char neighbor_node = neighbor.first;
            int weight = neighbor.second;
            int distance = current_distance + weight;

            if (distance < shortest_distances[neighbor_node]) {
                shortest_distances[neighbor_node] = distance;
                priority_queue.push({distance, neighbor_node});
            }
        }
    }

    return shortest_distances;
}

int main() {
    unordered_map<char, vector<Pair>> graph = {
        {'A', {{'B', 1}, {'C', 4}}},
        {'B', {{'A', 1}, {'C', 2}, {'D', 5}}},
        {'C', {{'A', 4}, {'B', 2}, {'D', 1}}},
        {'D', {{'B', 5}, {'C', 1}}}
    };

    char start_node = 'A';
    unordered_map<char, int> shortest_paths = dijkstra(graph, start_node);

    cout << "Shortest paths from " << start_node << ":\n";
    for (auto& path : shortest_paths) {
        cout << path.first << ": " << path.second << endl;
    }

    return 0;
}
