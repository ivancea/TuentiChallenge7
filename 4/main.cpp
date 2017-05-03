#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Number{
	int number;
	int count;
};

inline bool isValid(int a, int b, int c){
	return a < b+c && b < a+c && c < a+b;
}

inline bool isValid(int* values){
	return isValid(values[0], values[1], values[2]);
}

inline bool isValid(const vector<Number>& numbers, const int* indexes){
	return isValid(numbers[indexes[0]].number, numbers[indexes[1]].number, numbers[indexes[2]].number);
}

inline int getPerimeter(const vector<Number>& numbers, const int* indexes){
	return numbers[indexes[0]].number + numbers[indexes[1]].number + numbers[indexes[2]].number;
}

void moveIndexes(const vector<Number>& numbers, int* indexes){
	while(indexes[0] < numbers.size()){
		indexes[1]++;
		
		if(indexes[1] >= numbers.size() || indexes[1] == numbers.size()-1 && numbers[indexes[1]].count == 1){
			indexes[0]++;
			if(indexes[0] < numbers.size()){
				indexes[1] = indexes[0];
				if(numbers[indexes[0]].count == 1){
					indexes[1]++;
				}
			}else break;
		}
		
		indexes[2] = indexes[1];
		if(numbers[indexes[1]].count == 2 && indexes[0] != indexes[1]
		|| indexes[0] == indexes[1] && numbers[indexes[1]].count >= 3)
			break;
	}
}

int solve2(vector<Number>& numbers){
	const int n = numbers.size();
	
	int result = -1;
	
	int indexes[] = {0,-1,0};
	
	moveIndexes(numbers, indexes);
	
	while(indexes[0] < n){
		for(; indexes[2] < n; indexes[2]++){
			if(isValid(numbers, indexes)){
				int perimeter = getPerimeter(numbers, indexes);
				
				if(result == -1 || perimeter < result){
					result = perimeter;
				}
				
				moveIndexes(numbers, indexes);
				break;
			}else{
				if(numbers[indexes[2]].number >= numbers[indexes[0]].number + numbers[indexes[1]].number){
					moveIndexes(numbers, indexes);
					break;
				}
			}
		}
	}
	
	return result;
}
int solve(vector<Number>& numbers){
	const int n = numbers.size();
	
	int result = -1;
	
	for(int i=0; i<numbers.size() && (result==-1 || numbers[i].number*3 < result); i++){
		for(int j=i; j<numbers.size() && (result==-1 || numbers[i].number + numbers[j].number*2 < result); j++){
			if(i==j && numbers[i].count < 2){
				continue;
			}
			
			for(int k=j; k<numbers.size() && (result==-1 || numbers[i].number + numbers[j].number + numbers[k].number < result); k++){
				if(i==j && j==k && numbers[k].count < 3
				|| i!=j && j==k && numbers[k].count < 2){
					continue;
				}
				
				if(isValid(numbers[i].number, numbers[j].number, numbers[k].number)){
					int perimeter = numbers[i].number + numbers[j].number + numbers[k].number;
					
					if(result == -1 || perimeter < result){
						result = perimeter;
					}
				}else{
					if(numbers[k].number >= numbers[i].number + numbers[j].number){
						break;
					}
				}
			}
		}
	}
	
	return result;
}

int main(){
	int t;
	cin >> t;
	
	for(int i=1; i<=t; i++){
		int n;
		cin >> n;
		
		map<int,int> values;
		
		while(n-->0){
			int k;
			cin >> k;
			values[k]++;
		}
		
		vector<Number> numbers(values.size());
		
		int l = 0;
		for(auto it : values){
			numbers[l].number = it.first;
			numbers[l].count = it.second;
			++l;
		}
		
		
		int result = solve(numbers);
		
		
		cout << "Case #" << i << ": ";
		if(result >= 0)
			cout << result << endl;
		else
			cout << "IMPOSSIBLE" << endl;
	}
}