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

        int v = 0;
         // pronaci sve neobojene vrhove koji su incidentni ( spaja ih brid ) s mojim trenutnim vrhom
        while ( G[u][v] != -1 )
        {

            // ako nisam do sada obojio i brid postoji
            if (G[u][v]!=-1 && oboji[ G[u][v] ] == -1)
            {
                // pridruzi suprotnu boju incidentnima
                oboji[ G[u][v] ] = 1 - oboji[u];
                Q.push( G[u][v] );
                polje[ G[u][v] ] = 1;
            }

            //  ako postoji brid i ako su obojeni istom bojom susjedni
            else if (G[u][v]!=-1 && oboji[G[u][v]] == oboji[u])
                return 0;

         ++v;
        }
    }


    // uspio sam izvrtiti do kraja
    return 1;
}


int main()
{
    int V, i , broj, k = 0, spremi, zapamti = 1, kontrola = 0;
    cout << "Unesite broj vrhova : " << endl;
        cin >> V;

    vector<int> temp (V,-1);
    G.insert(G.begin(), V, temp );

    for ( i = 0 ; i < V ; ++i)
            polje.push_back(-1);


    // matrica susjedstva. za svaki vrh piše s kim je incidentan. unosimo vrhove dok ne dođe -1 ( = znak za prekid )
    for ( i = 0; i < V; ++i )
    {   cout << "S kim je incidentan "<< i << ". vrh ? " << endl;
        cin >> broj ;
        while (broj!=-1)
        {
            for ( int j = 0 ; j<V ; ++j)
         {
                if ( G[i][j] == broj ) {kontrola = 1; break;}
                if ( G[i][j] == -1 ) break;
         }

            if ( kontrola == 0 ) G[i][k++]=broj;

            kontrola = 0;

            cin >> broj ;
            if ( broj == -1 ) break;
        }

        k=0;

    }


        // za prolazak po svim povezanim komponentama za slučaj nepovezanog grafa
        for ( i = 0 ; i<V ; ++i)
            if ( polje[i] == -1 )
                {
                    spremi = bipartitan(G,i,V);
                    if ( spremi == 0 )
                        {zapamti = 0; break; }
                }

    zapamti ?  cout << "DA" : cout << "NE";

    return 0;
    }
