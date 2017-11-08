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


// Random Function to fill perceptron weights.

float randomFloat() {

	// rand() % (max_number + 1 - minimum_number) + minimum_number
	return rand() % (500 + 1 - 5) + 5;
}

/*
 * So far just put a CSV file titled "test.csv" in the same folder and this Program will read line for line and print in console.
 * TODO: Implement Perceptron
 */

int main() {

	// Allocating enough Space for the Char Arrays. Increase if you have lines with more than 6000 Characters
	char test_data[6000] = "";
	int value[6000] = { };
	int readval = 0;
	int counter = 0;
	int count = 0;


	//Initialize and fill Peceptron with Random Weights.
	double perceptron[784] = { };
	for (int iter = 0; iter < 784; iter++) {
		perceptron[iter] = randomFloat();
	}

	printf("Start Main. \n");


	// Originally this Part would read the CSV file and analyse the amount and length of Lines as Y and X respectively. This Info is not used so far as Dynamic memory allocation
	// turned out to be rather difficult in C.
	FILE *file;
	file = fopen("test.csv", "r");
	int sizex = 0;
	int sizey = 0;
	char lb;
	lb = getc(file);

	while (lb != '\n') {

		if (lb == ',') {
			sizex++;
		}
		lb = getc(file);
	}
	sizey++;

	while ((lb = getc(file)) != EOF) {
		if (lb == '\n')
			sizey++;
	}

	// printf("%d", sizex);
	// printf("\n");
	// printf("%d", sizey);
	// printf("\n");

	fclose(file);


	//--------------------------------------//

	// -- This is the important part! -- //
	// Here we start by opening the File and reading the it line by line.
	file = fopen("test.csv", "r");
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

//TODO: Here let the Perceptron work with the 785 int array of values.

				printf("Learn.\n");

				for (int i = 1; i < sizeof(perceptron); i++) {

					//	perceptron[i] += LEARNING_RATE * localError * [p];

				}
//--------------------------------------------------------------//


				// We print the first 100 int values of the line we just read to verify.
				printf("Start printing array.\n");

				for (int i = 0; i < 100; i++) {

					printf("%i", value[i]);
					printf("-");
				}

				printf("Reset.\n");
				printf("\n");

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

