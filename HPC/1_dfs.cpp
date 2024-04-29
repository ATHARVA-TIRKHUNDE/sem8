#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void seqbfs( vector<vector<int>> &graph, int start ){

    int nodes = graph.size() ;
    vector<bool> visited(nodes, false) ;
    stack<int> s;
    s.push(start) ;
    visited[start] = true ;

    while ( !s.empty()) {
        int curr = s.top() ;
        s.pop() ;
        cout << curr << ", " ;
        for( auto neighbour : graph[curr] ) {
            if( !visited[neighbour] ) {
                visited[neighbour] = true ;
                s.push(neighbour) ;
            }
        }
    }

}

void parallelbfs( vector<vector<int>> &graph, int start ){

    int nodes = graph.size() ;
    vector<bool> visited(nodes, false) ;
    stack<int> s;
    s.push(start) ;
    visited[start] = true ;

    # pragma omp while
    while ( !s.empty()) {
        int curr = s.top() ;
        s.pop() ;
        cout << curr << ", " ;
        for( auto neighbour : graph[curr] ) {
            if( !visited[neighbour] ) {
                visited[neighbour] = true ;
                s.push(neighbour) ;
            }
        }
    }

}

int main()
{
    vector<vector<int>> graph(5);
    graph[0] = {1, 2, 3} ;
    graph[1] = {0, 2} ;
    graph[2] = {1, 3} ;
    graph[3] = {0, 2, 4};
    graph[4] = {3} ;

    double start = omp_get_wtime() ;
    seqbfs(graph, 0) ;
    double end = omp_get_wtime() ;
    cout << "\nSequential BFS : " << (end - start) << endl ;

    start = omp_get_wtime() ;
    parallelbfs(graph, 0) ;
    end = omp_get_wtime() ;
    cout << "\nParallel BFS : " << (end - start) << endl ;

    return 0;
}