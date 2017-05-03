
// Se me han ocurrido muchas mejoras para este challenge... cuando ya había enviado el submit :D!

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


void addSections(int& straight, int& curve, int& doubleStraight, bool curveStrategy){
	int usedStraight = 0;
	
	if(curve >= 8){
		curve -= 8;
		if(doubleStraight >= 1){
			doubleStraight -= 1;
		}else if(straight >= 2){
			straight -= 2;
			usedStraight += 2;
		}
	}else if(curve >= 6){
		if(straight >= 2){
			curve -= 6;
			straight -= 2;
			usedStraight += 2;
		}
	}
	
	if(curveStrategy){
		while(curve >= 4 && (doubleStraight >= 1 || straight >= 2)){
			curve -= 4;
			if(doubleStraight >= 1){
				doubleStraight -= 1;
			}else{
				straight -= 2;
				usedStraight += 2;
			}
		}
	}else{
		while(curve >= 4 && doubleStraight*2 + straight >= 4){
			curve -= 4;
			if(doubleStraight >= 2){
				doubleStraight -= 2;
			}else if(doubleStraight >= 1){
				doubleStraight -= 1;
				straight -= 2;
				usedStraight += 2;
			}else{
				straight -= 4;
				usedStraight += 4;
			}
		}
	}
	
	while(curve >= 2){
		if(straight >= 2){
			curve -= 2;
			straight -= 2;
			usedStraight += 2;
			if(doubleStraight >= 2){
				doubleStraight -= 2;
			}else if(doubleStraight == 1){
				doubleStraight -= 1;
			}
		}else break;
	}
	
	doubleStraight = doubleStraight%2;
	if(doubleStraight == 1 && straight >= 2){
		doubleStraight = 0;
		straight -= 2;
		usedStraight += 2;
	}
	
	int remainder = straight%2;
	usedStraight += straight-remainder;
	straight = remainder;
	
	if(usedStraight >= 1 && doubleStraight == 1 && straight == 1){
		doubleStraight = 0;
	}
}

int main(){
	int t;
	cin >> t;
	
	for(int caseNumber=1; caseNumber<=t; caseNumber++){
		int straight,curve,doubleStraight;
		cin >> straight >> curve >> doubleStraight;
		int total = straight + curve + doubleStraight;
		
		int straight2 = straight,
			curve2 = curve,
			doubleStraight2 = doubleStraight,
			total2 = total;
			
		
		if(curve >= 4){
			curve -= 4;
			addSections(straight, curve, doubleStraight, true);
		}
		
		if(curve2 >= 4){
			curve2 -= 4;
			addSections(straight2, curve2, doubleStraight2, false);
		}
		
		int result = (total - straight - curve - doubleStraight),
			result2 = (total2 - straight2 - curve2 - doubleStraight2);
		
		/*cerr << caseNumber << ": " << straight << " - " << curve << " - " << doubleStraight << " // "
								   << straight2 << " - " << curve2 << " - " << doubleStraight2 << endl;*/
		
		cout << "Case #" << caseNumber << ": " << max(result, result2) << endl;
	}
}
