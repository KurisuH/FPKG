#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#include <string.h> /* memset */
#include <unistd.h> /* close */

#define LEARNING_RATE 0.1
#define MAX_ITERATION 100
#define NUM_INSTANCES = 100

float randomFloat()
{
	// rand() % (max_number + 1 - minimum_number) + minimum_number

	return rand() % (500 + 1 - 5) + 5;
}



/*
 * public domain strtok_r() by Charlie Gordon
 *
 *   from comp.lang.c  9/14/2007
 *
 *      http://groups.google.com/group/comp.lang.c/msg/2ab1ecbb86646684
 *
 *     (Declaration that it's public domain):
 *      http://groups.google.com/group/comp.lang.c/msg/7c7b39328fefab9c
 */



int array(int num1, int num2) {

   /* local variable declaration */
   int result;

   if (num1 > num2)
      result = num1;
   else
      result = num2;

   return result;
}




int main() {






     char test_data[6000] = "";
	  int value[6000]  ={};
	  int readval = 0;
	  int counter = 0;
	  int count = 0;
	  char temparr[6000] = "";
	  double perceptron [784] = {};

	for (int iter = 0; iter < 784; iter++)
	{
		perceptron[iter] = randomFloat();
	}


	printf("Start Main. \n");


	  FILE *file;
	  file = fopen("test.csv", "r");
	  int sizex = 0;
	  int sizey = 0;
	  char lb;
	  lb = getc(file);



 while ( lb !='\n') {

	if(lb ==',') {sizex++;}
	  lb = getc(file);}
	  sizey++;

	  while ((lb = getc(file)) != EOF)
	  {
		  if( lb == '\n')
			  sizey++;
	  }


	// printf("%d", sizex);
	 // printf("\n");
	 // printf("%d", sizey);
	 // printf("\n");

	  fclose(file);





  file = fopen("test.csv", "r");







  printf("\n");
  printf("Start reading into array.\n");

  if (file) {
      while ((readval = getc(file)) != EOF){



    	  if (readval == '\n'){

/*
        	   for (int i = 0; i < sizeof(test_data); i++) {
        	      temparr[i] = test_data[i];
        	   }

*/



//s
        		char *str = test_data;
        		char *end = str;

        		count = 0;
        		while(*end) {
        			int n = strtol(str, &end, 10);

        			value[count] = n;
        			count++;
        			//printf("%d\n", n);
        			while (*end == ',') {
        				end++;
        			}
        			str = end;


        		}







        		printf("Learn.\n");




        		for(int i = 1; i < sizeof(perceptron); i++)
        		{
        		//	perceptron[i] += LEARNING_RATE * localError * [p];

        		}









       	 	 printf("Start printing array.\n");

       	       for ( int i = 0; i < 100 ; i++ ) {

       	     	  printf("%i", value[i]);
       	     	  printf("-");
       	       }

       	    printf("Reset.\n");
       	    printf("\n");

           	   memset(test_data, 0, sizeof(test_data));
           	   memset(value, 0, sizeof(value));
       	       counter = 0;
   		  }


    	  test_data[counter] = readval;
    	  counter++;

    	  }









      printf("\n");
	  fclose(file);

	  printf("Finished, now terminating.\n");

      return 0;
}
}



