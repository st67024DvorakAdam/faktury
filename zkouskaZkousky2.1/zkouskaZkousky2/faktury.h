#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct faktura{
	char datum[20];
	char typ; //P/V
	char faktura[20];
	int castka;
}tFaktura;

enum fakturaEnum {
	vydana='V',
	prijata='P'
};

enum mesicEnum {
	leden=1,unor,brezen,duben,kveten,cerven,cervenec,srpen,zari,rijen,listopad,prosinec
};

typedef struct fakturaList {
	tFaktura* faktura;
	struct fakturaList* dalsi;
}tFakturaList;

tFakturaList* nactiFaktury(char* jmSoub, enum fakturaEnum typFaktury, enum mesicEnum mesic);

void vypisFaktury(tFakturaList* fakturaList);

//enum mesicEnum dejMesic(char* datum);