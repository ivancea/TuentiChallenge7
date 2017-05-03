#include <iostream>
#include <vector>

using namespace std;

int main(){
	int t;
	cin >> t;
	
	for(int caseNumber=1; caseNumber<=t; caseNumber++){
		int r;
		cin >> r;
		
		vector<int> rolls(r);
		
		for(int i=0; i<r; i++){
			cin >> rolls[i];
		}
		
		int total = 0;
		int frameTotal = 0;
		int frameNumber = 1;
		bool secondRoll = false;
		
		cout << "Case #" << caseNumber << ":";
		for(int i=0; i<r && frameNumber <= 10; i++){
			int extraRollSum = 0;
			
			frameTotal += rolls[i];
			
			if(frameTotal == 10){
				if(secondRoll){
					extraRollSum = 1;
				}else{
					extraRollSum = 2;
				}
			}
			
			if(secondRoll || frameTotal == 10){
				for(int j=i+1; j<r && j<=i+extraRollSum; j++)
					frameTotal += rolls[j];
				total += frameTotal;
				frameTotal = 0;
				secondRoll = false;
				frameNumber++;
				cout << " " << total;
			}else{
				secondRoll = true;
			}
		}
		
		cout << endl;
	}
}