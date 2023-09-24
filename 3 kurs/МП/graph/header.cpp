#include "header.h"

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::DFS(int v)
{
    // создать массив непройденных вершин
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    dfs(v, visited);
}

void Graph::dfs(int v, bool *visited)
{
    visited[v] = true;
    cout << v << " ";

    list<int>::iterator i; // индекс на номер ребра в список ребра list<int>
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i]) // если вершина непройденна
            dfs(*i, visited);
}

void Graph::BFS(int s)
{
    // создать массив непройденных вершин
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    visited[s] = true;

    list<int> list_ver;    // список вершин по ширине
    list_ver.push_back(s); // начинаем в вершиной 's'

    list<int>::iterator i; // индекс на номер ребра в список ребра list<int>
    while (!list_ver.empty())
    {
        // проходим через первую вершину списка вершин
        s = list_ver.front();
        cout << s << " ";
        list_ver.pop_front(); // вычеркнуть вершину уже проходили

        // добавить непройденные вершины, связанные с вершиной s, в конец списка
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                list_ver.push_back(*i);
            }
        }
    }
    // цикл while заканчивается когда мы уже проходили все вершины, лежащие в одном компаненте связности
}