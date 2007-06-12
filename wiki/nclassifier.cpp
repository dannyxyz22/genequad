#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <map>
#include <cmath>
#define YEARS 7 //2002,2003,2004,2005,2006,2007,ALL(2008)

using namespace std;
//gene class to make sorting easier
class gene{
public:
  int geneID;
  int rank[YEARS];
  double myShifts[YEARS-2];//2002 and ALL don't count
  int articles[YEARS];  
  double perc[YEARS];
};

map<int,gene> genes;

//load genes
void loadGenes(){
  ifstream in("genes.txt");
  int id;
  string temp;
  while(getline(in,temp)){
    sscanf(temp.c_str(),"%d",&id);
    gene myGene;
    myGene.geneID=id;
    for(int i=0;i<YEARS;i++){
      myGene.rank[i]=-1;
      myGene.articles[i]=0;
    }
    genes[id]=myGene;
  }
}

void calcPerc(){
  FILE* in;
  for(int i=0;i<YEARS;i++){
    char temp[200];
    sprintf(temp,"200%c.txt",'2'+i);
    in = fopen(temp,"r");
    int geneID,articles;
    int myRank=1;
    int first=1;
    int lastArticle=-1;
    int skip=0;
    int totalArticles=0;
    while(  fscanf(in,"%d|%d",&geneID,&articles)!=EOF){      
      //useful for percentage calc
      genes[geneID].articles[i]=articles;
      totalArticles+=articles;
      
      //useful for ranking according to articles
      //it ranks using 1224 instead of 1223
      //which means
      // A = 10
      // B = 8
      // C = 8
      // D = 5
      // A will be first, B and C second
      // and D will be fourth
      if(first){
	first=0;
	lastArticle=articles;
      }
      if(lastArticle==articles){
	genes[geneID].rank[i]=myRank;
	skip++;
      }
      else{
	myRank+=skip;
	skip=1;
	genes[geneID].rank[i]=myRank;
      }
      lastArticle=articles;          
    }
    //now rank the last ones 
    //and calculate the percentage
    myRank+=skip;
    for(map<int,gene>::iterator it=genes.begin();it!=genes.end();it++){
      (*it).second.perc[i]= 100*(*it).second.articles[i]/(double)totalArticles;
      if( (*it).second.rank[i]==-1){
	(*it).second.rank[i]=myRank;
      }
    }
  }
}
void calcShifts(){
  for(map<int,gene>::iterator it=genes.begin();it!=genes.end();it++){
    for(int i=0;i<YEARS-2;i++){ //all doesn't count as well as 2002
      (*it).second.myShifts[i] = (*it).second.perc[i+1] -(*it).second.perc[i];
    }
  }    
}

int year;

bool compare(gene g1, gene g2){
  if ( fabs(g1.myShifts[year]- g2.myShifts[year]) > 0.000000001)
    return (g1.myShifts[year] > g2.myShifts[year]);
  else
    return (g1.geneID < g2.geneID);
  
}
void geneSort(){
  vector<gene> myGenes;
  FILE* out;
  
  for(map<int,gene>::iterator it=genes.begin();it!=genes.end();it++){
    myGenes.push_back( (*it).second);
  }    
  for(int j=0;j<YEARS-2;j++){
    year = j;
    char myFile[200];
    sprintf(myFile,"star200%c.txt",'3'+j);
    out = fopen(myFile,"w");
    sort(myGenes.begin(),myGenes.end(),compare);   
    fprintf(out,"||*GeneID* || *Percentage shift(\%)* || *Rank in %d* || *Rank in %d* || *GeneRIFs in %d* || *GeneRIFs in %d* ||\n", 2002+j,2002+j+1,2002+j,2002+j+1);
    for(int i=0;i<myGenes.size();i++){
      fprintf(out,"||%6d||%+5.2lf||%5d||%5d||%5d||%5d||\n",myGenes[i].geneID,myGenes[i].myShifts[j], myGenes[i].rank[j],myGenes[i].rank[j+1],
	      myGenes[i].articles[j],myGenes[i].articles[j+1]);
    }
  }
}


int main(){
  loadGenes();
  calcPerc();
  calcShifts();
  geneSort();
  printf("GeneID\t2002\t2003\t2004\t2005\t2006\t2007\tall\t02->03\t03->04\t04->05\t05->06\t06->07\n");
  for(map<int,gene>::iterator it=genes.begin();it!=genes.end();it++){
    printf("%d\t",(*it).first);
    for(int i=0;i<YEARS;i++){
      printf("%5.2lf\t",(*it).second.perc[i]);
    }
    for(int i=0;i<YEARS-2;i++){
      printf("%+5.2lf\t",(*it).second.myShifts[i]);
    }
    printf("\n");
  }
}
