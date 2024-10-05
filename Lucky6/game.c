#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//KREDIT
int randomKredit() {
	int kredit;
	srand(time(NULL));
	kredit = (rand() % (200 - 50 + 1) + 50) * 10;
	return kredit;
}


//UNOS TIKETA
int check_unos(int broj, int odigrani_tiketi[][10], int index_tiketa) {
	int i = index_tiketa;
	for (int j = 0; j < 6; j++) {
		if (broj == odigrani_tiketi[i][j] || (broj < 1 || broj > 48)) {
			return 0;
		}
	}
	return 1;
}
void unos_tiketa(int odigrani_tiketi[10][10], int ulozi[100], int* i, int* kredit, int izvuceni_brojevi[]) {
	int broj;
	int provera_unos;
	printf("---------------------------------------------");
	printf("\nTIKET %d:\n", (*i) + 1);
	printf("--------\n");
	for (int a = (*i); a < (*i)+1; a++) {
		for (int b = 0; b < 6; b++) {
			printf("Unesite %d. broj: ", b+1);
			scanf("%d", &broj);
			int checker = check_unos(broj, odigrani_tiketi, *i);

			if (checker == 1) {
				odigrani_tiketi[*i][b] = broj;
			}
			else {
				printf("GRESKA PRILIKOM UNOSA!\n");
				b--;
			}
		}
		do{
			printf("\nUlog na TIKET %d: ", *i + 1);
			scanf("%d", &provera_unos);
			if (provera_unos < 50) {
				printf("Ulog na jedan tiket mora biti minimalno 50.");
			}
			else {
				ulozi[*i] = provera_unos;
				if (ulozi[*i] > *kredit) {
					printf("Zao nam je, nemate dovoljno kredita.");
				}
				else {
					*kredit = *kredit - ulozi[*i];
					break;
				}
			}
			
		} while (ulozi[*i] > *kredit || provera_unos < 50);
	}
	(*i)++;
}


//PRIKAZ TIKETA
void prikaz_tiketa(int odigrani_tiketi[10][10], int ulozi[100], int i) {
	printf("VASI TIKETI:\n");
	printf("------------\n");
	for (int a = 0; a < i; a++) {
		printf("+----+----+----+----+----+----+\n");
		for (int j = 0; j < 6; j++) {
			printf("|%3d ", odigrani_tiketi[a][j]);
		}
		printf("|");
		printf("\n+----+----+----+----+----+----+   ULOG: %4d\n", ulozi[a]);
	}
}


//IZVLACENJE BROJEVA
int provera_istog_izvlacenje(int broj, int izvuceni_brojevi[]) {
	for (int i = 0; i < 36; i++) {
		if (broj == izvuceni_brojevi[i]) {
			return 0;
		}
	}
	return 1;
}
void izvlacenje_brojeva(int izvuceni_brojevi[]) {
	int broj;
	srand(time(NULL));
	for (int i = 0; i < 36; i++) {
		broj = rand() % 48 + 1;
		int checker = provera_istog_izvlacenje(broj, izvuceni_brojevi);
		if (checker == 1) {
			izvuceni_brojevi[i] = broj;
		}
		else {
			i--;
		}
	}
}
void print_izvucene_brojeve(int izvuceni_brojevi[]) {
	izvlacenje_brojeva(izvuceni_brojevi);
	printf("---------------------------------------------\n");
	printf("\n\t   Brojevi se izvlace...\n\n\t");
	for (int i = 1; i <= 36; i++) {
		Sleep(3000);
		printf("%-5d", izvuceni_brojevi[i - 1]);
		if (i % 6 == 0)printf("\n\t");
	}
	printf("\n---------------------------------------------\n");
}


//PROVERA STATUSA TIKETA
int provera_tiketa(int odigrani_tiketi[][10], int izvuceni_brojevi[100], int i) {

	for (int j = 0; j < 6; j++) {
		int found = 0;
		for (int k = 0; k < 36; k++) {
			if (odigrani_tiketi[i][j] == izvuceni_brojevi[k]) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			return 0;
		}
	}
	return 1;

}
void potraga_za_indexom_zadnjeg_broja(int* index_zadnjeg_broja, int odigrani_tiketi[][10], int izvuceni_brojevi[100], int i) {

	for (int k = 35; k >= 6; k--) {
		for (int j = 0; j < 6; j++) {
			if (izvuceni_brojevi[k] == odigrani_tiketi[i][j]) {
				*index_zadnjeg_broja = k;
				return;
			}
		}
	}
}
void racunanje_dobitka(int index_zadnjeg_broja, int ulozi[100], int i, int* kredit) {
	int dobitak = 0;
	switch (index_zadnjeg_broja) {
	case 5:
		*kredit = 1000000;
		printf("\nJACKPOT!!! Kredit: %d\n", *kredit);
		break;
	case 6:
		*kredit = *kredit + ulozi[i] * 10000;
		dobitak = ulozi[i] * 10000;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 7:
		*kredit = *kredit + ulozi[i] * 7500;
		dobitak = ulozi[i] * 7500;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 8:
		*kredit = *kredit + ulozi[i] * 5000;
		dobitak = ulozi[i] * 5000;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 9:
		*kredit = *kredit + ulozi[i] * 2500;
		dobitak = ulozi[i] * 2500;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 10:
		*kredit = *kredit + ulozi[i] * 1000;
		dobitak = ulozi[i] * 1000;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 11:
		*kredit = *kredit + ulozi[i] * 500;
		dobitak = ulozi[i] * 500;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 12:
		*kredit = *kredit + ulozi[i] * 300;
		dobitak = ulozi[i] * 300;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 13:
		*kredit = *kredit + ulozi[i] * 200;
		dobitak = ulozi[i] * 200;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 14:
		*kredit = *kredit + ulozi[i] * 150;
		dobitak = ulozi[i] * 150;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 15:
		*kredit = *kredit + ulozi[i] * 100;
		dobitak = ulozi[i] * 100;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 16:
		*kredit = *kredit + ulozi[i] * 90;
		dobitak = ulozi[i] * 90;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 17:
		*kredit = *kredit + ulozi[i] * 80;
		dobitak = ulozi[i] * 80;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 18:
		*kredit = *kredit + ulozi[i] * 70;
		dobitak = ulozi[i] * 70;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 19:
		*kredit = *kredit + ulozi[i] * 60;
		dobitak = ulozi[i] * 60;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 20:
		*kredit = *kredit + ulozi[i] * 50;
		dobitak = ulozi[i] * 50;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 21:
		*kredit = *kredit + ulozi[i] * 40;
		dobitak = ulozi[i] * 40;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 22:
		*kredit = *kredit + ulozi[i] * 30;
		dobitak = ulozi[i] * 30;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 23:
		*kredit = *kredit + ulozi[i] * 25;
		dobitak = ulozi[i] * 25;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 24:
		*kredit = *kredit + ulozi[i] * 20;
		dobitak = ulozi[i] * 20;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 25:
		*kredit = *kredit + ulozi[i] * 15;
		dobitak = ulozi[i] * 15;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 26:
		*kredit = *kredit + ulozi[i] * 10;
		dobitak = ulozi[i] * 10;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 27:
		*kredit = *kredit + ulozi[i] * 9;
		dobitak = ulozi[i] * 9;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 28:
		*kredit = *kredit + ulozi[i] * 8;
		dobitak = ulozi[i] * 8;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 29:
		*kredit = *kredit + ulozi[i] * 7;
		dobitak = ulozi[i] * 7;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 30:
		*kredit = *kredit + ulozi[i] * 6;
		dobitak = ulozi[i] * 6;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 31:
		*kredit = *kredit + ulozi[i] * 5;
		dobitak = ulozi[i] * 5;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 32:
		*kredit = *kredit + ulozi[i] * 4;
		dobitak = ulozi[i] * 4;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 33:
		*kredit = *kredit + ulozi[i] * 3;
		dobitak = ulozi[i] * 3;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 34:
		*kredit = *kredit + ulozi[i] * 2;
		dobitak = ulozi[i] * 2;
		printf("Dobitak: %d\n", dobitak);
		break;
	case 35:
		*kredit = *kredit + ulozi[i] * 1;
		dobitak = ulozi[i] * 1;
		printf("Dobitak: %d\n", dobitak);
		break;
	}

}
void ispis_statusa_tiketa(int odigrani_tiketi[][10], int izvuceni_brojevi[100], int ulozi[100], int broj_tiketa, int* kredit) {
	int index_tiketa;
	int index_zadnjeg_broja = 35;

	printf("STATUSI TIKETA:\n");
	printf("---------------\n");
	for (int i = 0; i < broj_tiketa; i++) {
		index_tiketa = i;
		int check_ticket = provera_tiketa(odigrani_tiketi, izvuceni_brojevi, index_tiketa);
		if (check_ticket == 1) {
			printf("+----+----+----+----+----+----+\n");
			for (int j = 0; j < 6; j++) {
				printf("|%3d ", odigrani_tiketi[i][j]);
			}
			printf("|");
			printf("\n+----+----+----+----+----+----+      DOBITAN\n");

			potraga_za_indexom_zadnjeg_broja(&index_zadnjeg_broja, odigrani_tiketi, izvuceni_brojevi, index_tiketa);

			//printf("\nINDEX ZADNJEG BROJA JE %d\n\n", index_zadnjeg_broja);

			racunanje_dobitka(index_zadnjeg_broja, ulozi, index_tiketa, kredit);

		}
		else {
			printf("+----+----+----+----+----+----+\n");
			for (int j = 0; j < 6; j++) {
				printf("|%3d ", odigrani_tiketi[i][j]);
			}
			printf("|");
			printf("\n+----+----+----+----+----+----+      GUBITAN\n");
		}
	}
}


//RESET SKUPOVA
void vrati_tiket_na_prazan(int odigrani_tiketi[][10], int* i, int ulozi[]) {
	for (int a = 0; a < *i; a++) {
		for (int b = 0; b < 6; b++) {
			odigrani_tiketi[a][b] = 0;
			ulozi[a] = 0;
		}
	}
	*i = 0;
}
void reset_izvuceni_brojevi(int izvuceni_brojevi[]) {
	for (int i = 0; i < 36; i++) {
		izvuceni_brojevi[i] = 0;
	}
}


//MENI
void menu() {

	//PROMENLJIVE
	int i = 0;
	int odigrani_tiketi[10][10];
	int ulozi[100];
	int kredit = randomKredit();
	int izvuceni_brojevi[100];

	//SADRZAJ MENIJA
	int izbor;
	do{
		//system("cls");
		printf("---------------------------------------------\n");
		printf("\t\tLUCKY SIX\tKREDIT: %4d\n\n", kredit);
		printf("1. Odigraj tiket\n");
		printf("0. Zapocni igru\n");
		do{
			printf("\n> ");
			scanf("%d", &izbor);
			if (izbor != 1 && izbor != 0) {
				printf("Pogresan unos!\n");
			}
		} while (izbor != 1 && izbor != 0);

		//SLUCAJEVI
		switch (izbor) {
		case 1:
			if (kredit == 0) {
				printf("\nNemate dovoljno kredita da nastavite igru.\n\n");
				Sleep(3000);
				system("cls");
				if (i != 0) {
					prikaz_tiketa(odigrani_tiketi, ulozi, i);
				}
				break;
			}
			system("cls");
			if (i != 0) {
				prikaz_tiketa(odigrani_tiketi, ulozi, i);
			}
			printf("---------------------------------------------\n");
			printf("\t\tLUCKY SIX\tKREDIT: %4d\n\n", kredit);
			unos_tiketa(odigrani_tiketi, ulozi, &i, &kredit, izvuceni_brojevi);
			printf("\nVas tiket se ucitava...");
			Sleep(2000);
			system("cls");
			prikaz_tiketa(odigrani_tiketi, ulozi, i);
			break;
		case 0:
			Sleep(1500);
			system("cls");
			printf("\n\n\t   IGRA USKORO POCINJE...");
			Sleep(3000);
			system("cls");
			if (i != 0) {
				prikaz_tiketa(odigrani_tiketi, ulozi, i);
			}
			Sleep(3000);

			//izvlacenje brojeva
			print_izvucene_brojeve(izvuceni_brojevi);
			Sleep(3000);
			//provera statusa tiketa
			if (i != 0) {
				ispis_statusa_tiketa(odigrani_tiketi, izvuceni_brojevi, ulozi, i, &kredit);
			}
			printf("\nPritisnite ENTER da nastavite:");
			getchar();
			getchar();
			//Sleep(3000);
			system("cls");

			//vracanje tiketa, uloga i izvucenih brojeva na nulu
			vrati_tiket_na_prazan(odigrani_tiketi, &i, ulozi);
			reset_izvuceni_brojevi(izvuceni_brojevi);

			break;
		}

	} while (kredit >= 0);
}


int main(void) {

	menu();

	return 0;
}