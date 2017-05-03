#include <iostream>

using namespace std;

int main(){
	int t;
	cin >> t;
	
	for(int i=1; i<=t; i++){
		int n;
		cin >> n;
		
		int total = 0;
		
		while(n-->0){
			int k;
			cin >> k;
			total += k;
		}
		
		cout << "Case #" << i << ": " << (total/8 + (total%8!=0)) << endl;
	}
}