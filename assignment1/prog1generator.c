#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void generate(int u, int n, int m, int M, int s, char o[]){
	clock_t timer;
	timer = clock();
  if(u == 0){
    // does whatever u does here
	printf("USAGE: \n");
	printf("prog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]");
	exit(0);
  }else{
    srand(s);
    if(o == NULL){
      for(int parser=0; parser < n; parser++){
	printf("%d\n", (m + (rand()%(M-m))));
      }
    }else{
      FILE *optr;
      optr = fopen(o, "w+");
      if(optr){
	char value[7];
	int integer;
	for(int parser=0; parser < n; parser++){
	  char value[] = "\n";
	  integer = (m + (rand()%(M-m)));
		sprintf(value, "%d", integer);
//	  itoa(integer, value, 10);
	  fputs(value, optr);
	  //	printf("%s\n", value);
	  fputs("\n", optr);
	}
      }else{
	  printf("Failed to open output file\n");
      }
    }
  }
	timer = clock() - timer;
	double time_taken = ((double)timer)/CLOCKS_PER_SEC;
	fprintf(stderr, "%f\n", time_taken);
//	return 0;
  
}


int main(int argc, char *argv[]){
	int opt;
	int u = 1;
	int n = 100;
	int m = 1;
	int M = 255;

	struct timeval greg;
	gettimeofday(&greg, NULL);
	int s = greg.tv_sec;
	char* o = NULL;
	while((opt = getopt(argc, argv, "un:m:M:s:o:" )) != -1){
		switch(opt){
		case 'u':
			u=0;
			break;
		case 'n':
			n=atoi(optarg);
			break;
		case 'm':
			m=atoi(optarg);
			break;
		case 'M':
			M = atoi(optarg);
			break;
		case 's':
			s = atoi(optarg);
			break;
		case 'o':
			o = optarg;
			break;
		}

	}

	if(M < m){
		printf("Max cannot be less than min\n");
		exit(0);
	}
	if( n < 0){
		printf("You cannot have less than 0 integers\n");
		exit(0);
	}

	generate(u, n, m, M, s, o);
	return 0;

}
