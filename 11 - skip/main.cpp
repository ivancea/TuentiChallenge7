#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>

using namespace std;

using Color = int16_t;

class World {
	vector< list<Color> > _subColors;
	vector< 
	vector< vector<Color> > _wormholes; // Wormholes
};


template<typename T>
struct Node{
	T value;
	bool visited;
	
	bool hasCache;
	set<int> neighbours;
	
	Node() : hasCache(false){}
	
	Node(T _value, bool _visited)
		: value(_value), visited(_visited), hasCache(false){}
};

template<typename T>
class Graph {
	vector< vector<short> > _matrix;
	
	T _infiniteValue;
	
public:

	Graph(int nodeCount, T infiniteValue){
		_infiniteValue = infiniteValue;
		_matrix.resize(nodeCount, vector<T>(nodeCount, infiniteValue));
		
		for(int i=0; i<nodeCount; i++){
			_matrix[i][i] = T();
		}
	}
	
	Graph(const Graph&) = delete;
	
	Graph(Graph&& graph){
		_matrix = graph._matrix;
	}
	
	void connect(int n, int m, T value){
		_matrix[n][m] = value;
	}
	
	void connectIfLesser(int n, int m, T value){
		if(_matrix[n][m] == _infiniteValue || _matrix[n][m] > value){
			_matrix[n][m] = value;
		}
	}
	
	void disconnect(int n, int m){
		_matrix[n][m] = _infiniteValue;
	}
	
	T getConnection(int a, int b){
		return _matrix[a][b];
	}
	
	set<int> getNeighbours(int node){
		set<int> neighbours;
		
		for(int i=0; i<_matrix.size(); i++){
			if(i != node && _matrix[node][i] != _infiniteValue){
				neighbours.insert(i);
			}
		}
		
		return neighbours;
	}
	
	T getDistance(int start, int end){
		// Setup
		vector<Node<T>> nodes(_matrix.size(), Node<T>(_infiniteValue, false));
		set<int> nextNodes;
		
		nodes[start].value = 0;
		nextNodes.emplace(start);
		
		// Dijkstra
		while(nextNodes.size() > 0){
			int node = *nextNodes.begin();
			nextNodes.erase(node);
			nodes[node].visited = true;
			
			if(!nodes[node].hasCache){
				nodes[node].neighbours = getNeighbours(node);
				nodes[node].hasCache = true;
			}
			
			for(int neighbour : nodes[node].neighbours){
				if(nodes[neighbour].value == _infiniteValue 
				|| nodes[neighbour].value > nodes[node].value + _matrix[node][neighbour]){
					nodes[neighbour].value = nodes[node].value + _matrix[node][neighbour];
					nodes[neighbour].visited = false;
				}
				
				if(!nodes[neighbour].visited){
					nextNodes.emplace(neighbour);
				}
			}
		}
		
		return nodes[end].value;
	}
};


int main(){
	int t;
	cin >> t;
	
	for(int caseNumber=1; caseNumber<=t; caseNumber++){
		map<string, set<string> > colors;
		vector< map<string, int> > galaxies;
		vector< pair<string, pair<int,int> > > wormholes;
		
		int k;
		cin >> k;
		
		string colorName;
		cin >> colorName;
		auto& colorList = colors[colorName];
		
		int colorCount;
		cin >> colorCount;
		
		while(colorCount-->0){
			cin >> colorName;
			auto& t = colors[colorName];
			if(t.size() > 0){
				colorList.insert(t.begin(), t.end());
			}else{
				colorList.insert(colorName);
			}
		}
		
		int galaxyCount;
		cin >> galaxyCount;
		galaxies.resize(galaxyCount);
		for(int i=0; i<galaxyCount; i++){
			cin >> colorCount;
			while(colorCount-->0){
				int gatherTime;
				cin >> colorName >> gatherTime;
				galaxies[i][colorName] = gatherTime;
			}
		}
		
		int wormholeCount;
		cin >> wormholeCount;
		wormholes.resize(wormholeCount);
		for(int i=0; i<wormholeCount; i++){
			cin >> wormholes[i].first
				>> wormholes[i].second.first
				>> wormholes[i].second.second;
		}
		
	}
}

/*

Guardar en cada nodo el minimo numero de pasos, actualizable
Guardar en cada nodo los colores con los que se ha llegado
(si al volver a pasar, se repiten y el tiempo necesario es mayor o igual, se salta el nodo)
Los colores se calculan restandole a los colores del nodo anterior los colores del tunel
(Si son varios sets de colores los del anterior, se copian solo los que tengan el color del tunel)

El ciclo es:
-Por cada nodo, tratar de atravesarlo, mirando hacia atras si existen los colores
 (mirando por todos los nodos anteriores hasta llegar a un tunel que tenga alguno de esos colores, en tal caso, se salta el nodo)
 (Guardar una lista de listas de posibles colores que podria haber elegido, y lista de colores que ya se tienen.
   Al pasar por un wormhole, limpiar de las listas ese color. Guardar tambien el coste de cada lista)

Lista de colores actuales, lista de colores posibles con sus costes y lista de deudas
-Si el color del wormhole no existe en actuales ni en posibles, siguiente nodo
-Si existe en actuales, se elimina y se elimina ese color de todos los posibles (IMPORTANTE: tambien al coger color)

   
*/