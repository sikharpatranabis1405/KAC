#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "pbc-0.5.14/include/pbc.h"
#include "KAC-1.c"

void SetUp(){

	element_random(P);
	element_random(Q);

	element_random(alpha);

	int i;
	
	element_set(Y_P[0], P);
	element_set(Y_Q[0], Q);

	for(i = 1; i <= 2*N; i++){

		element_pow_zn(Y_P[i], Y_P[i-1], alpha);
		element_pow_zn(Y_Q[i], Y_Q[i-1], alpha);
	}

	

}

void OutPut(){

	FILE* f_Params = fopen("params.dat", "w");	
	int i;

	element_to_bytes(buffer, Y_P[0]);
	WriteEltoFile(f_Params, buffer, SIZE_1);

	element_to_bytes(buffer, Y_Q[0]);
	WriteEltoFile(f_Params, buffer, SIZE_2);


	for(i = 1; i <= N; i++){

		element_to_bytes(buffer, Y_P[i]);
		WriteEltoFile(f_Params, buffer, SIZE_1);
	}

	for(i = N+2; i <= 2*N; i++){

		element_to_bytes(buffer, Y_P[i]);
		WriteEltoFile(f_Params, buffer, SIZE_1);
	}

	for(i = 1; i <= N; i++){

		element_to_bytes(buffer, Y_Q[i]);
		WriteEltoFile(f_Params, buffer, SIZE_2);
	}

	for(i = N+2; i <= 2*N; i++){

		element_to_bytes(buffer, Y_Q[i]);
		WriteEltoFile(f_Params, buffer, SIZE_2);
	}

	fclose(f_Params);

}

int main(){

	InitializePairing("pbc-0.5.14/param/f.param");
	InitializeVar();
	SetUp();
	OutPut();
	return 0;
}

