#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sqlite3.h>



using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
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


  wanted.push_back(7157);
  wanted.push_back(7124);
  wanted.push_back(7422);
  wanted.push_back(7040);
  wanted.push_back(5743);
  wanted.push_back(3569);
  wanted.push_back(1956);
  wanted.push_back(2099);
  wanted.push_back(4790);
  wanted.push_back(3576);
  wanted.push_back(1029);
  wanted.push_back(348);
  wanted.push_back(4318);
  wanted.push_back(5468);
  wanted.push_back(351);
  wanted.push_back(3586);
  wanted.push_back(2064);
  wanted.push_back(596);
  wanted.push_back(1026);
  wanted.push_back(3479);



  for(int i=0;i<wanted.size();i++){

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
