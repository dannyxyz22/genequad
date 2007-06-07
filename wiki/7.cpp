#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main(){
  ifstream in("pubMedsClean.txt");
  string s;
  int count=0;

  while(getline(in,s)){
    count++;
    if(count%7==0){
      if(s!=""){
	printf("Breaking in line %d\n",count);
	break;
      }
    }

  }
}
