#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "pbc-0.5.14/include/pbc.h"

#define N 100
#define SIZE_1 40
#define SIZE_2 80
#define SIZE_3 240



pairing_t pairing;
char param[1024];

unsigned char buffer[SIZE_3];


element_t P;
element_t Q;

typedef struct{

	element_t PK_1;
	element_t PK_2;
}public_key;

public_key PK;

element_t msk;

typedef struct{

	element_t c_0;
	element_t c_1;
	element_t c_2_temp;
	char c_2[SIZE_3];
}CT;

CT CText;

int S[N];

element_t K_S;

element_t alpha;
element_t Y_P[N+1];
element_t Y_Q[N+1];

element_t M;
element_t temp;


void InitializePairing(char* paramFile){

	FILE* stream = fopen(paramFile, "r");
	size_t count = fread(param, 1, 1024, stream);
	if(!count){
		printf("Input Error!!\n");
	}
	pairing_init_set_buf(pairing, param, count);
}

void InitializeVar(){

	element_init_G1(P, pairing);	
	element_init_G2(Q, pairing);

	element_init_Zr(msk, pairing);
	element_init_G1(PK.PK_1, pairing);
	element_init_G2(PK.PK_2, pairing);

	element_init_G2(CText.c_0, pairing);
	element_init_G2(CText.c_1, pairing);
	element_init_GT(CText.c_2_temp, pairing);

	element_init_G1(K_S, pairing);

	element_init_Zr(alpha, pairing);

	int i;
	for(i = 0; i <= N; i++){

		element_init_G1(Y_P[i], pairing);
		element_init_G2(Y_Q[i], pairing);
	}

	element_init_GT(M, pairing);
	element_init_Zr(temp, pairing);

		
}

void WriteEltoFile(FILE* f_ptr, char* buffer, int size){

	int i;
	for(i = 0; i < size; i++){

		fprintf(f_ptr, "%c", buffer[i]);
	}	

}

void ReadElFromFile(FILE* f_ptr, char* buffer, int size){

	int i;
	char temp;
	for(i = 0; i < size; i++){

		fscanf(f_ptr, "%c", &temp);
		buffer[i] = temp;
	}	
}











