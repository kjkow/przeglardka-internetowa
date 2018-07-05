#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "obsluga_html.h"
#include "wspolne.h"


int czyWTagu;
int pomocnicza;
char buforTagaHtml[512];
char *wskaznikNaBuforTagaHTML;
size_t rozmiarKoduStronyZHTML;

char* stronaZKodemHTML;
char* stronaBezHTML;

int czyWLinku;
char poprzedniZnak = '\0';

char* linkiString;


char podajZnakSpozaTaguHTML(const char c){
    if(c == '<') czyWTagu = TAK;
    if(czyWTagu == TAK) *wskaznikNaBuforTagaHTML++ = c;
    if(c == '>'){
        czyWTagu = NIE;
        *wskaznikNaBuforTagaHTML++ = '\0';
        if(strstr(buforTagaHtml, "<s") != 0) pomocnicza = TAK;
        if(strstr(buforTagaHtml, "<S") != 0) pomocnicza = TAK;
        if(strstr(buforTagaHtml, "</") != 0) pomocnicza = NIE;
        wskaznikNaBuforTagaHTML = buforTagaHtml;
    }

    if(czyWTagu == NIE && pomocnicza == NIE && c != '>'){
        return c;
    }
    return '\0';
}

char podajZnakZLinkuHTML(const char c){
    if(c == '<') czyWTagu = TAK;
    if(czyWTagu == TAK) *wskaznikNaBuforTagaHTML++ = c;
    if(czyWTagu == TAK && c == 'a' && poprzedniZnak == '<'){
        czyWLinku = TAK;
    }

    if(c == '>') {
        czyWTagu = NIE; *wskaznikNaBuforTagaHTML++ = '\0';
        if(strstr(buforTagaHtml, "<s") != 0 || strstr(buforTagaHtml, "<S") != 0) pomocnicza = TAK;
        if(strstr(buforTagaHtml, "</") != 0) pomocnicza = NIE;
        czyWLinku = NIE;
        wskaznikNaBuforTagaHTML = buforTagaHtml;
    }

    poprzedniZnak = c;

    if(czyWLinku == TAK){
        return c;
    }else{
        return '\0';
    }
}

void oczyscKodHTML(){
    wskaznikNaBuforTagaHTML = buforTagaHtml;
    int i;
    char c;
    for(i=0;i<rozmiarKoduStronyZHTML;i++){
        c = podajZnakSpozaTaguHTML(stronaZKodemHTML[i]);
        if(c != '\r'  && c != '\0'){
            if(c < 0) zapiszZnakDoZmiennej('_', stronaBezHTML);
            else zapiszZnakDoZmiennej(c, stronaBezHTML);
        }
    }
}

void wyszukajLinki(){
    wskaznikNaBuforTagaHTML = buforTagaHtml;
    int i;
    char c;
    char ciagZnakowHref[5] = "href=";
    int buforNaCiagZnakowHref[5] = {0,0,0,0,0};
    int znacznikCiapek = 0;
    for(i=0;i<rozmiarKoduStronyZHTML;i++){
        c = podajZnakZLinkuHTML(stronaZKodemHTML[i]);
        if(c != '\r'  && c != '\0'){

            if(buforNaCiagZnakowHref[0] == 1 && buforNaCiagZnakowHref[1] == 1 && buforNaCiagZnakowHref[2] == 1 && buforNaCiagZnakowHref[3] == 1 && buforNaCiagZnakowHref[4] == 1 && buforNaCiagZnakowHref[5] == 1){
                if(znacznikCiapek == 1 && c == '"'){//To znaczy ¿e koniec linku
                    znacznikCiapek = 0;
                    buforNaCiagZnakowHref[0] = 0;
                    buforNaCiagZnakowHref[1] = 0;
                    buforNaCiagZnakowHref[2] = 0;
                    buforNaCiagZnakowHref[3] = 0;
                    buforNaCiagZnakowHref[4] = 0;
                    strcpy(ciagZnakowHref, "href=");
                    zapiszZnakDoZmiennej('\n', linkiString);
                    liczbaLinkow++;
                } else if(c == '"'){
                    znacznikCiapek = 1;
                    continue;
                } else{
                    if(c < 0) zapiszZnakDoZmiennej('_', linkiString);
                    else zapiszZnakDoZmiennej(c, linkiString);
                }
            }

            if(c == ciagZnakowHref[0]) buforNaCiagZnakowHref[0] = 1;
            if(c == ciagZnakowHref[1] && buforNaCiagZnakowHref[0] == 1) buforNaCiagZnakowHref[1] = 1;
            if(c == ciagZnakowHref[2] && buforNaCiagZnakowHref[0] == 1 && buforNaCiagZnakowHref[1] == 1) buforNaCiagZnakowHref[2] = 1;
            if(c == ciagZnakowHref[3] && buforNaCiagZnakowHref[0] == 1 && buforNaCiagZnakowHref[1] == 1 && buforNaCiagZnakowHref[2] == 1) buforNaCiagZnakowHref[3] = 1;
            if(c == ciagZnakowHref[4] && buforNaCiagZnakowHref[0] == 1 && buforNaCiagZnakowHref[1] == 1 && buforNaCiagZnakowHref[2] == 1 && buforNaCiagZnakowHref[3] == 1) buforNaCiagZnakowHref[4] = 1;
            if(c == ciagZnakowHref[5] && buforNaCiagZnakowHref[0] == 1 && buforNaCiagZnakowHref[1] == 1 && buforNaCiagZnakowHref[2] == 1 && buforNaCiagZnakowHref[3] == 1 && buforNaCiagZnakowHref[4] == 1) buforNaCiagZnakowHref[5] = 1;
            if(buforNaCiagZnakowHref[0] == 1 && buforNaCiagZnakowHref[1] == 1 && buforNaCiagZnakowHref[2] == 1 && buforNaCiagZnakowHref[3] == 1 && buforNaCiagZnakowHref[4] == 1 && buforNaCiagZnakowHref[5] == 1){
                if(c == '='){
                    continue;
                }
                if(znacznikCiapek == 1){
                    continue;
                }else{
                    zapiszZnakDoZmiennej(c, linkiString);
                }

            }
        }
    }
}

void inicjujZmienne(){
    czyWTagu = NIE;
    pomocnicza = NIE;
    czyWLinku = NIE;
    wskaznikNaBuforTagaHTML = NULL;
    stronaZKodemHTML = malloc(rozmiarKoduStronyZHTML + 1);
    stronaBezHTML = malloc(rozmiarKoduStronyZHTML + 1);
    stronaBezHTML[0] = '\0';
    linkiString = malloc(rozmiarKoduStronyZHTML + 1);
    linkiString[0] = '\0';
}


void przygotujStroneBezHTMLZLinkami(char *kodStronyHTML, char** stringZLinkami){
    rozmiarKoduStronyZHTML = (size_t) strlen(kodStronyHTML);
    char* kopiaKoduStrony = malloc(rozmiarKoduStronyZHTML + 1);
    strcpy(kopiaKoduStrony, kodStronyHTML);

    inicjujZmienne();
    strcpy(stronaZKodemHTML, kopiaKoduStrony);
    memset(buforTagaHtml, 0, 512);//wyczysc na wszelki wypadek
    oczyscKodHTML();
    strcpy(kodStronyHTML, stronaBezHTML);
    free(stronaZKodemHTML);
    free(stronaBezHTML);

    inicjujZmienne();
    strcpy(stronaZKodemHTML, kopiaKoduStrony);
    wyszukajLinki();

    *stringZLinkami = malloc(liczbaLinkow * MAX_ROZMIAR_LINKU);
    strcpy(*stringZLinkami, linkiString);
}
