#include <iostream>
#include <queue>
#include <vector>

using namespace std;


vector <vector<int> > G;
vector <int> polje;


int bipartitan( vector<vector <int> > G, int prvi, int V)
{
    // inicijaliziramo na -1 cijeli vector oboji što govori da u tim vrhovima do sada nije bila nijedna boja
    // boje su 0 i 1
    vector <int> oboji(V, -1);

    // prva boja. drugu oznacim s 0 jer cu lako alternirati 0-1
    oboji[prvi] = 1;
    polje[prvi] = 1;

    // u red cu ubacivati one cvorove koje trebam pregledati i bojiti. u startu je to inicijalni cvor
    queue <int> Q;
    Q.push(prvi);

    // vrti dok red nije prazan ( slicno ko u BFS-u )
    while (!Q.empty())
    {
        // dequeue
        int u = Q.front();
        Q.pop();

         // pronaci sve neobojene vrhove koji su incidentni ( spaja ih brid ) s mojim trenutnim vrhom
        for (int v = 0; v < V; ++v)
        {
            // ako nisam do sada obojio i brid postoji
            if (G[u][v] && oboji[v] == -1)
            {
                // pridruzi suprotnu boju incidentnima
                oboji[v] = 1 - oboji[u];
                Q.push(v);
                // za veliki dio bitno
                polje[v] = 1;
            }

            //  ako postoji brid i ako su obojeni istom bojom susjedni
            else if (G[u][v] && oboji[v] == oboji[u])
                return 0;
        }
    }

    // uspio sam izvrtiti do kraja
    return 1;
}


int main()
{
    int V, i , vrh1, vrh2, bridovi, spremi, zapamti = 1;
    cout << "Unesite broj vrhova : " << endl;
        cin >> V;
    cout << "Unesite broj bridova : " << endl;
        cin >> bridovi;
    cout << "Unosite bridove ! " << endl;

    // matricu cusjedstva postavim na 0 sve. mjesta gdje su incidentni vrhovi cu kasnije puniti s 1
    vector<int> temp (V,0);
    G.insert(G.begin(), V, temp );
    for ( i = 0 ; i < V ; ++i)
            polje.push_back(-1);

    // matrica susjedstva. stavim 1 na koordinatu (X,Y) ako su X i Y incidentni
    for ( i = 0; i < bridovi; ++i )
    {
        cin >> vrh1 >> vrh2 ;
        G[vrh1][vrh2] = G[vrh2][vrh1] = 1;
    }

        // za prolazak po svim povezanim komponentama za slučaj nepovezanog grafa
        for ( i = 0 ; i<V ; ++i)
            if ( polje[i] == -1 )
                {
                    spremi = bipartitan(G,i,V);
                    if ( spremi == 0 )
                        {zapamti = 0; break;}
                }

    zapamti ?  cout << "DA" : cout << "NE";

    return 0;
    }
