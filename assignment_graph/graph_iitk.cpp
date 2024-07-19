#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Node {
    string name;
    int x, y;
    
    Node() : name(""), x(0), y(0) {}  // Default constructor
    Node(string name, int x, int y) : name(name), x(x), y(y) {}
};

class Graph {
private:
    unordered_map<string, Node> nodes;
    unordered_map<string, vector<pair<string, double>>> adjList;

    double heuristic(const string &a, const string &b) {
        Node &nodeA = nodes[a];
        Node &nodeB = nodes[b];
        return sqrt(pow(nodeA.x - nodeB.x, 2) + pow(nodeA.y - nodeB.y, 2));
    }

public:
    void addNode(string name, int x, int y) {
        nodes[name] = Node(name, x, y);
    }

    void addEdge(string from, string to, double weight) {
        adjList[from].push_back({to, weight});
        adjList[to].push_back({from, weight});
    }

    void printGraph() {
        for (const auto& node : adjList) {
            cout << node.first << " -> ";
            for (const auto& neighbor : node.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }



    vector<string> dijkstra(const string &start, const string &goal) {
        unordered_map<string, double> dist;
        unordered_map<string, string> prev;
        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;

        for (auto &node : nodes) {
            dist[node.first] = numeric_limits<double>::infinity();
        }

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            string current = pq.top().second;
            pq.pop();

            if (current == goal) {
                vector<string> path;
                for (string at = goal; at != ""; at = prev[at]) {
                    path.push_back(at);
                }
                reverse(path.begin(), path.end());
                return path;
            }

            for (auto &neighbor : adjList[current]) {
                double alt = dist[current] + neighbor.second;
                if (alt < dist[neighbor.first]) {
                    dist[neighbor.first] = alt;
                    prev[neighbor.first] = current;
                    pq.push({alt, neighbor.first});
                }
            }
        }

        return {};
    }

    vector<string> aStar(const string &start, const string &goal) {
        unordered_map<string, double> gScore, fScore;
        unordered_map<string, string> prev;
        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;

        for (auto &node : nodes) {
            gScore[node.first] = numeric_limits<double>::infinity();
            fScore[node.first] = numeric_limits<double>::infinity();
        }

        gScore[start] = 0;
        fScore[start] = heuristic(start, goal);
        pq.push({fScore[start], start});

        while (!pq.empty()) {
            string current = pq.top().second;
            pq.pop();

            if (current == goal) {
                vector<string> path;
                for (string at = goal; at != ""; at = prev[at]) {
                    path.push_back(at);
                }
                reverse(path.begin(), path.end());
                return path;
            }

            for (auto &neighbor : adjList[current]) {
                double tentative_gScore = gScore[current] + neighbor.second;
                if (tentative_gScore < gScore[neighbor.first]) {
                    prev[neighbor.first] = current;
                    gScore[neighbor.first] = tentative_gScore;
                    fScore[neighbor.first] = gScore[neighbor.first] + heuristic(neighbor.first, goal);
                    pq.push({fScore[neighbor.first], neighbor.first});
                }
            }
        }

        return {};
    }
};

int main() {
    Graph g;
    
    // Adding nodes
    g.addNode("Hall 1", 0, 0);
    g.addNode("Hall 2", 50, 50);
    g.addNode("Hall 3", 100, 100);
    g.addNode("Hall 4", 150, 150);
    g.addNode("Hall 5", 200, 200);
    g.addNode("Hall 6", 250, 250);
    g.addNode("Hall 7", 300, 300);
    g.addNode("Hall 8", 350, 350);
    g.addNode("Hall 9", 400, 400);
    g.addNode("Hall 10", 450, 450);
    g.addNode("Hall 11", 500, 500);
    g.addNode("Hall 12", 550, 550);
    g.addNode("Hall 13", 600, 600);
    g.addNode("Girls Hostel 1", 100, 50);
    g.addNode("Kargil Chowk", 700, 700);
    g.addNode("Counselling Service", 200, 100);
    g.addNode("Open Air Theatre", 150, 200);
    g.addNode("Pronite Ground", 250, 200);
    g.addNode("Events Ground", 200, 150);
    g.addNode("Health Centre", 300, 100);
    g.addNode("New Shopping Complex", 350, 200);

    // Adding edges
    g.addEdge("Hall 1", "Hall 2", 75);
    g.addEdge("Hall 2", "Hall 3", 125);
    g.addEdge("Hall 3", "Hall 4", 100);
    g.addEdge("Hall 4", "Hall 5", 150);
    g.addEdge("Hall 5", "Hall 6", 250);
    g.addEdge("Hall 6", "Hall 7", 300);
    g.addEdge("Hall 7", "Hall 8", 50);
    g.addEdge("Hall 8", "Hall 9", 75);
    g.addEdge("Hall 9", "Hall 10", 180);
    g.addEdge("Hall 10", "Hall 11", 200);
    g.addEdge("Hall 11", "Hall 12", 250);
    g.addEdge("Hall 12", "Hall 13", 150);
    g.addEdge("Hall 4", "Girls Hostel 1", 197.231);
    g.addEdge("Hall 4", "Hall 3", 100);
    g.addEdge("Hall 4", "Hall 5", 250.138);
    g.addEdge("Hall 4", "Kargil Chowk", 570.351);
    g.addEdge("Hall 4", "Counselling Service", 181.108);
    g.addEdge("Hall 4", "Open Air Theatre", 113.137);
    g.addEdge("Hall 4", "Pronite Ground", 160);
    g.addEdge("Hall 4", "Events Ground", 160);
    g.addEdge("Hall 4", "Health Centre", 100);
    g.addEdge("Hall 4", "New Shopping Complex", 80);

    g.printGraph();
    cout << endl;
    cout << endl;
    cout << endl;
    
    string start = "Hall 1";
    string goal = "Hall 13";

    vector<string> dijkstraPath = g.dijkstra(start, goal);
    cout << "Dijkstra Path from " << start << " to " << goal << ": ";
    for (const string &node : dijkstraPath) {
        cout << node << " ";
    }
    cout << endl;
    cout << endl;
    cout << endl;
    
    vector<string> aStarPath = g.aStar(start, goal);
    cout << "A* Path from " << start << " to " << goal << ": ";
    for (const string &node : aStarPath) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
