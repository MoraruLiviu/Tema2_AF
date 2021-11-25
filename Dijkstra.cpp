#include<bits/stdc++.h>
using namespace std;
 
ifstream f("dijkstra.in");
ofstream g("dijkstra.out");

const int NMax = 100005;
const int inf = 1000000000;
	
int N, M, P;
int D[NMax];
bool InStiva[NMax];
vector < pair <int,int> > G[NMax];

struct compara	
{
    bool operator()(int x, int y)	
    {
        return D[x] > D[y];
    }
};
	
priority_queue<int, vector<int>, compara> Stiva;	

void Dijkstra(int nodStart)
{
    for(int i = 1; i <= N; i++)
        D[i] = inf;
    D[nodStart]=0;
    Stiva.push(nodStart);
    InStiva[nodStart] = true;

    while(!Stiva.empty())
    {
        int nodCurent = Stiva.top();
        Stiva.pop();
        InStiva[nodCurent] = false;
        for(size_t i = 0; i < G[nodCurent].size(); i++)
        {
            int Vecin = G[nodCurent][i].first;
            int Cost = G[nodCurent][i].second;
            if(D[nodCurent] + Cost < D[Vecin])
            {
                D[Vecin] = D[nodCurent] + Cost;
                if(InStiva[Vecin] == false)
                {
                    Stiva.push(Vecin);
                    InStiva[Vecin] = true;
                }
            }
        }
    }
}


int main()	
{
    f>>N>>M;	
    P = 1;
    for(int i = 1; i <= M; i++)
    {
        int x, y, c;
        f>>x>>y>>c;
        G[x].push_back(make_pair(y,c));
    }

    Dijkstra(P);

    for(int i = 2; i <= N; i++)	
    {
        if(D[i] != inf)
            g<<D[i]<< " ";
        else
            g<<"0 ";
    }

    return 0;
}