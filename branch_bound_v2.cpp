#include <bits/stdc++.h> 
using namespace std; 
typedef pair<int, int> pairs; //define um tipo de pares para calcular a distancia

#define INF std::numeric_limits<double>::infinity(); //define infinito
  
int N;
int caminhoFinal[101]; 
bool visited[100];  
int adj[100][100];
int respostaFinal = INT_MAX; 

double calcDist(pairs p1, pairs p2){
	//retorna a distancia entre 2 pontos
	return sqrt(pow((p2.first - p1.first), 2) + pow((p2.second - p1.second), 2));
}

void copyToFinal(int caminhoAtual[]) { 
    for (int i=0; i<N; i++) 
        caminhoFinal[i] = caminhoAtual[i]; 
    caminhoFinal[N] = caminhoAtual[0]; 
} 
  
// acha a aresta (rota) de menor peso
// que termina no vertice (cidade) i
int menorAresta(int adj[][100], int i) { 
    int min = INT_MAX; 
    for (int k=0; k<N; k++) 
        if (adj[i][k]<min && i != k) 
            min = adj[i][k]; 
    return min; 
} 
  
// acha a aresta (rota) de segundo menor peso
// que termina no vertice (cidade) i
int segundaMenor(int adj[][100], int i) { 
    int first = INT_MAX, second = INT_MAX; 
    for (int j=0; j<N; j++) 
   { 
        if (i == j) 
            continue; 
  
        if (adj[i][j] <= first) 
       { 
            second = first; 
            first = adj[i][j]; 
        } 
        else if (adj[i][j] <= second && 
                 adj[i][j] != first) 
            second = adj[i][j]; 
    } 
    return second; 
} 

void TSPRec(int adj[][100], int limite_atual, int pesoAtual, 
            int level, int caminhoAtual[]) { 
    // caso base = nivel N (percorremos todas as cidades)
    if (level==N){ 
        // confere se o ultimo vertice pode voltar para o inicial
        if (adj[caminhoAtual[level-1]][caminhoAtual[0]] != 0) { 
            int respParcial = pesoAtual + 
                    adj[caminhoAtual[level-1]][caminhoAtual[0]]; 
  
            // atualiza o caminho final se o parcial for melhor
            if (respParcial < respostaFinal){ 
                copyToFinal(caminhoAtual); 
                respostaFinal = respParcial; 
            } 
        } 
        return; 
    } 
   
    for (int i=0; i<N; i++) { 
        // se nao tiver sido visitado e nao for diagonal às outras arestas 
        if (adj[caminhoAtual[level-1]][i] != 0 && 
            visited[i] == false) { 
            int temp = limite_atual; 
            pesoAtual += adj[caminhoAtual[level-1]][i]; 
            if (level==1) 
              limite_atual -= ((menorAresta(adj, caminhoAtual[level-1]) + 
                             menorAresta(adj, i))/2); 
            else
              limite_atual -= ((segundaMenor(adj, caminhoAtual[level-1]) + 
                             menorAresta(adj, i))/2); 
  
            // limite_atual + pesoAtual é o limite inferior atual 
            if (limite_atual + pesoAtual < respostaFinal) { 
                caminhoAtual[level] = i; 
                visited[i] = true; 
  
                
                TSPRec(adj, limite_atual, pesoAtual, level+1, 
                       caminhoAtual); 
            } 
  
            // caso não tenha funcionado, desfaz as mudanças
            pesoAtual -= adj[caminhoAtual[level-1]][i]; 
            limite_atual = temp; 
  
            // desfaz as mudanças do array de visitados
            memset(visited, false, sizeof(visited)); 
            for (int j=0; j<=level-1; j++) 
                visited[caminhoAtual[j]] = true; 
        } 
    } 
} 
  
 
void TSP(int adj[][100]) { 
    int caminhoAtual[N+1]; 
  
    // calcula o limite inferior atual 
    // usando a formula formula 1/2 * (soma da menor aresta + 
    // segunda menor aresta) for all edges. 
    int limite_atual = 0; 
    memset(caminhoAtual, -1, sizeof(caminhoAtual)); 
    memset(visited, 0, sizeof(caminhoAtual)); 
    for (int i=0; i<N; i++) 
        limite_atual += (menorAresta(adj, i) + 
                       segundaMenor(adj, i)); 
    limite_atual = (limite_atual&1)? limite_atual/2 + 1 : 
                                 limite_atual/2; 
  
    visited[0] = true; 
    caminhoAtual[0] = 0; 
    TSPRec(adj, limite_atual, 0, 1, caminhoAtual); 
} 

int main() { 
    cin >> N;
	vector<pairs> coords; //cria um vetor de pares ordenados
	int x, y;
	for(int i = 0; i < N; i++){
		cin >> x >> y;
		coords.push_back(make_pair(x, y)); //adiciona as coordenadas no vetor
	}

	for(int i = 0; i < N; i++){
		for(int j = i; j < N; j++){
			//calcula a distancia entre todos os pontos afim de fazer um grafo completo
			double d = calcDist(coords[i], coords[j]);
			adj[i][j] = d;
			adj[j][i] = d;
		}
	}
  
    TSP(adj); 
  
    printf("Custo : %d\n", respostaFinal); 
    printf("caminho : "); 
    for (int i=0; i<=N; i++) 
        printf("%d ", caminhoFinal[i] + 1); 
  
    return 0; 
} 