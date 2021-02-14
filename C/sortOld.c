#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRINGS 100
int main( int argc, char *argv[] ){
  //Reversed and numerical change depending on options in commandline
  int reversed = 0;
  int numerical = 0;
  //Holds number of items in the file beingf read
  int numItems = 0;
  // 
  char strings[MAX_STRINGS][100];
  int nums[MAX_STRINGS];
  FILE *outfile;
  FILE *infile;
  if(argc==1){
    fprintf(stderr,"Invalid number of arguments");
    exit(1);
  }
  int i = 1;
  while(i<argc){
    switch(argv[i][0]){
      case'-':
        switch(argv[i][1]){
          case'o':
            i++;
            char* outputFileName = argv[i];
            outfile = fopen(outputFileName,"w");
            if(outfile == NULL){
              fprintf(stderr,"Unable to create/find output file");
              exit(1);
            }
          break;
          case 'r':
            reversed = 1;
          break;
          case 'n':
            numerical = 1;
          break;
          case 'h':
          printf("%s\n%s\n%s\n%s\n","-o specifies output file","-r reverses the sort order","-n for numerical values","Currently implemented, reverse, output file and numerical values");
          break;
          default:
            fprintf(stderr,"%s%s\n",argv[i]," is not a valid argument");
            exit(1);
          break;
        }
        break;
      //Arg is the file in input
      default :
        ;
            char* inputFileName = argv[i];
            infile = fopen(inputFileName,"r");
            if(infile){
              int pos = 0;
              char* line[50];
              while(fgets(line, 50, infile) != NULL){
                if(numerical == 1 && strcmp("0",line)!= 0 && atoi(line) == 0){
                  fprintf(stderr,"Non-Numerical Value entered\n");
                  exit(1);
                }
                strcpy(strings[pos], line);
                nums[pos] = atoi(line);
                numItems++;
                pos++;
                }
            }
            else{
              fprintf(stderr,"Invalid input file\n");
              exit(1);
            }



    }
    i++;
  }
  switch(reversed){
    //Not reversed
    case 0:
    ;

    switch(numerical){
      case 0:
      ;
        int strComp(const void* a, const void* b)
        {
          const char* aa = (const char*)a;
          const char* bb = (const char*)b;
          return strcmp(aa, bb);
        }
        qsort(strings, numItems, sizeof(strings[0]), strComp);
        printStringOutput(outfile,strings,numItems);
      break;
      case 1:
      ;
        int intComp (const void * a, const void * b)
        {
           return ( *(int*)a - *(int*)b );
        }
        qsort(nums, numItems, sizeof(nums[0]), intComp);
        printIntOutput(outfile,*nums,numItems);
      break;
    }
    break;
    //Reversed
    case 1:
      switch(numerical){
        case 0:
        ;
          int strComp(const void* a, const void* b)
          {
            const char* aa = (const char*)a;
            const char* bb = (const char*)b;
            return strcmp(bb, aa);
          }
          qsort(strings, numItems, sizeof(strings[0]), strComp);
          printStringOutput(outfile,strings,numItems);
        break;
        case 1:
        ;
          int intComp (const void * a, const void * b)
          {
             return ( *(int*)b - *(int*)a );
          }
          qsort(nums, numItems, sizeof(nums[0]), intComp);
          printIntOutput(outfile,nums,numItems);

        break;
    break;

  }
}
switch (numerical) {
  case 0:
  if(outfile != NULL){
    for(int j=0;j<numItems;j++){
      fprintf(outfile, "%s",strings[j] );
    }
  }
  else{
    for(int j=0;j<numItems;j++){
      fprintf(stdout, "%s",strings[j] );
    }
  }
  break;
  case 1:
    if(outfile != NULL){
      for(int j=0;j<numItems;j++){
        fprintf(outfile, "%d\n",nums[j] );
      }
    }
    else{
      for(int j=0;j<numItems;j++){
        fprintf(stdout, "%d\n",nums[j] );
      }
    }
  break;
}
}
void printIntOutput(FILE* outfile, int arr[],int numItems){


}
void printStringOutput(FILE* outfile, char **arr,int numItems){

}
