#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int a, b, weight;
    Edge(int a, int b, int weight) : a(a), b(b), weight(weight) {}
    bool operator < (const Edge& other) const {
        return weight < other.weight;
    }
};

bool is_in(vector<int> set, int target) {
    return find(set.begin(), set.end(), target) != set.end();
}

int countVertices(const vector<Edge>& graph) {
    vector<int> vertices;
    for (Edge edge: graph) {
        if (!is_in(vertices, edge.a))
            vertices.push_back(edge.a);
        if (!is_in(vertices, edge.b))
            vertices.push_back(edge.b);
    }
    return (int)vertices.size();
}

void printEdges(const vector<Edge>& graph) {
    cout << "Graph:\n";
    for (Edge e: graph) {
        printf("(%d-%d): %d\n", e.a, e.b, e.weight);
    }
}

void printStep(const vector<vector<int>>& mst) {
    for (const vector<int>& set: mst) {
        cout << "{ ";
        for (int vertex: set) {
            cout << vertex << " ";
        }
        cout << "} ";
    }
    cout << endl;
}

void createMST(const vector<Edge>& graph, int vertCount) {
    vector<vector<int>> mst;
    vector<Edge> mstGraph;

    for (Edge edge: graph) {
        cout << edge.a << ' ' << edge.b << endl;

        int id_a = -1, id_b = -1;
        for (int i = 0; i < mst.size(); i++) {
            if (id_a != -1 && id_b != -1) break;
            if (id_a == -1 and is_in(mst[i], edge.a))
                id_a = i;
            if (id_b == -1 and is_in(mst[i], edge.b))
                id_b = i;
        }

//        cout << id_a << ' ' << id_b << endl;

        if (id_a == -1 && id_b == -1) {
            vector<int> set = {edge.a, edge.b};
            mst.push_back(set);
            mstGraph.emplace_back(Edge(edge.a, edge.b, edge.weight));
        }
        else if (id_a != -1 && id_b != -1) {
            if (id_a != id_b) {
                mst[id_a].insert(
                        mst[id_a].end(),
                        mst[id_b].begin(),
                        mst[id_b].end()
                );
                mst.erase(mst.begin() + id_b);
                mstGraph.emplace_back(Edge(edge.a, edge.b, edge.weight));
            }
            else
                cout << "this is circle!\n";
        }
        else if (id_a == -1) {
            mst[id_b].push_back(edge.a);
            mstGraph.emplace_back(Edge(edge.a, edge.b, edge.weight));
        }
        else {
            mst[id_a].push_back(edge.b);
            mstGraph.emplace_back(Edge(edge.a, edge.b, edge.weight));
        }
        printStep(mst);

        if (mst.size() == 1 and mst[0].size() == vertCount) {
            printEdges(mstGraph);
            break;
        }
    }
}

int main() {
    int a, b, weight;
    vector<Edge> edges;

    bool is_user_input;
    cout << "User (1) or example (0) input? ";
    cin >> is_user_input;

    if (is_user_input) {
        do {
            cout << "Enter verticles 'a', 'b' and weight of the edge 'ab' (or enter '0' to finish input):\n";
            cin >> a;
            if (a == 0) break;
            cin >> b >> weight;
            edges.emplace_back(Edge(a, b, weight));
        } while (a != 0);
    }
    else {
        edges.emplace_back(1, 2, 20);
        edges.emplace_back(Edge(2, 3, 15));
        edges.emplace_back(Edge(3, 4, 3));
        edges.emplace_back(Edge(4, 5, 17));
        edges.emplace_back(Edge(5, 6, 28));
        edges.emplace_back(Edge(6, 1, 23));

        edges.emplace_back(Edge(1, 7, 1));
        edges.emplace_back(Edge(2, 7, 4));
        edges.emplace_back(Edge(3, 7, 9));
        edges.emplace_back(Edge(4, 7, 16));
        edges.emplace_back(Edge(5, 7, 25));
        edges.emplace_back(Edge(6, 7, 36));
    }

    sort(edges.begin(), edges.end());

    int count = countVertices(edges);
    printEdges(edges);
    createMST(edges, count);

    return 0;
}
