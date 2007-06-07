#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
  ifstream in("out.txt");
  string s;
  int count=0;
  int fileID=0;
  FILE* out = fopen("out0.txt","w");

  while(getline(in,s)){
    count++;
    if(count==200){
      fprintf(out,"%s",(char*)s.c_str());
      count =0;   
      char temp[200];
      sprintf(temp,"out%d.txt",++fileID);
      out = fopen(temp,"w");      
    }
    else{
      fprintf(out,"%s,",(char*)s.c_str());
    }
  }
  fclose(out);
}
