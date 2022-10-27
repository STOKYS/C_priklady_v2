#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define VSTUP "../slalom/slalom.txt"
#define VYSTUP "vysledkova_listina.txt"
#define VELIKOST 100
#define ODDELOVACE " /n"

typedef struct {
    int start_c;
    char jmeno[30];
    char prijmeni[30];
    float cas_one;
    float cas_two;
} SLALOMAR;

float string_na_float(char cas[20]) {
    char *token;
    int sloupec = 0;
    float final = 0;
    for (int i = 0; i < 2; i++) {
        sloupec = 1;
        token = strtok(cas, ":");
        while (token != NULL) {
            switch (sloupec) {
                case 1:
                    printf("%f\n", final);
                    final = atof(token) * 60;
                    printf("%f\n", final);
                    break;
                case 2:
                    printf("%f\n", final);
                    final += atof(token);
                    printf("%f\n", final);
                    break;
            }
            token = strtok(NULL, ":");
            sloupec++;
        }
    }
    printf("%f\n\n", final);
    return final;
}

int nactiSoubor(SLALOMAR *pole) {
    int pocet = 0;
    char *pch;
    int sloupec;
    char buffer[VELIKOST];
    FILE *soubor = fopen(VSTUP, "r");
    if (soubor == NULL) {
        printf("Nastala chyba pri otevirani souboru %s", VSTUP);
        return EXIT_FAILURE;
    } else {
        while (fgets(buffer, VELIKOST, soubor) != NULL) {
            if (pocet > 0) {
                sloupec = 1;
                pch = strtok(buffer, "\n ");
                while (pch != NULL) {
                    switch (sloupec) {
                        case 1:
                            pole[pocet - 1].start_c = atoi(pch);
                            break;
                        case 2:
                            strcpy(pole[pocet - 1].jmeno, pch);
                            break;
                        case 3:
                            strcpy(pole[pocet - 1].prijmeni, pch);
                            break;
                        case 4:
//                            strcpy(pole[pocet - 1].cas_one, pch);
                            pole[pocet - 1].cas_one = string_na_float(pch);
                            break;
                        case 5:
                            pole[pocet - 1].cas_two = string_na_float(pch);
                            break;
                    }
                    pch = strtok(NULL, "\n ");
                    sloupec++;
                }
            }
            pocet++;
        }
        pocet--;
        if (fclose(soubor) == EOF) {
            printf("Soubor %s se nepodarilo uzavrit.\n", VSTUP);
        }
    }
    return pocet;
}

void vypisSouboru(SLALOMAR *pole, int pocet) {
    for (int i = 0; i < pocet; i++) {
        printf("%d %s %s %f %f \n", pole[i].start_c, pole[i].jmeno, pole[i].prijmeni,
               pole[i].cas_one, pole[i].cas_two);
    }
}

int main() {
    SLALOMAR slalomari[100];
    int pocetVysledku = nactiSoubor(slalomari);
    vypisSouboru(slalomari, pocetVysledku);
    return 0;
}