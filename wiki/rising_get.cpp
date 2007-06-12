#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sqlite3.h>



using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  printf("%s||\n",argv[9]);
  return 0;
}

int main(){
  string s;
  string::size_type pos = 0;

  sqlite3 *db;
  char* zErrMsg = 0;
  int rc = sqlite3_open("gene_info.db",&db);
  if(rc) {printf("bugged\n");return 0;}
  
  int count=0;

  
  char temp[20000];
  vector<int> wanted;
  vector<string> desc;
  
  string str;
  getline(cin,str); //dummy line

  int gID;
  int gcount=1;
  while(getline(cin,str)){
    if(gcount==26) break;
    sscanf(str.c_str(),"||%d",&gID);
    wanted.push_back(gID);
    desc.push_back(str);
    ++gcount;    
  }


  for(int i=0;i<wanted.size();i++){

    printf("%s",desc[i].c_str());
    sprintf(temp,"select * from gene_info where geneID = %d;",wanted[i]);    
    rc = sqlite3_exec(db,temp, callback, 0, &zErrMsg);
    if( rc!=SQLITE_OK){
      fprintf(stderr, "SQL error: %s\n",zErrMsg);
      fprintf(stderr, "Blamed string: %s\n",temp);
      sqlite3_free(zErrMsg);
    }

  }
  
  sqlite3_close(db);
}
