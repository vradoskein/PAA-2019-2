#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<math.h>
#include<limits>

using namespace std;

typedef pair<int, int> pairs; //define um tipo de pares para calcular a distancia

#define INF std::numeric_limits<double>::infinity(); //define infinito

double m[100][100]; // inicializando a matriz de adjacencia
vector<int> shorterPath; // inicializando vector pra armazernar o menor caminho
int cities[100]; //inicializando vetor para armazenar as cidades possiveis
int n; //numero de cidades

double calcDist(pairs p1, pairs p2){
	//retorna a distancia entre 2 pontos
	return sqrt(pow((p2.first - p1.first), 2) + pow((p2.second - p1.second), 2));
}

//copia o caminho para o vector
void copyPath(int a[], int n){
	if(shorterPath.size() > 0) shorterPath.clear();
	for(int i = 0; i < n+1; i++){
		shorterPath.push_back(a[i]);
	}
}

/*
gera todas permutações das cidades
calcula a distancia de cada permutação
salva a que for menor, e o seu caminho
e então printa no final
*/
void bruteForce(int a[], int n, double menorDist){
	//orgazina o vector (para uma solução generica - para essa solução ele já sempre está ordenado)
	sort(a, a+n);
	double somaDist = 0; // inicia soma das distancias
	do{
		for (int i = 0; i < n; i++) {
	        somaDist += m[a[i]][a[i+1]]; //soma as distancias do caminho
	    }
		if(somaDist < menorDist){
			// se essa soma for menor que a menor atual, salva ela como menor e salva o caminho dela
			menorDist = somaDist;
			copyPath(a, n);
		}

		somaDist = 0; //reseta a soma

	} while (next_permutation(a + 1, a + n)); //proxima permutação

	// procedimento para imprimir resposta
	cout << menorDist << endl;
	for(int i = 0; i < shorterPath.size() - 1; i++){
		cout << shorterPath[i] + 1 << " ";
	}
	cout << endl;
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

	for(int i = 0; i < n; i++){
		cities[i] = i;
	}
	cities[n] = cities[0]; // cria a rota para permutar

	double menorDist = INF;
	bruteForce(cities, n, menorDist); // metodo força bruta
	return 0;
}
