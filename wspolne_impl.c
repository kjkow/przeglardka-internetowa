#include <string.h>

void zapiszZnakDoZmiennej(const char c, char* ciagZnakow){
    int rozmiar = strlen(ciagZnakow);
    if(
       (c == ' ' || c == '\n' || c == '\t') &&
       (ciagZnakow[rozmiar-1] == ' ' || ciagZnakow[rozmiar-1] == '\n' || ciagZnakow[rozmiar-1] == '\t')){ //¿eby nie by³o dwoch enterow lub spacji po sobie
        return;
    }

    ciagZnakow[rozmiar] = c;
    ciagZnakow[rozmiar+1] = '\0';
}
