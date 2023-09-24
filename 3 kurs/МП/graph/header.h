#include <iostream>
#include <list>
using namespace std;

class Graph
{
    int V;                 // число вершин в графе
    list<int> *adj;        // индекс на массив, состоящий из линейного списка
                           // у каждой вершины есть линейный список ребр list<int>
    void dfs(int, bool *); // функция для поиск по глубине
public:
    Graph(int V);               // создать граф из 'V' вершин
    void addEdge(int v, int w); // добавить ребро из вершины 'v' в вершину 'w'
    void DFS(int v);            // поиск по глубине; начинал с вершины 'v'
    void BFS(int v);            // поиск по ширине; начинал с вершины 'v'
};