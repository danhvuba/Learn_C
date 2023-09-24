#include "header.h"
int main()
{
    Graph new_graph(4);
    new_graph.addEdge(0, 1);
    new_graph.addEdge(0, 2);
    new_graph.addEdge(1, 2);
    new_graph.addEdge(2, 0);
    new_graph.addEdge(2, 3);
    new_graph.addEdge(3, 3);

    cout << "Поиск по глубине; начинал с вершины 2\nСписок вершин: " << endl;
    new_graph.DFS(2);

    cout << "\nПоиск по ширине; начинал с вершины 2\nСписок вершин: " << endl;
    new_graph.BFS(2);
    cout
        << endl;
}
