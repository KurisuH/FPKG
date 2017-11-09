#include <stdio.h>
#include <afx.h>
#include <math.h>
#include <stdlib.h>

#define Input 2		
#define Hidden 2	
#define Output 1			
#define datanum 100		//Datenanzahl

void main(){
	double sigmoid(double);
	char CString result = "";
	char buffer[200];
	double x_out[Input];		 //InputLayer
	double Hidden_out[Hidden];	 // Hiddenlayer
	double y_out[Output];         // Outputlayer
	double y[Output];				// erwarteter Output
	double w[Input][Hidden];		// Gewichte vom Inputlayer zum Hiddenlayer
	double v[Hidden][Output];			//Gewichte vom Hiddenlayer zum Outputlayer
	
	double deltaw[Input][Hidden];   //delta von input zu hidden
	double deltav[Hidden][Output];	//delta von hidden zu output
	
	double Hidden_delta[Hidden];		// delta vom hidden
	double y_delta[Output];		        // delta output
	double error;
	double errlimit = 0.001;
	double alpha = 0.1, beta = 0.1;
	int loop = 0;
	int times = 50000;
	int i, j, m;
	double max, min;
	double errtemp;
	
	// training set
	struct{
		double input[Input];
		double teach[Output];
	}data[datanum];

	for(m=0; m<datanum; m++){
		for(i=0; i<Input; i++)
			data[m].input[i] = rand()%2;
		for(i=0;i<Output;i++)
			data[m].teach[i] = rand()%2;
	}

	// Initialisiere
	for(i=0; i<Input; i++){
		for(j=0; j<Hidden; j++){
			w[i][j] = ((double)rand()/32767.0)*2-1;
			deltaw[i][j] = 0;
		}
	}
	for(i=0; i<Hidden; i++){
		for(j=0; j<Output; j++){
			v[i][j] = ((double)rand()/32767.0)*2-1;
			deltav[i][j] = 0;
		}
	}

	// Training
	while(loop < times){
		loop++;
		error = 0.0;

		for(m=0; m<datanum ; m++){

			// Backpropagation
			for(i=0; i<Output; i++){
				errtemp = y[i] - y_out[i];
				y_delta[i] = -errtemp * sigmoid(y_out[i]) * (1.0 - sigmoid(y_out[i]));
				error += errtemp * errtemp;
			}

			for(i=0; i<Hidden; i++){
				errtemp = 0.0;
				for(j=0; j<Output; j++)
					errtemp += y_delta[j] * v[i][j];
				Hidden_delta[i] = errtemp * (1.0 + Hidden_out[i]) * (1.0 - Hidden_out[i]);
			}

		}

		// Global error 
		error = error / 2;
		if(loop%1000==0){
			result = "Global Error = ";
			sprintf(buffer, "%f", error);
			result += buffer;
			result += "\r\n";
		}
		if(error < errlimit)
			break;

		printf("The %d th training, error: %f\n", loop, error);
	}

}

// sigmoid Funktion für Aktivierungsfunktion
double sigmoid(double x){
	return(1.0 / (1.0 + exp(-x)));
}
