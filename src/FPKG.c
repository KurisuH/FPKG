#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#include <string.h> /* memset */
#include <unistd.h> /* close */

#define LEARNING_RATE 0.2
#define MAX_ITERATION 2
#define PERCEPTRON_SIZE 785
#define SAMPLE_SIZE 800

#define TEST_VALUE1 0
#define TEST_VALUE2 1

#define INPUT_N
#define HIDDEN_N
#define OUT_N


double sigmoid(double x){
	return(1.0 / (1.0 + exp(-x)));
}
// Random Function to fill perceptron weights.
float randomFloat() {

	// rand() % (max_number + 1 - minimum_number) + minimum_number
	return rand() % (5000 + 1 - 0) + 0;

}

// Is the classifation the same as the guess? If yes no changes, if no do an update.
int evaluate(int guess, int data) {
	if (guess == data) {
		return 1;
	} else {
		return 0;
	}

}

// Activation function. Is the sum of all perceptron*value pair bigger than 0? If yes, the fire. If not then dont.
// Returns 1 for activation and 0 else.
int calculate_output(float *perceptron, int *data, int size) {
	float sum = 0;

	for (int i = 1; i < size; i++) {
		sum += perceptron[i] * data[i] ;
	}

	if (sum >= 0) {
		return 1;
	}

	return 0;

}

// Input a Char CSV and an int Array to be filled. It then extracts the values via strtol and reads them into the values array.
void extract_values(char *data, int *values, int size) {

	char *str = data;
	char *end = str;
	int count = 0;

	// Here we extract int values via strtol and return a clean int array, rather than a char array with breaks.
	while (*end) {
		int n = strtol(str, &end, 10);

		values[count] = n;
		count++;
		//printf("%d\n", n);
		while (*end == ',') {
			end++;
		}
		str = end;

	}
}

int main() {

	// Allocating enough Space for the Char Arrays. Increase if you have lines with more than 6000 Characters
	char test_data[6000] = "";
	char test_data2[6000] = "";
	int value[6000] = { };
	int value2[6000] = { };
	int readval = 0;
	int counter = 0;
	int count = 0;
	int output = 0;

	//Initialize and fill Peceptron with Random Weights.
	float perceptron[PERCEPTRON_SIZE] = { };
	for (int iter = 1; iter < 785; iter++) {
		perceptron[iter] = randomFloat();
	}


	printf("Start Main. \n");

	FILE *file;

	//--------------------------------------//

	// -- This is the important part! -- //
	// Here we start by opening the File and reading the it line by line.

	printf("Start Training Phase.\n");

	// Numbers of Iterations over the training Data.
	for (int i = 0; i < MAX_ITERATION; i++) {

		file = fopen("mnist_train_small.csv", "r");
		printf("\n");

		if (file) {

			// It reads the File Char by Char until the End of File.
			while ((readval = getc(file)) != EOF) {

				// Once a line is completed, we have a finished array and extract the int Values.
				if (readval == '\n') {

					extract_values(test_data, value, PERCEPTRON_SIZE);


//----------------------------Perceptron Learning----------------------------------//


					if (value[0] == TEST_VALUE2 || value[0] == TEST_VALUE1) {





/*
						 for (int i = 200; i < 240; i++) {

						 printf("%i", value[i]);
						 printf("-");

						 }
						 printf("\n");
*/


						output = calculate_output(perceptron, value,
								sizeof(perceptron));

						int evaluation = evaluate(output, value[0]);

						for (int i = 1; i < PERCEPTRON_SIZE; i++) {



							perceptron[i] += LEARNING_RATE * (evaluation - output) * value[i];

						}


						/*

						 for (int i = 200; i < 240; i++) {

						 printf("%f", perceptron[i]);
						 printf("|");

						 }
						 */

						/*
						 printf("\n");
						 printf("Output is: ");
						 printf("%d", output);
						 printf("\n");
						 printf("Expected from Value ");
						 printf("%d", value[0]);
						 printf("\n");
						 printf("\n");
						 */


						// We print the first 100 int values of the line we just read to verify.
						//	printf("Start printing array.\n");

					}

//---------------------------Perceptron Learning End-----------------------------------//


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
		}
	}

	// Finished, maybe think about clearing up Memory to avoid Memory leak?
	printf("\n");
	fclose(file);

//---------------------------Testphase---------------------------------//

	printf("Start Test Phase.\n");
	file = fopen("mnist_test.csv", "r");
	//	printf("\n");
	//  printf("Start reading into array.\n");

	int correct = 0;
	int wrong = 0;
	int total = 0;

	if (file) {

		while ((readval = getc(file)) != EOF) {

			if (readval == '\n') {

				/*
				 for (int i = 0; i < 20; i++) {
				 printf("%c", test_data2[i]);

				 }
				 */

				extract_values(test_data2, value2, PERCEPTRON_SIZE);

				if (value2[0] == TEST_VALUE2 || value2[0] == TEST_VALUE1) {

					output = calculate_output(perceptron, value2,
							sizeof(perceptron));
					int error = evaluate(output, value2[0]);

					if (error == 1) {
						correct++;
					} else {
						wrong++;
					}
					total++;

					/*
					 printf("\n");


					 for (int i = 0; i < 10; i++) {


					 printf("%i", value2[i]);
					 printf(",");

					 }
					 printf("\n");
					 */

				}

				memset(test_data2, 0, sizeof(test_data2));
				memset(value2, 0, sizeof(value2));
				counter = 0;

				// We print the first 100 int values of the line we just read to verify.

			}

			// This is the part where the array is filled while we still haven't encountered a line break. Which is then used above.
			// We copy character by character from the source file into a Char Array. That is the Array which gets turned into an int array by strtol.
			test_data2[counter] = readval;

			//printf("%c",readval);
			//printf("%c",test_data2[counter]);
			counter++;
		}

	}


	//---------------------------Testphase End---------------------------------//

	printf("\n");
	printf("Total: ");
	printf("%d", total);
	printf("\n");
	printf("Correct ");
	printf("%d", correct);
	printf("\n");
	printf("Wrong ");
	printf("%d", wrong);
	printf("\n");
	printf("Percent:  ");

	printf("%g\r", (((double)correct)/total)*100);
	printf("\n");





	printf("Finished, now terminating.\n");

	return 0;
}

