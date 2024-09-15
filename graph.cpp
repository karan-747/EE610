#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// Class to represent an Undirected Graph
class Graph
{
private:
    int V;                   // Number of vertices
    vector<vector<int>> adj; // Adjacency list to represent the graph

    // BFS to check connectivity and explore all reachable nodes
    void bfs(int start, vector<bool> &visited)
    {
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            // Explore all adjacent vertices
            for (int v : adj[u])
            {
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

public:
    // Constructor to initialize graph with a given number of vertices
    Graph(int vertices) : V(vertices)
    {
        adj.resize(V);
    }

    // Add an undirected edge between two vertices
    void addEdge(int u, int v)
    {
        if (u < V && v < V && u >= 0 && v >= 0)
        {
            adj[u].push_back(v); // Add v to u's adjacency list
            adj[v].push_back(u); // Add u to v's adjacency list (since the graph is undirected)
        }
    }

    // Function to check if the graph is connected
    bool isConnected()
    {
        if (V == 0)
            return true; // An empty graph is trivially connected

        vector<bool> visited(V, false);
        bfs(0, visited); // Start BFS from node 0

        // Check if all nodes are visited
        for (bool nodeVisited : visited)
        {
            if (!nodeVisited)
                return false; // If any node is not visited, the graph is disconnected
        }

        return true;
    }

    // Find isolated nodes (nodes with no edges)
    vector<int> getIsolatedNodes()
    {
        vector<int> isolatedNodes;
        for (int i = 0; i < V; ++i)
        {
            if (adj[i].empty())
            {
                isolatedNodes.push_back(i); // If no adjacent nodes, it's isolated
            }
        }
        return isolatedNodes;
    }

    // Get the degree (number of edges) of each node
    map<int, int> getDegrees()
    {
        map<int, int> degrees;
        for (int i = 0; i < V; ++i)
        {
            degrees[i] = adj[i].size(); // Degree is the size of the adjacency list
        }
        return degrees;
    }

    // Print the graph's properties such as connectivity and isolated nodes
    void printGraphProperties()
    {
        if (V == 0)
        {
            cout << "The graph is empty." << endl;
            return;
        }

        cout << "Graph properties:" << endl;

        // Check if the graph is connected
        if (isConnected())
        {
            cout << "The graph is connected." << endl;
        }
        else
        {
            cout << "The graph is disconnected." << endl;
        }

        // Print isolated nodes, if any
        vector<int> isolatedNodes = getIsolatedNodes();
        if (isolatedNodes.empty())
        {
            cout << "There are no isolated nodes." << endl;
        }
        else
        {
            cout << "Isolated nodes: ";
            for (int node : isolatedNodes)
            {
                cout << node << " ";
            }
            cout << endl;
        }

        // Print the degrees of all nodes
        map<int, int> degrees = getDegrees();
        cout << "Degrees of nodes:" << endl;
        for (const auto &pair : degrees)
        {
            cout << "Node " << pair.first << ": " << pair.second << endl;
        }
    }
};

// Class to represent a Directed Graph
class DirectedGraph
{
private:
    int V;                       // Number of vertices
    vector<vector<int>> adj;     // Adjacency list for out-degrees
    vector<vector<int>> rev_adj; // Reverse adjacency list for in-degrees

public:
    // Constructor to initialize the directed graph with a given number of vertices
    DirectedGraph(int vertices) : V(vertices)
    {
        adj.resize(V);
        rev_adj.resize(V);
    }

    // Add a directed edge from u to v
    void addEdge(int u, int v)
    {
        if (u < V && v < V && u >= 0 && v >= 0)
        {
            adj[u].push_back(v);   // Add v to u's adjacency list (outgoing edges)
            rev_adj[v].push_back(u); // Add u to v's reverse adjacency list (incoming edges)
        }
    }

    // Get the in-degrees of nodes (number of incoming edges)
    map<int, int> getInDegrees()
    {
        map<int, int> inDegrees;
        for (int i = 0; i < V; ++i)
        {
            inDegrees[i] = rev_adj[i].size(); // In-degree is the size of the reverse adjacency list
        }
        return inDegrees;
    }

    // Get the out-degrees of nodes (number of outgoing edges)
    map<int, int> getOutDegrees()
    {
        map<int, int> outDegrees;
        for (int i = 0; i < V; ++i)
        {
            outDegrees[i] = adj[i].size(); // Out-degree is the size of the adjacency list
        }
        return outDegrees;
    }

    // Check if the directed graph is connected (all nodes can be reached from any other node)
    bool isConnected()
    {
        if (V == 0)
            return true; // An empty graph is trivially connected

        vector<bool> visited(V, false);
        bfs(0, visited); // Start BFS from node 0

        // Check if all nodes are visited
        for (bool nodeVisited : visited)
        {
            if (!nodeVisited)
                return false; // If any node is not visited, the graph is disconnected
        }

        return true;
    }

    // BFS to check connectivity
    void bfs(int start, vector<bool> &visited)
    {
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            // Explore all adjacent vertices
            for (int v : adj[u])
            {
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    // Print the directed graph's properties such as connectivity and degrees
    void printGraphProperties()
    {
        if (V == 0)
        {
            cout << "The graph is empty." << endl;
            return;
        }

        cout << "Directed Graph properties:" << endl;

        // Check if the directed graph is connected
        if (isConnected())
        {
            cout << "The graph is connected." << endl;
        }
        else
        {
            cout << "The graph is disconnected." << endl;
        }

        // Print in-degrees of nodes
        map<int, int> inDegrees = getInDegrees();
        cout << "In-degrees of nodes:" << endl;
        for (const auto &pair : inDegrees)
        {
            cout << "Node " << pair.first << ": " << pair.second << endl;
        }

        // Print out-degrees of nodes
        map<int, int> outDegrees = getOutDegrees();
        cout << "Out-degrees of nodes:" << endl;
        for (const auto &pair : outDegrees)
        {
            cout << "Node " << pair.first << ": " << pair.second << endl;
        }
    }
};

// Function to solve the problem for multiple test cases
void solve()
{
    int vertices, edges;
    char graphType;

    // Input graph type ('u' for undirected, 'd' for directed)
    cin >> graphType;

    // Input number of vertices
    cin >> vertices;

    if (graphType == 'u')
    {
        Graph g(vertices);

        // Input number of edges
        cin >> edges;

        // Input edges
        for (int i = 0; i < edges; ++i)
        {
            int u, v;
            cin >> u >> v;
            g.addEdge(u, v); // Add undirected edge
        }

        // Print properties of the undirected graph
        g.printGraphProperties();
    }
    else if (graphType == 'd')
    {
        DirectedGraph g(vertices);

        // Input number of edges
        cin >> edges;

        // Input directed edges
        for (int i = 0; i < edges; ++i)
        {
            int u, v;
            cin >> u >> v;
            g.addEdge(u, v); // Add directed edge
        }

        // Print properties of the directed graph
        g.printGraphProperties();
    }
    else
    {
        cout << "Invalid graph type!" << endl;
    }
}

int main()
{
    // Number of test cases
    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}
