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

	int i;
	for(i = 1; i <= N; i++){

		ReadElFromFile(f_Params, buffer, SIZE_1);
		element_from_bytes(Y_P[i], buffer);
	}

	for(i = 1; i <= N; i++){

		ReadElFromFile(f_Params, buffer, SIZE_2);
		element_from_bytes(Y_Q[i], buffer);
	}

	fclose(f_Params);

}

void ReadPK(){

	FILE* f_PK = fopen("PK.dat", "r");

	ReadElFromFile(f_PK, buffer, SIZE_1);
	element_from_bytes(PK.PK_1, buffer);

	ReadElFromFile(f_PK, buffer, SIZE_2);
	element_from_bytes(PK.PK_2, buffer);
	
	fclose(f_PK);

}

void Encrypt(int i, char* msg, int len){

	element_random(temp);

	element_pow_zn(CText.c_0, Q, temp);

	element_mul(CText.c_1, PK.PK_2, Y_Q[i]);
	element_pow_zn(CText.c_1, CText.c_1, temp);

	pairing_apply(CText.c_2_temp, Y_P[N], Y_Q[1], pairing);
	element_pow_zn(CText.c_2_temp, CText.c_2_temp, temp);

	element_to_bytes(buffer, CText.c_2_temp);
	int j;
	for(j = 0; j < SIZE_3; j++){

		CText.c_2[j] = (char) (buffer[j]^msg[j]);
	}


}

void Output(int i){

	sprintf(buffer,"CText_%d.dat",i);
	FILE* f_CText = fopen(buffer,"w");

	element_to_bytes(buffer, CText.c_0);
	WriteEltoFile(f_CText, buffer, SIZE_2);

	element_to_bytes(buffer, CText.c_1);
	WriteEltoFile(f_CText, buffer, SIZE_2);

	WriteEltoFile(f_CText, CText.c_2, SIZE_3);

	fclose(f_CText);
}

int main(int argc, char* argv[]){

	InitializePairing("pbc-0.5.14/param/f.param");
	InitializeVar();

	ReadParams();
	ReadPK();
	Encrypt((int)(atoi(argv[1])), argv[2], strlen(argv[2]));
	Output((int)(atoi(argv[1])));

	return 0;
}
