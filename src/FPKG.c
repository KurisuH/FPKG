#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#include <string.h> /* memset */
#include <unistd.h> /* close */

#define LEARNING_RATE 0.2
#define MAX_ITERATION 100
#define NUM_INSTANCES = 100


// Random Function to fill perceptron weights.

float randomFloat() {

	// rand() % (max_number + 1 - minimum_number) + minimum_number
	return rand() % (500 + 1 - 5) + 5;
}


// Is the classifation the same as the guess? If yes no changes, if no do an update.
int evaluate (int guess, int data)
{
	if (guess == data)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


int calculate_output(float *perceptron, int *data, int size )
{
	float sum = 0;

	for (int i = 1; i < size; i++) {
		sum += perceptron[i] * data[i];
	}

	if (sum >= 0){ return 1;}

	return 0;

}

int main() {

	// Allocating enough Space for the Char Arrays. Increase if you have lines with more than 6000 Characters
	char test_data[6000] = "";
	int value[6000] = { };
	int readval = 0;
	int counter = 0;
	int count = 0;
	int output = 0;


	//Initialize and fill Peceptron with Random Weights.
	float perceptron[785] = { };
	for (int iter = 1; iter < 785; iter++) {
		perceptron[iter] = randomFloat();
	}

	printf("Start Main. \n");


	// Originally this Part would read the CSV file and analyse the amount and length of Lines as Y and X respectively. This Info is not used so far as Dynamic memory allocation
	// turned out to be rather difficult in C.
	FILE *file;


	//--------------------------------------//

	// -- This is the important part! -- //
	// Here we start by opening the File and reading the it line by line.
	file = fopen("mnist_train_small.csv", "r");
	printf("\n");
	printf("Start reading into array.\n");

	if (file) {

		// It reads the File Char by Char until the End of File.
		while ((readval = getc(file)) != EOF) {

			// Once a line is completed, we have a finished array and extract the int Values.
			if (readval == '\n') {


				char *str = test_data;
				char *end = str;
				count = 0;

				// Here we extract int values via strtol and return a clean int array, rather than a char array with breaks.
				while (*end) {
					int n = strtol(str, &end, 10);

					value[count] = n;
					count++;
					//printf("%d\n", n);
					while (*end == ',') {
						end++;
					}
					str = end;

				}


//--------------------------------------------------------------//

//Implementation of Perceptron.


				if (value[0] == 1 || value[0] == 0 ){
				printf("Learn.\n");


				for (int i = 100; i < 400; i++) {

					printf("%i", value[i]);
					printf("-");
				}

				output = calculate_output(perceptron,value,sizeof(perceptron));

				int error = evaluate(output, value[0]);


				for (int i = 1; i < 785; i++) {

				perceptron[i] += LEARNING_RATE * (error - output) * value[i];



				}


				printf("\n");
				printf("Output is: ");
				printf("%d", output);
				printf("\n");
				printf("Expected from Value ");
				printf("%d", value[0]);
				printf("\n");
				printf("\n");

				// We print the first 100 int values of the line we just read to verify.
				printf("Start printing array.\n");




				}
//--------------------------------------------------------------//


				// Reset the Arrays so that we can fill them again. This method uses as little as possible Memory.
				memset(test_data, 0, sizeof(test_data));
				memset(value, 0, sizeof(value));
				counter = 0;
			}


			// This is the part where the array is filled while we still haven't encountered a line break. Which is then used above.
			// We copy character by character from the source file into a Char Array. That is the Array which gets turned into an int array by strtol.
			test_data[counter] = readval;
			counter++;

		}


		// Finished, maybe think about clearing up Memory to avoid Memory leak?
		printf("\n");
		fclose(file);

		printf("Finished, now terminating.\n");

		return 0;
	}
}

