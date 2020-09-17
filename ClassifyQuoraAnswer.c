

/*

Quora uses a combination of machine learning (ML) algorithms and moderation to ensure high-quality content on the site. 
High answer quality has helped Quora distinguish itself from other Q&A sites on the web.  

->Constraints:

0 0 0

->Sample Input:

5 23
2LuzC +1 1:2101216030446 2:1.807711 3:1 4:4.262680 5:4.488636 6:87.000000 7:0.000000 8:0.000000 9:0 10:0 11:3.891820 12:0 13:1 14:0 15:0 16:0 17:1 18:1 19:0 20:2 21:2.197225 22:0.000000 23:0.000000
LmnUc +1 1:99548723068 2:3.032810 3:1 4:2.772589 5:2.708050 6:0.000000 7:0.000000 8:0.000000 9:0 10:0 11:4.727388 12:5 13:1 14:0 15:0 16:1 17:1 18:0 19:0 20:9 21:2.833213 22:0.000000 23:0.000000
ZINTz -1 1:3030695193589 2:1.741764 3:1 4:2.708050 5:4.248495 6:0.000000 7:0.000000 8:0.000000 9:0 10:0 11:3.091042 12:1 13:1 14:0 15:0 16:0 17:1 18:1 19:0 20:5 21:2.564949 22:0.000000 23:0.000000
gX60q +1 1:2086220371355 2:1.774193 3:1 4:3.258097 5:3.784190 6:0.000000 7:0.000000 8:0.000000 9:0 10:0 11:3.258097 12:0 13:1 14:0 15:0 16:0 17:1 18:0 19:0 20:5 21:2.995732 22:0.000000 23:0.000000
5HG4U -1 1:352013287143 2:1.689824 3:1 4:0.000000 5:0.693147 6:0.000000 7:0.000000 8:0.000000 9:0 10:1 11:1.791759 12:0 13:1 14:1 15:0 16:1 17:0 18:0 19:0 20:4 21:2.197225 22:0.000000 23:0.000000
2
PdxMK 1:340674897225 2:1.744152 3:1 4:5.023881 5:7.042286 6:0.000000 7:0.000000 8:0.000000 9:0 10:0 11:3.367296 12:0 13:1 14:0 15:0 16:0 17:0 18:0 19:0 20:12 21:4.499810 22:0.000000 23:0.000000
ehZ0a 1:2090062840058 2:1.939101 3:1 4:3.258097 5:2.995732 6:75.000000 7:0.000000 8:0.000000 9:0 10:0 11:3.433987 12:0 13:1 14:0 15:0 16:1 17:0 18:0 19:0 20:3 21:2.639057 22:0.000000 23:0.000000

->Output :

PdxMK +1
ehZ0a -1

Good Luck
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

  long x,N,train,M,param,Q,query,pos,decision;
  char *in,*name;
  double **tp,*p;
  double *mean_p,*mean_n,*count_p,*count_n;
  double *v;
  double dp,dn;
  long vote_p,vote_n;
  
  in = (char *)malloc(1024*sizeof(char));
  name = (char *)malloc(1024*sizeof(char));
  
  scanf("%ld %ld",&N,&M);
  
  tp = (double **)malloc(N*sizeof(double *));
  p = (double *)malloc(M*sizeof(double));
  v = (double *)malloc(N*sizeof(double));
  
  // GET ALL OF THE TRAINING DATA
  for (train=0;train<N;train++) {
    tp[train] = (double *)malloc(M*sizeof(double));
    
    // read identifier
    scanf("%s",name);
    
    // read evaluation of training data (+1/-1)
    scanf("%s",in);
    sscanf(in,"%lf",&(v[train]));
    
    // read parameters
    for (param=0;param<M;param++) {
      scanf("%s",in);
      
      pos = 0; while (in[pos]!=':') { pos++; }
      memmove(&(in[0]),&(in[pos+1]),strlen(in)-pos-1);
      
      sscanf(in,"%lf",&(tp[train][param]));
    }
  }

  // SIMPLE DECISION PROCESS
  //   assume all variables are independent (BAD ASSUMPTION)
  //   get the mean of all +1 and -1 parameters
  //   processing will find dist from each mean and vote
  mean_p = (double *)malloc(M*sizeof(double));
  count_p = (double *)malloc(M*sizeof(double));
  mean_n = (double *)malloc(M*sizeof(double));
  count_n = (double *)malloc(M*sizeof(double));
  for (x=0;x<M;x++) {
    mean_p[x] = 0.0; count_p[x] = 0.0;
    mean_n[x] = 0.0; count_n[x] = 0.0;
  }
  for (train=0;train<N;train++) {
    if (v[train]>0) {
      for (x=0;x<M;x++) {
        mean_p[x] += tp[train][x];
        count_p[x] += 1.0;
      }
    } else {
      for (x=0;x<M;x++) {
        mean_n[x] += tp[train][x];
        count_n[x] += 1.0;
      }      
    }
  }
  for (x=0;x<M;x++) {
    if (count_p[x]>0.0) {
      mean_p[x] /= count_p[x];
    }
    if (count_n[x]>0.0) {
      mean_n[x] /= count_n[x];
    }
  }
  
  // GET ALL OF THE TESTING DATA - DO PROCESSING
  scanf("%ld",&Q);
  for (query=0;query<Q;query++) {
    scanf("%s",name);
    for (param=0;param<M;param++) {
      scanf("%s",in);
      
      pos = 0; while (in[pos]!=':') { pos++; }
      memmove(&(in[0]),&(in[pos+1]),strlen(in)-pos-1);
      
      sscanf(in,"%lf",&(p[param]));
    }
    
    vote_p = 0; vote_n = 0;
    for (x=0;x<M;x++) {
      dp = (p[x]-mean_p[x])*(p[x]-mean_p[x]);
      dn = (p[x]-mean_n[x])*(p[x]-mean_n[x]);
      if (dp<dn) {
        vote_p++;
      } else {
        vote_n++;
      }
    }
    
    if (vote_p>=vote_n) {
      printf("%s +1\n",name);
    } else {
      printf("%s -1\n",name);
    }
    
  }
  
  return 0;
}
