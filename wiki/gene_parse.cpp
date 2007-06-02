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

void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}


int main(){
  ifstream in("gene_info");
  string s;
  string::size_type pos = 0;

  sqlite3 *db;
  char* zErrMsg = 0;
  int rc = sqlite3_open("gene_info.db",&db);
  if(rc) {printf("bugged\n");return 0;}

  int count=0;

  getline(in,s);//ignore first line... only headers
  
  while(getline(in,s)){

    vector<string> fields;

    Tokenize(s,fields,"\t");


    char temp[20000];
    
    sprintf(temp,"insert into gene_info values(%d , %s , %s , '%s' , '%s', '%s','%s', '%s', '%s', '%s', '%s', '%s','%s', '%s', '%s', %s )",count++,
	    replace(fields[0]).c_str(), //taxID
	    replace(fields[1]).c_str(), //geneID
	    replace(fields[2]).c_str(), //symbol
	    replace(fields[3]).c_str(), //locusTag
	    replace(fields[4]).c_str(), //synonyms
	    replace(fields[5]).c_str(), //dbXrefs
	    replace(fields[6]).c_str(), //chromosome
	    replace(fields[7]).c_str(), //mapLocation
	    replace(fields[8]).c_str(), //description
	    replace(fields[9]).c_str(), //typeofGene
	    replace(fields[10]).c_str(),//sysmbolAuthority
	    replace(fields[11]).c_str(),//fullname
	    replace(fields[12]).c_str(),//nomenclature
	    replace(fields[13]).c_str(),//otherDesignations
	    replace(fields[14]).c_str());//date


    rc = sqlite3_exec(db,temp, NULL, 0, &zErrMsg);
    if( rc!=SQLITE_OK){
      fprintf(stderr, "SQL error: %s\n",zErrMsg);
      fprintf(stderr, "Blamed string: %s\n",temp);
      sqlite3_free(zErrMsg);
    }

  }
  sqlite3_close(db);
}
