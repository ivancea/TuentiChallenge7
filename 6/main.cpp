#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cmath>

using namespace std;

using llong = int64_t;

struct Shortcut {
	llong from;
	llong to;
	llong years;
	
	Shortcut(){}
	
	Shortcut(llong _from, llong _to, llong _years)
		: from(_from), to(_to), years(_years){}
};

llong getYears(llong from, llong to){
	if(to <= from){
		return 0;
	}
	
	const llong distance = to - from;
	
	return from*distance + ((distance-1)*(1 + to-from-1))/2;
}

bool isValidShortcut(map<llong, map<llong,llong> > shortcuts, llong a, llong b, llong y){
	if(getYears(a,b) < y){
		return false;
	}
	
	auto isRedundant = [](llong a1,llong b1,llong y1, llong a2,llong b2,llong y2) -> bool{
		return (a1>=a2 && b1<=b2 && getYears(a1,a2) + y2 + getYears(b2,b1) <= y1)
			|| (a1==a2 && b1<=b2 && y1>=y2);
	};
	
	for(auto it1 = shortcuts.begin(); it1 != shortcuts.end();){
		bool deletedInner = false;
		for(auto it2 = it1->second.begin(); it2 != it1->second.end();){
			if(isRedundant(a,b,y, it1->first,it2->first,it2->second)){
				return false;
			}
			if(isRedundant(it1->first,it2->first,it2->second, a,b,y)){
				it2 = it1->second.erase(it2);
				if(it2 == it1->second.end()){
					it1 = shortcuts.erase(it1);
					deletedInner = true;
					break;
				}
			}else it2++;
		}
		if(!deletedInner){
			it1++;
		}
	}
	
	return true;
}

vector<Shortcut> getShortcuts(int n) {
	map<llong, map<llong,llong> > mapShortcuts;
	int shortcutCount = 0;
	while(n-->0){
		llong a,b,y;
		cin >> a >> b >> y;
		
		if(isValidShortcut(mapShortcuts, a,b,y)){
			auto& fromIt = mapShortcuts[a];
			auto last = fromIt.find(b);
			if(last == fromIt.end()){
				fromIt[b] = y;
				shortcutCount++;
			}else if(last->second > y){
				last->second = y;
			}
		}
	}
	
	vector<Shortcut> shortcuts;
	shortcuts.reserve(shortcutCount);
	for(auto it : mapShortcuts){
		for(auto it2 : it.second){
			shortcuts.emplace_back(Shortcut(it.first, it2.first, it2.second));
		}
	}
	
	return shortcuts;
}


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
	vector< vector<T> > _matrix;
	
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
		int finalFloor;
		int n;
		
		cin >> finalFloor >> n;
		
		vector<Shortcut> shortcuts = getShortcuts(n);
		
		set<int> realFloors;
		realFloors.emplace(1);
		realFloors.emplace(finalFloor);
		
		for(auto& it : shortcuts){
			realFloors.emplace(it.from);
			realFloors.emplace(it.to);
		}
		
		map<int,int> floorToNode;
		{
			int i = 0;
			for(auto it : realFloors){
				floorToNode[it] = i;
				++i;
			}
		}
		
		Graph<llong> graph(floorToNode.size(), -1);
		graph.connectIfLesser(floorToNode[1], floorToNode[finalFloor], getYears(1, finalFloor));
		
		for(auto it1 : shortcuts){
			graph.connectIfLesser(floorToNode[it1.from], floorToNode[it1.to], it1.years);
			graph.connectIfLesser(floorToNode[it1.to], floorToNode[it1.from], it1.years);
			graph.connectIfLesser(floorToNode[it1.to], floorToNode[finalFloor], getYears(it1.to, finalFloor));
			graph.connectIfLesser(floorToNode[1], floorToNode[it1.from], getYears(1, it1.from));
			
			for(auto it2 : shortcuts){
				if(it1.from != it2.from || it1.to != it2.to){
					graph.connectIfLesser(floorToNode[it1.to], floorToNode[it2.to], getYears(it1.to, it2.to));
					graph.connectIfLesser(floorToNode[it1.to], floorToNode[it2.from], getYears(it1.to, it2.from));
					graph.connectIfLesser(floorToNode[it1.from], floorToNode[it2.to], getYears(it1.from, it2.to));
					graph.connectIfLesser(floorToNode[it1.from], floorToNode[it2.from], getYears(it1.from, it2.from));
				}
			}
		}
		
		llong total = graph.getDistance(floorToNode[1], floorToNode[finalFloor]);
		
		cout << "Case #" << caseNumber << ": " << total << endl;
	}
}