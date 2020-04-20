#include<iostream>
#include<bits/stdc++.h>
#include<list>
#include<math.h>
#include<limits>

using namespace std;

typedef pair<int, int> pairs; //define um tipo de pares para calcular a distancia

#define INF std::numeric_limits<double>::infinity(); //define infinito

double m[100][100]; // inicializando a matriz de adjacencia
list<int> shorterPath; // inicializando vector pra armazernar o menor caminho
int n; //numero de cidades

string caminho_final = "";//**********
string fim_do_caminho = "";//*************

double calcDist(pairs p1, pairs p2){
	//retorna a distancia entre 2 pontos
	return sqrt(pow((p2.first - p1.first), 2) + pow((p2.second - p1.second), 2));
}



double TSPutil(int mask, int atual, int bc,string caminho_parcial){//**********
    if(atual != 0) caminho_parcial += to_string(atual+1) + " ";// *************
    if(mask==bc){
        fim_do_caminho = caminho_parcial; //*********
        //se a mascara for igual ao caso base retorna a distancia entre a ultima cidade visitada e a inicial
        return m[atual][0];
    }

    double ans = INF;
    for(int prox = 0; prox < n; prox++){
        //verifica se a proxima cidade ja foi visitada
        if((mask&(1<<prox)) == 0){
            //resposta parcial = distancia entre o vertice atual e o proximo, e a menor distancia calculada recursivamente
            int parcial = m[atual][prox] + TSPutil((mask|(1<<prox)), prox, bc, caminho_parcial);
            if(parcial < ans){
                ans = parcial;
                caminho_final = fim_do_caminho + "1";//****************
            }
        }
    }

    return ans;
}

void TSP(){
    //criando uma mascara de bits para o caso base, que seria 11111....1 com N bits, significando que todas cidades foram visitadas
    int baseCase = (1 << n) - 1;
    cout << TSPutil(1, 0, baseCase,"") << endl; //*********
    reverse(caminho_final.rbegin(),caminho_final.rend());
    cout << caminho_final << endl;
}

int main(){
    cin >> n;
	vector<pairs> coords; //cria um vetor de pares ordenados
	int x, y;
	for(int i = 0; i < n; i++){
		cin >> x >> y;
		coords.push_back(make_pair(x, y)); //adiciona as coordenadas no vetor
	}

	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++){
			//calcula a distancia entre todos os pontos afim de fazer um grafo completo
			double d = calcDist(coords[i], coords[j]);
			m[i][j] = d;
			m[j][i] = d;
		}
	}


    const clock_t begin_time = clock(); // gets time
	TSP();
	cout << "\n\nTempo : " << float(clock () - begin_time) /  CLOCKS_PER_SEC << " segundos."; // shows time in seconds

    return 0;
}
