#include <bits/stdc++.h>
#include "parser.h"

using namespace std;

#define vi vector<int>
#define ll long long
#define pb push_back
#define mp make_pair
#define ii pair<int,int>

vector <vi> maxclique;
vector <vi> adjacencyList;

void listAllVertexDegrees(vector<vector<int>> adjacencyList)
{
    for(int i = 0; i < adjacencyList.size(); i++)
    {
        cout << "The degree of vertex no. " << i+1 << " is " << adjacencyList[i].size() << endl;
    }
}


pair<int,double> clusteringCoefficient(vector<vector<int>> graph, int node)
{
    int neighbours = graph[node-1].size();
    int triangles = (neighbours * (neighbours - 1)) / 2;
    double triads = 0;
    double clusteringcoef = 0;

    if(triangles > 0 && neighbours >= 2)
    {
        int a = node;
    
        for(int i = 0; i < graph[a-1].size(); i++)
        {   
            int b = graph[a-1][i];

            for(int j = 0; j < graph[b-1].size(); j++)
            {
                int c = graph[b-1][j];

                if(c != a)
                {
                    for(int k = 0; k < graph[c-1].size(); k++)
                    {                
                        if(graph[c-1][k] == a)
                        {
                            triads++;
                            break;
                        }
                    }
                }
            }
        }

        clusteringcoef = triads/(neighbours * (neighbours - 1));
    }

    pair<int, double> p = make_pair(node, clusteringcoef);

    return p;
}

double averageClusteringCoefficient(vector<vector<int>> graph)
{
    double sum = 0.0;

    for(int i = 0; i < graph.size(); i++)
    {
        pair<int, double> p = clusteringCoefficient(graph, i+1);
        sum += p.second;
    }

    return sum/(graph.size());

}

void listAllClusteringCoefficients(vector<vector<int>> graph)
{
    for(int i = 1; i <= graph.size(); i++)
    {
        pair <int, double> p = clusteringCoefficient(graph, i);
        printf("The clustering coefficiente of node %d is %.2f\n", p.first, p.second);
    }
}

vi Union( vi V, int N){
    sort(V.begin(), V.end() );
    auto aux = lower_bound( V.begin(), V.end(), N );

    if (V.empty())
    {
        V.pb(N);
        return V;
    }

    if (*aux != N){
        V.pb(N);
        sort(V.begin(), V.end() );
    }
    return V;
}

vi InterN( vi V, int N)
{
    vi neighbours, out;
    int aux;

    for( int i=0; i<adjacencyList[N].size(); i++)
    {
        aux = adjacencyList[N][i];
        neighbours.pb(aux);
    }

    for(int i=0; i < V.size(); i++)
    {
        for(int j=0; j < neighbours.size(); j++)
        {
            if(neighbours[j] == V[i])
            {
                //out.pb(V[i]);
            }
        }
    }
    return out;

}

vi Subnode (vi V, int N){
    sort(V.begin(), V.end() );
    auto aux = lower_bound( V.begin(), V.end(), N );
    if (*aux == N){
        V.erase(aux);
    }
    return V;
}


//R: Maximal clique found
//P: Possible nodes in a maximal clique
//X: Excluded nodes
void bronKerbosch(vi R, vi P, vi X)
{
    //If both P and X are empty, it means that R contains a maximal clique
    if( ( P.empty() ) && ( X.empty() ) )
    {
        maxclique.pb(R);
    }
    //até aqui tudo bem;

    //For each node in vector p
    for(int i=0; i < P.size(); i++)
    {
        bronKerbosch( Union(R,P[i]), InterN(P,P[i]), InterN(X,P[i]) );
        P = Subnode( P, P[i] );
        X = Union( X, P[i] );
    }
}

void printMaximalClique()
{
    cout << maxclique.size() << " " << "Maximal Cliques" << endl << endl;
    for(int i=0; i< maxclique.size(); i++)
    {
        cout << "TAM: " << maxclique[i].size() << "; { ";
        for(int j=0; j< maxclique[i].size(); j++)
        {
            cout << maxclique[i][j] << ", ";
        }
        cout << "}" << endl;
    }
}


int main()
{
    adjacencyList = generateGraph();
    vi R, P, X;

    int input;

    cout << "MENU" << endl;
    cout << "   1. List the vertex degrees of the graph." << endl;
    cout << "   2. List the maximal cliques of the graph." << endl;
    cout << "   3. List clustering coefficients of each vertex." << endl;
    cout << "   4. List average clustering coefficient of the graph." << endl;

    cin >> input;

    switch (input)
    {
        case 1:
            listAllVertexDegrees(adjacencyList);

            break;
        case 2:
            for (int i = 0; i < adjacencyList.size(); i++) P.push_back(i);
            bronKerbosch(R, P, X);
            printMaximalClique();

            break;
        case 3:
            listAllClusteringCoefficients(adjacencyList);
        
            break;
        case 4:
            printf("The average clustering coefficient is %.2f.\n", averageClusteringCoefficient(adjacencyList));

            break;
        default:
            break;
    }

    return 0;
}