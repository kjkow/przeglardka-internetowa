#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pobieranie_stron.h"
#include "obsluga_html.h"
#include "wspolne.h"

void poprosOLink();
void zapytajCzySkorzystacZNawigacji();
void obslugaUzyciaNawigacji();
void wyswietlStrone();
void wyswietlMenuPowitalne();

char* zawartoscStrony;
char* linkiStrony;
char* linkPodanyPrzezUzytkownika;
char odpUzytkownika;
char* linkWybranyZNawigacji;

int UZYCIE_NAWIGACJI;
int ZAKONCZ;



int main(){
    system("chcp 1250");
    char* komunikatNiepoprawnejWalidacji = malloc((100 * sizeof(char))+1);
    strcpy(komunikatNiepoprawnejWalidacji, "\nB³¹d walidacji! Wprowadzi³eœ niepoprawn¹ wartoœæ.\n");
    wyswietlMenuPowitalne();
    while(1){
        if(BLAD_WALIDACJI == 0) system("@cls||clear");
        BLAD_WALIDACJI = 0;
        UZYCIE_NAWIGACJI = 0;

        if(linkWybranyZNawigacji == NULL){
            poprosOLink();
            if(BLAD_WALIDACJI == 1){
                printf("%s", komunikatNiepoprawnejWalidacji);
                continue;
            }
            if(ZAKONCZ == 1) break;

            wyswietlStrone();
            if(BLAD_WALIDACJI == 1){
                printf("%s", komunikatNiepoprawnejWalidacji);
                continue;
            }

            zapytajCzySkorzystacZNawigacji();
            if(BLAD_WALIDACJI == 1){
                printf("%s", komunikatNiepoprawnejWalidacji);
                continue;
            }

            if(UZYCIE_NAWIGACJI == 1){
                obslugaUzyciaNawigacji();
                if(BLAD_WALIDACJI == 1){
                    printf("%s", komunikatNiepoprawnejWalidacji);
                    continue;
                }
            }
        }else{
            strcpy(linkPodanyPrzezUzytkownika, linkWybranyZNawigacji);

            wyswietlStrone();
            if(BLAD_WALIDACJI == 1){
                linkWybranyZNawigacji = NULL;
                printf("%s", komunikatNiepoprawnejWalidacji);
                continue;
            }

            zapytajCzySkorzystacZNawigacji();
            if(BLAD_WALIDACJI == 1){
                printf("%s", komunikatNiepoprawnejWalidacji);
                continue;
            }

            if(UZYCIE_NAWIGACJI == 1){
                obslugaUzyciaNawigacji();
                if(BLAD_WALIDACJI == 1){
                    printf("%s", komunikatNiepoprawnejWalidacji);
                    continue;
                }
            }
        }

    }
    free(zawartoscStrony);
    free(linkiStrony);
    free(linkPodanyPrzezUzytkownika);
    free(linkWybranyZNawigacji);
    return 0;
}

void wyswietlMenuPowitalne(){
    printf("%s\n%s\n\n", "---WITAJ---", "Aplikacja: \"Prosta przegl¹darka internetowa\"");
}

void obslugaUzyciaNawigacji(){
    linkWybranyZNawigacji = malloc(MAX_ROZMIAR_LINKU);
    printf("\n\n%s\n\n", "Nawigacja:");
    char listaLinkow[liczbaLinkow][MAX_ROZMIAR_LINKU];
    przepiszLinkiDoListyLinkow(listaLinkow, linkiStrony);
    int i;
    for(i=0; i<liczbaLinkow; i++){
        printf("%d. %s\n", i+1, listaLinkow[i]);
    }
    int numerLinku;
    printf("\n%s\n>>", "Podaj numer linku:");
    scanf(" %d", &numerLinku);
    strcpy(linkWybranyZNawigacji, listaLinkow[numerLinku-1]);
    if(numerLinku < 1 || numerLinku > liczbaLinkow){
        BLAD_WALIDACJI = 1;
        free(linkWybranyZNawigacji);
        linkWybranyZNawigacji = NULL;
    }else if(strstr(linkWybranyZNawigacji, "http") == NULL){
        char* tmp = malloc(strlen(linkPodanyPrzezUzytkownika) + strlen(linkWybranyZNawigacji));
        tmp[0] = '\0';
        strcat(tmp, linkPodanyPrzezUzytkownika);
        strcat(tmp, linkWybranyZNawigacji);
        strcpy(linkWybranyZNawigacji, tmp);
    }
    for(i=0; i<liczbaLinkow; i++){
        free(listaLinkow[i]);
    }
    free(listaLinkow);
    liczbaLinkow = 0;
}

void zapytajCzySkorzystacZNawigacji(){
    printf("\n\n%s\n>>","Skorzystaæ z nawigacjii strony? (wyœwietli mo¿liwe przejœcia do innych stron)? T/N");
    scanf(" %c", &odpUzytkownika);
    if(odpUzytkownika == 'T' || odpUzytkownika == 't'){
        UZYCIE_NAWIGACJI = 1;
    } else if(odpUzytkownika == 'N' || odpUzytkownika == 'n'){
        UZYCIE_NAWIGACJI = 0;
        liczbaLinkow = 0;
    } else{
        BLAD_WALIDACJI = 1;
        liczbaLinkow = 0;
    }
    linkWybranyZNawigacji = NULL;
}

void wyczyscBuforInputuUzytkownika(){
    linkPodanyPrzezUzytkownika = NULL;
    linkPodanyPrzezUzytkownika = malloc(MAX_ROZMIAR_LINKU);
    linkPodanyPrzezUzytkownika[0] = '\0';
}

void poprosOLink(){
    wyczyscBuforInputuUzytkownika();
    printf("\n%s\n%s\n%s\n>>","--MENU--" ,"Wpisz quit aby wyjœæ", "Wpisz link, aby przejœæ do strony.");
    scanf(" %s", linkPodanyPrzezUzytkownika);
    if(strstr(linkPodanyPrzezUzytkownika, "quit")) ZAKONCZ = 1;
}


void wyswietlStrone(){
    if(zawartoscStrony != NULL){
        free(zawartoscStrony);
    }
    pobierzKodHTMLStrony(linkPodanyPrzezUzytkownika, &zawartoscStrony);
    if(BLAD_WALIDACJI == 0) przygotujStroneBezHTMLZLinkami(zawartoscStrony, &linkiStrony);
    if(BLAD_WALIDACJI == 0) printf("%s\n\n%s\n\n%s", "--ZAWARTOŒÆ STRONY--", zawartoscStrony, "--KONIEC ZAWARTOŒCI STRONY--");
}


void przepiszLinkiDoListyLinkow(char listaLinkow[liczbaLinkow][MAX_ROZMIAR_LINKU], const char* linkiString){
    int rozmiarLinkiString = strlen(linkiString);
    int i;
    int numerLinku = 0;
    char* link = malloc(MAX_ROZMIAR_LINKU);
    link[0] = '\0';
    for(i=0; i<rozmiarLinkiString; i++){
        if(linkiString[i] != '\n')zapiszZnakDoZmiennej(linkiString[i], link);
        if(linkiString[i] == '\n'){
            strcpy(listaLinkow[numerLinku], link);
            numerLinku++;
            free(link);
            link = malloc(MAX_ROZMIAR_LINKU);
            link[0] = '\0';
        }
    }
    free(link);
}
