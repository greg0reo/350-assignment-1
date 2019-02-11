#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void writeFile(char filename[], char input[]){
	// writes input to a file, used for <-c> and <-o>

	FILE *optr;
	optr = fopen(filename, "w+");
	if(optr){
		fputs(input, optr);
	}else{
		printf("Failed to open o or c file\n");
	}
}

void report(int input[]){



}

int comparer(const void * a, const void * b){
	return ( *(int*)a - *(int*)b );
}

int* sort(int input[], int u, int n, int m, int M){
	//variables corespond with their interface function
	// maybe i, o, c should be part of greater helper function
	//helper function should determine what values to plug into vars

	if(u == 0){
		printf("USAGE: \n");
		printf("prog1sorter [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]\n");
		exit(0);
		// does whatever it does when u is specified
	}else{

	int *sortThis = (int *)malloc(sizeof(int)*n);
	
	int parser = 0;
	int intCounter = 0;
	while(intCounter < n){ // && parser < input){ //parser must be less than input length
						 //perhaps the way to do this is count amount of ints in input AS INPUT IS CONSTRUCTED
	// if number is between m and M, add it to sortThis
	// make sure to only add n ints to sortThis
	// sort sortThis

		if(m <= input[parser] <= M){
//			printf("%d", input[parser]);
//			printf("Make sure all input values are in the specified range\n");
//			exit(0);
			sortThis[intCounter] = input[parser];
			intCounter++;
		}else{
			printf("Make sure all input values are in teh specified range\n");
			exit(0);
		}
		parser++;
	}

	//sortThis now contains all ints that fulfill the requirements
	//it is time to sort the array

	int *pointer;
	pointer = sortThis;
	qsort( pointer,intCounter, sizeof(int), comparer);

	return sortThis;

	//Don't forget to write the report
	//Count runtime
	// ^^ both of these should be handled in the helper function
	// remember to include i, o, c in the greater helper function

	}
}

//int* text2Array(   			IS THIS NECESSARY?

int* greatsort(char i[], char o[], char c[], int u, int n, int m, int M, char username[]){
	clock_t timer;
	timer = clock();
	int input[n];
	int parser = 0;
	if(i == NULL){ // if there is no i specified
		char *line = NULL;
		size_t size;
		if (getline(&line, &size, stdin) == -1){
			printf("No line\n");
		}else{
			printf("%s\n", line);
			input[parser] = atoi(line);
			parser++;
		}
	}else{ 		// open and read the file saved at i
			// record the file's items to input[]
		FILE *iptr;
		char line[8];
//		scanf("%s", i);
		iptr = fopen(i, "r");
		if(iptr == NULL){
			printf("The input file you entered cannot be opened \n");
			exit(0);
		}
		while(fgets(line, 8, iptr)){
			input[parser] = atoi(line);
			parser++;
		}

	}
	// Values should be in input[] right now, submit input into sort and print results

	int *sortedVals = sort(input, u, n, m, M);

	// Time to print the results!
	// if o or c are null, print the results, if not, print to respective files


	if(o == NULL){ // if there is no o specified
		for(int p = 0; p < n; p++){
			printf("%d\n", sortedVals[p]);
			//			printf("what is p? it is %d\n", p);
		}
	}else{		// build string of sorted numbers, then print to file
		char output[n];
		char * temp;
		char newline[] = "\n";
		for(int p = 0; p < n; p++){
			temp[0] = '\0';
			sprintf(temp, "%d", sortedVals[p]);
			//temp = itoa(sortedVals[p], temp, 10);
			strcat(output, temp);
			strcat(output, newline);
		}
		writeFile(o, output);
	}

		// DONT FORGET TO DO REPORT
		// DONT FORGET TO DO TIME





	if(c == NULL){

	
	  for(int nameparser = 0; username[nameparser] != '\0'; nameparser++){
	    printf("%c\t", username[nameparser]);
	    printf("%d\t", username[nameparser]);
	    int counter = 0;
	    for(int numparser = 0; numparser < n; numparser++){
	      if(username[nameparser] == sortedVals[numparser]){
		counter++;
	      }

	    }
	    printf("%d", counter);
	    printf("\n");
	  }

	}
	if(c != NULL){
	  //printf("greg was here");
	  char output2[n];
	  char * temp;
	  char newline[] = "\n";


	  for(int nameparser = 0; username[nameparser] != '\0'; nameparser++){
	    //strcat(output2, user[nameparser]);

	    temp[0] = '\0';
	    sprintf(temp, "%c\t%d\t", username[nameparser], username[nameparser]);
	    strcat(output2, temp);
	    temp[0] = '\0';
	    int counter = 0;
	    for(int numparser = 0; numparser < n; numparser++){
	      if(username[nameparser] == sortedVals[numparser]){
		counter++;
	      }
	    }
	    sprintf(temp, "%d\n", counter);
	    strcat(output2, temp);
	  }
       	    writeFile(c, output2);
	    //	    printf("%s", output2);

	}

	timer = clock() - timer;
	double time_taken = ((double)timer)/CLOCKS_PER_SEC;
	fprintf(stderr, "%f\n" , time_taken);

	return sortedVals;
	
	
}




 int main(int argc, char *argv[], char *envp[]){
  int opt;
  int u = 1;
  int n = 100;
  int m = 1;
  int M = 255;
  char* i = NULL;
  char* o = NULL;
  char* c = NULL;
  while((opt = getopt(argc, argv, "un:m:M:i:o:c:" )) != -1){
    switch(opt){
    case 'u':
      u = 0;
      break;
    case 'n':
      n = atoi(optarg);
      //printf("%d\n\n", &opt);
      break;
    case 'm':
      m = atoi(optarg);
      break;
    case 'M':
      M = atoi(optarg);
      break;
    case 'i':
      i = optarg;
      break;
    case 'o':
      o = optarg;
      break;
    case 'c':
      c = optarg;
      break;
    }
  }

  if(M < m){
    printf("max cannot be less than min\n");
    //    break;
	exit(0);
  }
	if(n < 0){
	printf("You cannot have less than 0 integers\n");
	exit(0);
	}
	
//	printf("AHHHHHHH");
//	printf("%s\n", envp[9]);
//	for(int george = 0; george < 9; george++){
//		printf("%s\n", envp[george]);
//	}

//	printf("\n%s\n", envp[7]+5);
	char* user = getenv("USER");
	
	printf("%s\n", user);
	int* sortedArray;
	//	printf("%c    why no work?\n", c);
	sortedArray =  greatsort(i, o, c, u, n, m, M, user);

	//	printf("%c\n", user[0]);

	//	printf("%sbigdicknick", c);
	/*	if(c == NULL){

	
	  for(int nameparser = 0; user[nameparser] != '\0'; nameparser++){
	    printf("%c\t", user[nameparser]);
	    printf("%d\t", user[nameparser]);
	    int counter = 0;
	    for(int numparser = 0; numparser < n; numparser++){
	      if(user[nameparser] == sortedArray[numparser]){
		counter++;
	      }

	    }
	    printf("%d", counter);
	    printf("\n");
	  }

	}
	if(c != NULL){
	  	    printf("greg was here");
	  char output2[n];
	  char * temp;
	  char newline[] = "\n";


	  for(int nameparser = 0; user[nameparser] != '\0'; nameparser++){
	    //strcat(output2, user[nameparser]);

	    temp[0] = '\0';
	    sprintf(temp, "%c\t%d\t", user[nameparser], user[nameparser]);
	    strcat(output2, temp);
	    temp[0] = '\0';
	    int counter = 0;
	    for(int numparser = 0; numparser < n; numparser++){
	      if(user[nameparser] == sortedArray[numparser]){
		counter++;
	      }
	    }
	    sprintf(temp, "%d\n", counter);
	    strcat(output2, temp);

	    writeFile(c, output2);

	  }



	  /*

	  for(int p = 0; p < n; p++){
	    temp[0] = '\0';
	    sprintf(temp, "%d", sortedVals[p]);
	    //temp = itoa(sortedVals[p], temp, 10);
	    strcat(output2, temp);
	    strcat(output2, newline);
	  }
	  writeFile(o, output);

	  */

	  return 0;

 }
	//	printf("%d\n", sortedArray[3]);
  
  

