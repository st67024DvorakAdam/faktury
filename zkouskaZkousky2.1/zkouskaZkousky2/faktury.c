#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "faktury.h"

enum mesicEnum dejMesic(char* datum) {
	char mesic[2];
	mesic[0] = datum[3];
	mesic[1] = datum[4];
	printf("%s", mesic);

	switch (mesic[0]) {
	case '0':
		switch (mesic[1]) {
		case '1':
			return leden;
		case '2':
			return unor;
		case '3':
			return brezen;
		case '4':
			return duben;
		case '5':
			return kveten;
		case '6':
			return cerven;
		case '7':
			return cervenec;
		case '8':
			return srpen;
		case '9':
			return zari;
		}
		break;
	case '1':
		switch (mesic[1]) {
		case '0':
			return rijen;
		case '1':
			return listopad;
		case '2':
			return prosinec;
		}
		break;
	}

}

tFakturaList* nactiFaktury(char* jmSoub, enum fakturaEnum typFaktury, enum mesicEnum mesic) {
	FILE* file = fopen(jmSoub, "r");
	if (file == NULL) {
		printf("nepodarilo se otevrit soubor.\n");
		exit(1);
	}

	char typHledaneFaktury;
	if (typFaktury == prijata) {
		typHledaneFaktury = 'P';
	}
	else {
		typHledaneFaktury = 'V';
	}

	char line[1024];
	if (fgets(line, 1024, file) == NULL) { //nacteni hlavicky
		printf("chyba cteni hlavicky");
		exit(1);
	}

	tFakturaList* head = NULL;
	tFakturaList* current = NULL;

	while (fgets(line, 1024, file) != NULL) {
		tFakturaList* element = (tFakturaList*)malloc(sizeof(tFakturaList));
		element->faktura = (tFaktura*)malloc(sizeof(tFaktura));

		char* token = strtok(line, ";");
		strcpy(((tFaktura*)element->faktura)->faktura, token);

		token = strtok(NULL, ";");
		strcpy(((tFaktura*)element->faktura)->datum, token);

		token = strtok(NULL, ";");
		((tFaktura*)element->faktura)->castka = (int)strtol(token, NULL, 10);

		token = strtok(NULL, ";");
		char znak = (char)(token[0]);
		((tFaktura*)element->faktura)->typ = znak;
		element->dalsi = NULL;

		//zde má být podmínka
		if (head == NULL) {
			head = (tFakturaList*)malloc(sizeof(tFakturaList));
			head = element;
		}
		else {
			current = head;
			while (current->dalsi != NULL) {
				current = current->dalsi;
			}
			current->dalsi = (tFakturaList*)malloc(sizeof(tFakturaList));
			current->dalsi = element;
		}
	

	//zde má konèit tìlo podmínky}
	}
	
		return head;

}

void vypisFaktury(tFakturaList* fakturaList) {
	tFakturaList* current = fakturaList;

	while (current != NULL) {
		printf("Datum: %s\n", current->faktura->datum);
		printf("Typ: %c\n", current->faktura->typ);
		printf("Faktura: %s\n", current->faktura->faktura);
		printf("Castka: %d\n", current->faktura->castka);
		printf("---------------------\n");

		current = current->dalsi;
	}
}

