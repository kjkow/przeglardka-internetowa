#include <curl/curl.h>
#include <string.h>
#include "wspolne.h"

void obsluzBladAlokowaniaPamieci();

struct PobranaStrona {
  char* dane;
  size_t rozmiar;
};

size_t curlWyjscie(void *wskaznik, size_t liczbaPaczek, size_t rozmiarPaczki, struct PobranaStrona *aStr){

    size_t powiekszonyRozmiarODanePrzychodzace = aStr->rozmiar + rozmiarPaczki*liczbaPaczek;
    aStr->dane = realloc(aStr->dane, powiekszonyRozmiarODanePrzychodzace + 1);
    if(aStr->dane == NULL){
        obsluzBladAlokowaniaPamieci();
    }
    memcpy(aStr->dane + aStr->rozmiar, wskaznik, rozmiarPaczki*liczbaPaczek);
    aStr->dane[powiekszonyRozmiarODanePrzychodzace] = '\0';
    aStr->rozmiar = powiekszonyRozmiarODanePrzychodzace;

    return rozmiarPaczki*liczbaPaczek;
}

void inicjujStrukture(struct PobranaStrona *ps){
    ps->rozmiar = 0;
    ps->dane = malloc(1);
    if(ps->dane == NULL){
        obsluzBladAlokowaniaPamieci();
    }
    ps->dane[0] = '\0';
}

void pobierzKodHTMLStrony(const char* link, char** bufor){
    CURL *wskaznikCURL;
    CURLcode odpowiedzCURL;
    wskaznikCURL = curl_easy_init();

    if(wskaznikCURL) {
        struct PobranaStrona pobrana_strona;
        inicjujStrukture(&pobrana_strona);
        curl_easy_setopt(wskaznikCURL, CURLOPT_URL, link);
        curl_easy_setopt(wskaznikCURL, CURLOPT_WRITEFUNCTION, curlWyjscie);
        curl_easy_setopt(wskaznikCURL, CURLOPT_WRITEDATA, &pobrana_strona);

        odpowiedzCURL = curl_easy_perform(wskaznikCURL);
        if(odpowiedzCURL != CURLE_OK){
          fprintf(stdout, "Pobieranie strony zakonczone niepowodzeniem z powodu: \n%s\n", curl_easy_strerror(odpowiedzCURL));
          curl_easy_cleanup(wskaznikCURL);
          BLAD_WALIDACJI = 1;
          curl_global_cleanup();
          *bufor = malloc(1);//zeby pozniej mozna bylo zrobic niezaleznie od bledu free w mainie
          return;
        }
        *bufor = malloc(pobrana_strona.rozmiar+1);
        strcpy(*bufor, pobrana_strona.dane);
        free(pobrana_strona.dane);
        curl_easy_cleanup(wskaznikCURL);
    }

    curl_global_cleanup();
}

void obsluzBladAlokowaniaPamieci(){
    printf("Zalokowanie pamieci nie powiodlo sie");
    exit(EXIT_FAILURE);
}
