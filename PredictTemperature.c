//AUTHOR : HAMORA HADI

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define ALLOC_COUNT ((long)16)

int main() {

  long N,x,y;
  char s[128];
  long *year,*month;
  double *t,*minv,*maxv;
  long missing;
  long missing_alloc;
  long *missing_i;
  double *missing_v;
  double spread[12];
  double avemin[12],avemax[12];
  double count[12];
  char *valid_min,*valid_max;
  
  missing = 0;
  missing_i = (long *)malloc(ALLOC_COUNT*sizeof(long));
  missing_v = (double *)malloc(ALLOC_COUNT*sizeof(double));
  missing_alloc = ALLOC_COUNT;
  
  // get the number of entries
  scanf("%ld",&N);
  // pull out the table headings
  for (x=0;x<4;x++) {
    scanf("%s",&(s[0]));
  }
  year = (long *)malloc(N*sizeof(long));
  month = (long *)malloc(N*sizeof(long));
  t = (double *)malloc(N*sizeof(double));
  minv = (double *)malloc(N*sizeof(double));
  valid_min = (char *)malloc(N*sizeof(char));
  memset(valid_min,0,N*sizeof(char));
  maxv = (double *)malloc(N*sizeof(double));
  valid_max = (char *)malloc(N*sizeof(char));
  memset(valid_max,0,N*sizeof(char));
  
  for (x=0;x<N;x++) {
    scanf("%ld",&(year[x]));
    scanf("%s",&(s[0]));
    if (strcmp(s,"January")==0) { month[x] = 0; }
    if (strcmp(s,"February")==0) { month[x] = 1; }
    if (strcmp(s,"March")==0) { month[x] = 2; }
    if (strcmp(s,"April")==0) { month[x] = 3; }
    if (strcmp(s,"May")==0) { month[x] = 4; }
    if (strcmp(s,"June")==0) { month[x] = 5; }
    if (strcmp(s,"July")==0) { month[x] = 6; }
    if (strcmp(s,"August")==0) { month[x] = 7; }
    if (strcmp(s,"September")==0) { month[x] = 8; }
    if (strcmp(s,"October")==0) { month[x] = 9; }
    if (strcmp(s,"November")==0) { month[x] = 10; }
    if (strcmp(s,"December")==0) { month[x] = 11; }
    t[x] = ((double)year[x])*12.0+((double)month[x]);
    
    scanf("%s",&(s[0]));
    if (s[0]=='M') {
      maxv[x] = -100;
      missing_i[missing] = x;
      missing_v[missing] = 0.0;
      missing++;
      if (missing==missing_alloc) {
        missing_i = (long *)realloc(missing_i,(missing_alloc+ALLOC_COUNT)*sizeof(long));
        missing_v = (double *)realloc(missing_v,(missing_alloc+ALLOC_COUNT)*sizeof(double));
        missing_alloc += ALLOC_COUNT;
      }
    } else {
      sscanf(s,"%lf",&(maxv[x]));
      valid_max[x] = 1;
    }
    scanf("%s",&(s[0]));
    if (s[0]=='M') {
      minv[x] = -100;
      missing_i[missing] = x;
      missing_v[missing] = 0.0;
      missing++;
      if (missing==missing_alloc) {
        missing_i = (long *)realloc(missing_i,(missing_alloc+ALLOC_COUNT)*sizeof(long));
        missing_v = (double *)realloc(missing_v,(missing_alloc+ALLOC_COUNT)*sizeof(double));
        missing_alloc += ALLOC_COUNT;
      }
    } else {
      sscanf(s,"%lf",&(minv[x]));
      valid_min[x] = 1;
    }
    
  }
  
  
  // compute some useful periodic info to help estimate
  for (x=0;x<12;x++) { spread[x] = 0.0; count[x] = 0.0; }
  for (x=0;x<N;x++) {
    if ( (valid_min[x]==1)&&(valid_max[x]==1) ) {
      spread[month[x]] += (maxv[x]-minv[x]);
      count[month[x]] += 1.0;
    }
  }
  for (x=0;x<12;x++) {
    spread[x] /= count[x];
//printf("month=%ld spread=%lf\n",x,spread[x]);
  }

  for (x=0;x<12;x++) { avemin[x] = 0.0; count[x] = 0.0; }
  for (x=0;x<N;x++) {
    if (valid_min[x]==1) {
      avemin[month[x]] += minv[x];
      count[month[x]] += 1.0;
    }
  }
  for (x=0;x<12;x++) {
    avemin[x] /= count[x];
  }  
  
  for (x=0;x<12;x++) { avemax[x] = 0.0; count[x] = 0.0; }
  for (x=0;x<N;x++) {
    if (valid_max[x]==1) {
      avemax[month[x]] += maxv[x];
      count[month[x]] += 1.0;
    }
  }
  for (x=0;x<12;x++) {
    avemax[x] /= count[x];
  }    
  for (x=0;x<missing;x++) {
//printf("x=%ld missing_i=%ld year=%ld month=%ld minv=%lf maxv=%lf\n",
//       x,missing_i[x],year[missing_i[x]],month[missing_i[x]],minv[missing_i[x]],maxv[missing_i[x]]);
    
    if ( (valid_min[missing_i[x]]==0)&&(valid_max[missing_i[x]]==0) ) {
      if (missing_i[x]==missing_i[x+1]) {
        printf("%lf\n",avemin[month[missing_i[x]]]);
      } else {
        printf("%lf\n",avemax[month[missing_i[x]]]);
      }
    } else if (valid_min[missing_i[x]]==0) {
      printf("%lf\n",maxv[missing_i[x]]-spread[month[missing_i[x]]]);
    } else {
      printf("%lf\n",minv[missing_i[x]]+spread[month[missing_i[x]]]);
    }
  }
  
  return 0;
}
