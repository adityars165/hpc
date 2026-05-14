#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

// Function for BFS traversal using OpenMP
void bfs(const vector<vector<int>> &graph, int start) {
    int n = graph.size();

    vector<bool> visited(n, false);
    vector<int> current_level, next_level;

    visited[start] = true;
    current_level.push_back(start);

    cout << "\nBFS Traversal: ";

    while (!current_level.empty()) {

        next_level.clear();

        // Print current level nodes
        for (int node : current_level) {
            cout << node << " ";
        }

        // Parallel processing of current level
        #pragma omp parallel for
        for (int i = 0; i < (int)current_level.size(); i++) {

            int u = current_level[i];

            for (int v = 0; v < n; v++) {

                if (graph[u][v] == 1) {

                    bool should_add = false;

                    // Critical section for visited check
                    #pragma omp critical
                    {
                        if (!visited[v]) {
                            visited[v] = true;
                            should_add = true;
                        }
                    }

                    // Critical section for pushing into next level
                    if (should_add) {
                        #pragma omp critical
                        {
                            next_level.push_back(v);
                        }
                    }
                }
            }
        }

        current_level = next_level;
    }

    cout << endl;
}

// Function for DFS traversal using OpenMP
void dfs(const vector<vector<int>> &graph, int start) {

    int n = graph.size();

    vector<bool> visited(n, false);

    stack<int> st;

    st.push(start);

    cout << "\nDFS Traversal: ";

    while (!st.empty()) {

        int node;

        // Critical section for stack access
        #pragma omp critical
        {
            node = st.top();
            st.pop();
        }

        if (!visited[node]) {

            visited[node] = true;

            cout << node << " ";

            // Push neighbors in reverse order
            for (int i = n - 1; i >= 0; i--) {

                if (graph[node][i] == 1 && !visited[i]) {

                    #pragma omp critical
                    {
                        st.push(i);
                    }
                }
            }
        }
    }

    cout << endl;
}

int main() {

    int n;

    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    cout << "Enter adjacency matrix:\n";

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            cin >> graph[i][j];
        }
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    // Call BFS
    bfs(graph, start);

    // Call DFS
    dfs(graph, start);

    return 0;
}