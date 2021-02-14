#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define INITIAL_BUFFER 1

//QSort compare function
int compareNumericalStrings(const void* a, const void* b){
  //Convert them back to strings
  const char* aa = *(const char **)a;
  const char* bb = *(const char **)b;
  //Find if there is a leading number, 0 if not
  int aDigit = atoi(aa);
  int bDigit = atoi(bb);
  //If they're equal then sort by string
  if(aDigit == bDigit){
    return strcoll(aa, bb);
  }
  //Sort by differnce in number
  else{
    return aDigit - bDigit;
  }
}

//Qsort compare strings function
int compareStrings(const void* a, const void* b){
  //Convert them back to strings
  const char* aa = *(const char **)a;
  const char* bb = *(const char **)b;
  return strcoll(aa, bb);
}


int main( int argc, char *argv[] ){
  //Set locale to try match linux sort better
  setlocale(LC_ALL,"");
  //Malloc the array of strings
  char **strings = malloc(INITIAL_BUFFER * sizeof(char*));
  if(strings == NULL){
    fprintf(stderr,"%s\n"," Failed to reserve memory for strings");
    exit(1);
  }
  int amountOfStrings = 0;
  //Reversed and numerical change depending on options in commandline
  int reversed = 0;
  int numerical = 0;
  int fOpened = 0;
  int outfileFound = 0;
  FILE *outfile;
  FILE *infile;
  if(argc==1){
    fprintf(stderr,"Invalid number of arguments");
    exit(1);
  }
  int i = 1;
  while(i<argc){
    //If this arg is an option
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
            outfileFound = 1;
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
              fOpened = 1;

              int eof = 0;
              int stringPos = 0;
              while(eof==0){
                int pos = 0;
                int lineSize = 1;
                //Create the string for the line
                char *line = malloc(1*(sizeof(char)));
                if(line == NULL){
                  fprintf(stderr,"%s\n"," Failed to reserve memory for line");
                  exit(1);
                }
                amountOfStrings++;
                char character = 's';
                while(character != '\n'){
                  if(fscanf(infile,"%c",&character)==EOF){
                    eof = 1;
                    break;
                  }
                  else if(character == '\n'){
                    break;
                  }
                    lineSize++;
                    //printf("%c %d\n",character,lineSize);
                    if(lineSize>INITIAL_BUFFER){
                      line = realloc(line, (lineSize+INITIAL_BUFFER)*(sizeof(char)));
                      if (line == NULL)
                      {
                        fprintf(stderr,"%s\n"," Failed to reserve memory for line");
                        exit(1);
                      }
                    }
                    line[pos] = character;
                    pos++;
                }
                line[pos+1] = '\0';
                //printf("%s\n", line);
                  if(amountOfStrings>INITIAL_BUFFER){
                    strings = (char **) realloc(strings, (amountOfStrings+INITIAL_BUFFER)* sizeof(char*));
                    if (strings == NULL)
                    {
                      fprintf(stderr,"%s\n"," Failed to reserve memory for strings");
                      exit(1);
                    }
                  }
                  strings[stringPos] = malloc(lineSize * sizeof(char));
                  if (strings[stringPos] == NULL)
                  {
                    fprintf(stderr,"%s\n"," Failed to reserve memory for strings");
                    exit(1);
                  }
                  strcpy(strings[stringPos],line);
                  stringPos++;

                free(line);
              }
              amountOfStrings = stringPos;
              fclose(infile);
            }

  }
    i++;
  }
  if(fOpened == 0){
    fprintf(stderr,"Unable to find input file\n");
    exit(1);
  }
  //Sort the input
  switch(numerical){
    case 0:
    qsort(strings,amountOfStrings,sizeof(char *),compareStrings);
    break;
    case 1:
    qsort(strings,amountOfStrings,sizeof(char *),compareNumericalStrings);
    break;
  }
  //Printing out the result depending on the -r option
  switch(reversed){
    case 0:
      if(outfileFound == 1){
        for(int i =0;i<amountOfStrings;i++){
          fprintf(outfile,"%s\n",strings[i] );
          free(strings[i]);
        }
      }
      else{
        for(int i =0;i<amountOfStrings;i++){
          fprintf(stdout,"%s\n",strings[i] );
          free(strings[i]);
        }
      }
    break;
    case 1:
    if(outfileFound == 1){
      for(int i =amountOfStrings-1;i>=0;i--){
        fprintf(outfile,"%s\n",strings[i] );
        free(strings[i]);
      }
    }
    else{
      for(int i =amountOfStrings-1;i>=0;i--){
        fprintf(stdout,"%s\n",strings[i] );
        free(strings[i]);
      }
    }

    break;
  }
  free(strings);

}
