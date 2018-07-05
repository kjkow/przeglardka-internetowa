# przeglardka-internetowa
Konsolowa przeglądarka internetowa napisana w C jako projekt na studiach  

## Uruchamianie programu
Musiałbyś rozpakować przesłaną przeze mnie paczkę z .exe-kami i .dll-ami. Ze względów bezpieczeństwa pewnie nie chcesz tego robić :)

## Sposób działania programu
Program przyjmuje od użytkownika link do strony internetowej. Przedrostek "http://www" można
pominąć. Wykorzystuje bibliotekę libcurl aby pobrać kod źródłowy strony za pomocą protokołu
HTTP. Z pobranego kodu wyodrębnia zawartość strony z wykluczeniem tagów html oraz wszystkie
linki zawarte w tagu html <a> z wartości href tego taga. Następnie pyta użytkownika czy chce
skorzystać z wyżej uzyskanej nawigacji, czy ponownie wpisać link ręcznie. Skorzystanie z
nawigacji skutkuje wypisaniem numerowanej listy linków, aby przejść do konretnego wystarczy
wpisać liczbę odpowiadającą wybranemu linkowi. Działanie programu jest zapętlone i może zostać
przerwane jeśli użytkownik zamiast linku wpisze słowo kluczowe quit.  
  
## Kluczowe wady programu
- Brak polskich znaków – problem z kodowaniem przy użyciu libcurl, mimo wielu prób nie
udało się ustawić dla curla kodowania polskich znaków. Zastosowano obejście –
wyświetlanie znaku '_'.
- Jeśli zawartość strony jest obszerna to zostanie wyświetlona w standardowym trybie – na
tyle ile pozwoli konsola – nie będzie można przewinąć do góry żeby przeczytać początek.
To samo z linkami – jeśli ich lista jest zbyt długa to zostanie wyświetlonych tylko
kilkadziesiąt ostatnich (w zależności od rozmiaru bufora konsoli). Propozycja rozwiązania –
można by dzielić zawartość strony na paczki i wyświetlać po jednej czekając aż użytkownik
wskaże że chce przejść dalej.
- Brak obsługi protokołu SSL/TLS – teoretycznie libcurl pozwala na taką obsługę
  
## Źródła
- Dokumentacja biblioteki libcurl - https://curl.haxx.se/libcurl/c/
- Rozwiązywanie różnych drobnych problemów implementacyjnych -
https://stackoverflow.com/
- Instalacja biblioteki libcurl w środowisku programistycznym CodeBlocks -
https://www.youtube.com/watch?v=u4L1_mXuJxQ
• Algorytm na którym bazowałem podaczas implementacji funkcji usuwania tagów html z
pobranego kodu źródłowego strony - http://c.happycodings.com/smallprograms/
code28.html
