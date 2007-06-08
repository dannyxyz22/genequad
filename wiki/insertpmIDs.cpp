#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sqlite3.h>

using namespace std;

string replace(string test){
  string ans;
  string::size_type pos=0;
  while( (pos = test.find("\'",pos))<test.size() ){
    test.replace(pos,1,"\'\'");
    pos = pos + 2;
  }
  ans = test;
  return ans;  
}

int main(){
  ifstream in("cleanPMids.txt");
  vector<string> fields(7);
  string::size_type pos = 0;

  sqlite3 *db;
  char* zErrMsg = 0;
  int rc = sqlite3_open("gene.db",&db);
  if(rc) {printf("bugged\n");return 0;}

  int count=0;

  while(1){
    fields.clear();
    for(int i=0;i<7;i++)      
      getline(in,fields[i]);

    if(fields[0]=="") break;
  

    char temp[20000];
    
    sprintf(temp,"insert into pubMed values(%s , '%s' , '%s' , %s , '%s', '%s')",
	    replace(fields[0]).c_str(),//pmID
	    replace(fields[1]).c_str(),//pubDate
	    replace(fields[2]).c_str(),//source
	    replace(fields[3]).c_str(),//number of authors
	    replace(fields[4]).c_str(),//paper title
	    replace(fields[5]).c_str() //issn
	    );

    rc = sqlite3_exec(db,temp, NULL, 0, &zErrMsg);
    if( rc!=SQLITE_OK){
      fprintf(stderr, "SQL error: %s\n",zErrMsg);
      fprintf(stderr, "Blamed string: %s\n",temp);
      sqlite3_free(zErrMsg);
      }
    printf("%s\n",(char*)fields[0].c_str());

  }
  sqlite3_close(db);
}
