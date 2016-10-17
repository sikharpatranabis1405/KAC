#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "pbc-0.5.14/include/pbc.h"
#include "KAC-1.c"

void ReadParams(){

	FILE* f_Params = fopen("params.dat", "r");

	ReadElFromFile(f_Params, buffer, SIZE_1);
	element_from_bytes(P, buffer);

	ReadElFromFile(f_Params, buffer, SIZE_2);
	element_from_bytes(Q, buffer);

	element_set(Y_P[0], P);
	element_set(Y_Q[0], Q);

	int i;
	for(i = 1; i <= N; i++){

		ReadElFromFile(f_Params, buffer, SIZE_1);
		element_from_bytes(Y_P[i], buffer);
	}

	for(i = N+2; i <= 2*N; i++){

		ReadElFromFile(f_Params, buffer, SIZE_1);
		element_from_bytes(Y_P[i], buffer);
	}

	for(i = 1; i <= N; i++){

		ReadElFromFile(f_Params, buffer, SIZE_2);
		element_from_bytes(Y_Q[i], buffer);
	}

	for(i = N+2; i <= 2*N; i++){

		ReadElFromFile(f_Params, buffer, SIZE_2);
		element_from_bytes(Y_Q[i], buffer);
	}

	fclose(f_Params);

}

void Readmsk(){

	FILE* f_msk = fopen("msk.dat", "r");

	ReadElFromFile(f_msk, buffer, SIZE_1);
	element_from_bytes(msk, buffer);

	fclose(f_msk);

}

void GetSubSet(char* S_File){

	FILE* f_S = fopen(S_File,"r");

	int i;
	for(i = 1; i <= N; i++){
		fscanf(f_S, "%d", &S[i]);
	}
}

void Extract(){

	element_set1(K_S);
	int i;

	for(i = 1; i<=N; i++){

		if(S[i] == 1){
			element_mul(K_S, K_S, Y_P[N+1-i]);
		}
	}

	element_pow_zn(K_S, K_S, msk);

}

void OutPut(){

	FILE* f_K_S = fopen("K_S.dat","w");

	element_to_bytes(buffer, K_S);
	WriteEltoFile(f_K_S, buffer, SIZE_2);

	fclose(f_K_S);
}

int main(int argc, char* argv[]){

	InitializePairing("pbc-0.5.14/param/f.param");
	InitializeVar();
	ReadParams();
	Readmsk();
	GetSubSet(argv[1]);
	Extract();
	OutPut();

	return 0;
}



