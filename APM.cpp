#include<bits/stdc++.h>
using namespace std;
 
ifstream f("apm.in");
ofstream g("apm.out");

bool sortaremuchii(const pair<pair<int, int>, int> &x, const pair<pair<int, int>, int> &y)
{
    return (x.second < y.second);
}
	
class Graf
{
private:	
    int N, M;
    vector<pair<pair<int, int>, int>> adiacenta;
    vector<pair<int, int>> solutie;
    vector<int> parinte;
    vector<int> rank;
	
public:	
    Graf(int);
    void muchie(int, int, int);
    void Kruskal();
    void Leaga(int, int);
    int Gaseste(int);
    void printSolutie();
};
	
Graf ::Graf(int n)
{
  N = n;
  parinte.resize(N + 1);
  rank.resize(N + 1);
}
	
void Graf ::muchie(int x, int y, int c)
{
  adiacenta.push_back(make_pair(make_pair(x, y), c));	
}
	
int Graf ::Gaseste(int x)
{
  if (x == parinte[x])	
    return x;
  return Gaseste(parinte[x]);
}
	
void Graf::Leaga(int a, int b)	
{
  int x = Gaseste(a);	
  int y = Gaseste(b);
	
  if (rank[x] >= rank[y])
  {
    parinte[y] = x;
    rank[x] += rank[y];
    M++;
  }
  else
  {
    parinte[x] = y;
    rank[y] += rank[x];
    M++;
  }
}
	
void Graf ::Kruskal()
{
  int cost = 0, x, y, a, b;
  	
  M = 0;
	
  for (int i = 1; i <= N; i++)
  {
    parinte[i] = i;
    rank[i] = 1;
  }
  sort(adiacenta.begin(), adiacenta.end(), sortaremuchii);
	
  for (long unsigned int i = 0; i < adiacenta.size(); i++)
  {
    x = Gaseste(adiacenta[i].first.first);
    y = Gaseste(adiacenta[i].first.second);
    a = adiacenta[i].first.first;
    b = adiacenta[i].first.second;

    if (x != y)
    {
      solutie.push_back(make_pair(b, a));
      Leaga(b, a);
      cost += adiacenta[i].second;
    }
  }
	
  g<<cost<<endl;
  g<<M<<endl;
	
}

void Graf ::printSolutie()
{
    for (int i = 0; i < M; i++)
    g<<solutie[i].first<<' '<<solutie[i].second<<endl;
}

int main()
{
  int N, M, i, x, y, c;
  f>>N>>M;
  Graf G(N);
	
  for (i = 1; i <= M; i++)
  {
    f>>x>>y>>c;
    G.muchie(x, y, c);
  }
	
  G.Kruskal();
  G.printSolutie();
    return 0;
}