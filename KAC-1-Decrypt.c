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

void GetSubSet(char* S_File){

	FILE* f_S = fopen(S_File,"r");

	int i;
	for(i = 1; i <= N; i++){
		fscanf(f_S, "%d", &S[i]);
		// printf("%d\n",S[i]);
	}
}

void ReadK_S(char* K_file){

	FILE* f_K_S = fopen(K_file, "r");

	ReadElFromFile(f_K_S, buffer, SIZE_1);
	element_from_bytes(K_S, buffer);

	fclose(f_K_S);

}

void ReadCText(int i){

	sprintf(buffer,"CText_%d.dat",i);
	FILE* f_CText = fopen(buffer,"r");

	int j;

	ReadElFromFile(f_CText, buffer, SIZE_2);
	
	// for(j = 0; j < SIZE_2; j++){
	// 	printf("%c",buffer[j]);
	// }

	// printf("\n\n********************************************************************\n\n");

	element_from_bytes(CText.c_0, buffer);

	ReadElFromFile(f_CText, buffer, SIZE_2);
	
	// for(j = 0; j < SIZE_2; j++){
	// 	printf("%c",buffer[j]);
	// }

	// printf("\n\n********************************************************************\n\n");

	element_from_bytes(CText.c_1, buffer);

	ReadElFromFile(f_CText, CText.c_2, SIZE_3);
	
	// for(j = 0; j < SIZE_3; j++){
	// 	printf("%c", CText.c_2[j]);
	// }

	// printf("\n\n********************************************************************\n\n");

	fclose(f_CText);
}

void Decrypt(int i, char* msg){

	element_set1(a_S);
	element_set1(b_S);

	int j;

	for(j = 1; j<=N; j++){

		if(S[j] == 1){
			element_mul(b_S, b_S, Y_P[N+1-j]);
			if(j != i){
				element_mul(a_S, a_S, Y_P[N+1-j+i]);
			}
		}

	}

	element_mul(K_S, K_S, a_S);
	pairing_apply(temp1, K_S, CText.c_0, pairing);
	pairing_apply(temp2, b_S, CText.c_1, pairing);
	element_invert(temp2, temp2);
	element_mul(temp1, temp1, temp2);

	element_to_bytes(buffer, temp1);

	for(j = 0; j < SIZE_3; j++){

		msg[j] = (char) (buffer[j]^CText.c_2[j]);
	}

}

int main(int argc, char* argv[]){

	InitializePairing("pbc-0.5.14/param/f.param");
	InitializeVar();
	ReadParams();
	GetSubSet(argv[1]);
	ReadK_S(argv[2]);
	ReadCText((int)(atoi(argv[3])));

	char msg[SIZE_3];
	Decrypt((int)(atoi(argv[3])), msg);

	printf("%s\n", msg);

	return 0;
}