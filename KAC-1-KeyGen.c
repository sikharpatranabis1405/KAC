#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "pbc-0.5.14/include/pbc.h"
#include "KAC-1.c"

void ReadPQ(){

	FILE* f_Params = fopen("params.dat", "r");

	ReadElFromFile(f_Params, buffer, SIZE_1);
	element_from_bytes(P, buffer);

	ReadElFromFile(f_Params, buffer, SIZE_2);
	element_from_bytes(Q, buffer);

	fclose(f_Params);

}

void KeyGen(char* ownerID, int len){

	element_from_hash(msk, ownerID, len);
	element_pow_zn(PK.PK_1, P, msk);
	element_pow_zn(PK.PK_2, Q, msk);
}

void OutPut(){

	FILE* f_msk = fopen("msk.dat","w");
	FILE* f_PK = fopen("PK.dat","w");

	element_to_bytes(buffer, msk);
	WriteEltoFile(f_msk, buffer, SIZE_1);

	element_to_bytes(buffer, PK.PK_1);
	WriteEltoFile(f_PK, buffer, SIZE_1);

	element_to_bytes(buffer, PK.PK_2);
	WriteEltoFile(f_PK, buffer, SIZE_2);

	fclose(f_msk);
	fclose(f_PK);	
}

int main(int argc, char* argv[]){

	InitializePairing("pbc-0.5.14/param/f.param");
	InitializeVar();
	ReadPQ();
	KeyGen(argv[1], (int) strlen(argv[1]));
	OutPut();
	return 0;
}