#include "Point.h"
#include "Algorithms.h"

vector<int> bfs(int start, int end, vector<vector<int>>& graph, vector<int>& visited) {
    queue<int> q;
    unordered_map<int, int> parent;
    q.push(start);
    parent[start] = -1;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        visited.push_back(current);

        if (current == end) {
            vector<int> path;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i : graph[current]) {
            if (parent.find(i) == parent.end()) {
                parent[i] = current;
                q.push(i);
            }
        }
    }

    return {};
}

vector<int> dfs(int start, int end, vector<vector<int>>& graph, vector<int>& visited) {
    stack<int> s;
    unordered_map<int, int> parent;
    s.push(start);
    parent[start] = -1;

    while (!s.empty()) {
        int current = s.top();
        s.pop();
        visited.push_back(current);

        if (current == end) {
            vector<int> path;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i : graph[current]) {
            if (parent.find(i) == parent.end()) {
                parent[i] = current;
                s.push(i);
            }
        }
    }

    return {};
}

vector<int> a_star(int start, int end, vector<vector<int>>& graph, vector<Point>& points, vector<int>& visited) {
    auto heuristic = [&](int a, int b) {
        float dx = points[a].x - points[b].x;
        float dy = points[a].y - points[b].y;
        return sqrt(dx * dx + dy * dy);
    };

    priority_queue<PQ, vector<PQ>, greater<PQ>> frontier;
    unordered_map<int, int> parent;
    unordered_map<int, float> cost_so_far;

    frontier.emplace(0, start);
    parent[start] = -1;
    cost_so_far[start] = 0.0f;

    while (!frontier.empty()) {
        int current = frontier.top().second;
        frontier.pop();
        visited.push_back(current);

        if (current == end) {
            vector<int> path;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i : graph[current]) {
            float new_cost = cost_so_far[current] + heuristic(current, i);

            if (!cost_so_far.count(i) || new_cost < cost_so_far[i]) {
                cost_so_far[i] = new_cost;
                float priority = new_cost + heuristic(i, end);
                frontier.emplace(priority, i);
                parent[i] = current;
            }
        }
    }

    return {};
}

vector<int> greedy_best_first(int start, int end, vector<vector<int>>& graph, vector<Point>& points, vector<int>& visited) {
    auto heuristic = [&](int a, int b) {
        float dx = points[a].x - points[b].x;
        float dy = points[a].y - points[b].y;
        return sqrt(dx * dx + dy * dy);
    };

    priority_queue<PQ, vector<PQ>, greater<PQ>> frontier;
    unordered_map<int, int> parent;

    frontier.emplace(0, start);
    parent[start] = -1;

    while (!frontier.empty()) {
        int current = frontier.top().second;
        frontier.pop();
        visited.push_back(current);

        if (current == end) {
            vector<int> path;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }

            reverse(path.begin(), path.end());
            return path;
        }

        for (int i : graph[current]) {
            if (parent.find(i) == parent.end()) {
                float priority = heuristic(i, end);
                frontier.emplace(priority, i);
                parent[i] = current;
            }
        }
    }

    return {};
}

vector<int> hill_climbing(int start, int end, vector<vector<int>>& graph, vector<Point>& points, vector<int>& visited) {
    auto objective = [&](int a) {
        float dx = points[a].x - points[end].x;
        float dy = points[a].y - points[end].y;
        return sqrt(dx * dx + dy * dy);
    };

    int current = start;
    unordered_map<int, int> parent;
    parent[start] = -1;

    while (current != end) {
        visited.push_back(current);
        int next = -1;
        float best_value = objective(current);

        for (int i = 0; i < (int)graph[current].size(); i++) {
            int neighbor = graph[current][i];
            float value = objective(neighbor);
            if (value < best_value) {
                best_value = value;
                next = neighbor;
            }
        }
        if (next == -1) {
            break;
        }
        parent[next] = current;
        current = next;
    }

    if (current == end) {
        vector<int> path;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());
        return path;
    }

    return {};
}

vector<int> dijkstra(int start, int end, vector<vector<int>>& graph, vector<Point>& points, vector<int>& visited) {
    auto weights = [&](int a, int b) {
        float dx = points[a].x - points[b].x;
        float dy = points[a].y - points[b].y;
        return sqrt(dx * dx + dy * dy);
    };

    priority_queue<PQ, vector<PQ>, greater<PQ>> frontier;
    unordered_map<int, int> parent;
    unordered_map<int, float> distance;
    frontier.emplace(0, start);
    parent[start] = -1;
    distance[start] = 0.0f;

    while (!frontier.empty()) {
        int current = frontier.top().second;
        float current_weight = frontier.top().first;
        frontier.pop();

        if (current_weight > distance[current]) {
            continue;
        }

        visited.push_back(current);

        if (current == end) {
            vector<int> path;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i : graph[current]) {
            float new_distance = distance[current] + weights(current, i);
            if (!distance.count(i) || new_distance < distance[i]) {
                distance[i] = new_distance;
                parent[i] = current;
                frontier.emplace(new_distance, i);
            }
        }
    }

    return {};
}

vector<int> ida_star(int start, int end, vector<vector<int>>& graph, vector<Point>& points, vector<int>& visited) {
    auto heuristic = [&](int a, int b) {
        float dx = points[a].x - points[b].x;
        float dy = points[a].y - points[b].y;
        return sqrt(dx * dx + dy * dy);
    };

    float threshold = heuristic(start, end);
    unordered_map<int, int> parent;
    parent[start] = -1;

    function<float(int, float)> search = [&](int current, float g) -> float {
        visited.push_back(current);
        float f = g + heuristic(current, end);
        if (f > threshold) return f;
        if (current == end) return -1;

        float min_threshold = 1e9f;
        for (int i : graph[current]) {
            if (parent.find(i) == parent.end()) {
                parent[i] = current;
                float temp = search(i, g + heuristic(current, i));
                if (temp == -1) return -1;
                min_threshold = min(min_threshold, temp);
                parent.erase(i);
            }
        }
        return min_threshold;
    };

    while (true) {
        parent.clear();
        parent[start] = -1;
        float temp = search(start, 0.0f);
        if (temp == -1) {
            vector<int> path;
            int current = end;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }
        if (temp >= 1e9f) return {};
        threshold = temp;
    }
}