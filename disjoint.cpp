#include<bits/stdc++.h>
using namespace std;
 
ifstream f("disjoint.in");
ofstream g("disjoint.out");


class Graf{
private:
    int N;
    int M;
public:
    Graf(int N=0, int M=0){
        this->N = N;
        this->M = M;
    }
    int gaseste(int, vector<int> &);
    void uneste(int, int, vector<int> &);
    vector<int> disjoint(vector<pair<int, pair<int, int>>>);
};

int Graf ::gaseste(int nod, vector<int> &radacina){
    if(radacina[nod] != nod){
        radacina[nod] = gaseste(radacina[nod], radacina);
    }
    return radacina[nod];
}
	
void Graf ::uneste(int x, int y, vector<int> &radacina){
    int rad1, rad2;
    rad1 = gaseste(x, radacina);
    rad2 = gaseste(y, radacina);
    radacina[rad1] = rad2;
}

vector<int> Graf ::disjoint(vector<pair<int,pair<int, int>>> operatii){	
    vector<int> radacina(N + 1);
    vector<int> sol;

    for(int i = 0; i < N; i++){
        radacina[i] = i;
    }
	
    for(long unsigned int i = 0; i < operatii.size(); i++){
        int cod = operatii[i].first;
        int x = operatii[i].second.first;
        int y = operatii[i].second.second;
        if(cod == 1){
            uneste(x, y, radacina);
        }
        else{
            if(cod == 2){
                if(gaseste(x, radacina) == gaseste(y, radacina)){
                    sol.push_back(1);
                }
                else{
                    sol.push_back(0);
                }
            }
        }
    }
    return sol;
}	
	

	
int main()	
{	
    int N, M, cod, x, y;
    f>>N>>M;
    Graf G(N);
    vector<pair<int, pair<int, int>>> operatii;

    for(int i = 0; i < M; i++){
        f>>cod>>x>>y;
        operatii.push_back(make_pair(cod, make_pair(x, y)));
    }
	
    vector<int> sol = G.disjoint(operatii);

    for(int i = 0; i < sol.size(); i++){
        if(sol[i]){
            g<<"DA"<<"\n";
        }
        else{
            g<<"NU"<<"\n";
        }
    }

    return 0;
}