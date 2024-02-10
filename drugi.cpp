/*#include <iostream>

using namespace std;

void playerData(char& id, int* player){ // funkcja do przetwarzania danych o graczu id przez referencję - aby tam wpisać, playera przez wskaźnik
    cin>>id; // id, czyli a-z
    int x;   // aktualna liczba oczek
    for (int i=0;i<4;i++){
        cin>>x; // pobieramy, cin pomija białe znaki
        player[x-1]++; // w player jest liczba wystąpień player = [ 2 1 0 1 ], wyrzucił dwa razy 1, raz dwójkę, i raz czwórkę
    }
    // powrót do maina już ze zmienionymi danymi playera
}

void clearPlayers(int* a,int* b){ // tak samo wskaźniki, aby można było pisac po pamięci a nie tworzyć kopie zmiennych
    for (int i=0;i<4;i++){ // dla wszystkich wylosowań ustawiamy 0, czyli taka sytuacja, iż żaden player jeszcze nie rzucił kostką.
        a[i]=0;
        b[i]=0;
    }
    // powrót do maina
}

void determineWin(int* player, int* win){ // przekazujemy wskaźniki na te miejsca w pamięci, aby "w nich zapisywać" ( lepiej niż wszystko jako globalne zmienne) ładniej i czysciej
    // przekazujemy losowanie gracza oraz tablicę z wynikami jego zwycięstwa
    if(player[0] == 1 && player[1] == 1 && player[2] == 1 && player[3] == 1)  // jeśli nic sie nie powtarza, 2 zwycięstwo ( z tabeli z pdf-a)
    {
        win[0]=2; // więc drugie zwycięstwo
        win[1]=0; // nie ma "determistycznej liczby" bo wszystkie są XD
    }
    else if(player[3] == 2 && (player[2] == 2 || player[1] == 2 || player[0] == 2)){ // wylosował 4 dwa razy (player[3] to ile razy czwórkę wylosował) i coś innego dwa razy
        win[0]=3; // wygrana 3
        win[1]=4; // największa liczba to 4
    }else if(player[2] == 2 && (player[1] == 2 || player[0] == 2)) // jak nie 4 to może 3 dwa razy, player[2] to ilość wylosowań 3. podobnie
    {
        win[0]=3; // trzecia wygrana
        win[1]=3; // najwieksza to 3
    }else if(player[1] == 2 && player[0] == 2) // to może chociaż 2, zobacz że poprzednie kombinacje czyli [ 2 x x x ], [ 0 2 x x ], [0 0 2 2] rozpatrzyliśmy wyżej w tych nawiasach,
                                               // więc jesli tu jesteśmy to zostaje nam tylko opcja [ 2 2 0 0] do sprawdzenia. ten fakt będzie dla nas istotny niżej, w lini 55
    {
        win[0]=3;
        win[1]=2;
    }
    else
        win[0]=6; // jeśli nie wygrał to wygraną ustawiamy na maxa (czyli cokolwiek z nim tera wygra

    win[2] = player[0] + player[1]*2 + player[2]*3 + player[3]*4; // robimy sumę oczek, pod player[x] jest liczba wystąpień oczka x+1 ( bo tablicę indeksujemy od 0)

    for (int i=3;i>=0;i--){ // sprawdzamy po kolei od końca czy któryś wynik się powtórzył, bo mamy w tablicy player indexy [ 0 1 2 3 ] więc od 3 do 0
        if(1 < win[0] && player[i]==4){ // jeśli nie mamy pierwszej wygranej, to jest po to, lecimy od końca, więc jesli mamy w tablicy [ 0 0 0 4 ] to nie ma innej opcji,
            win[0] = 1;   // 1 rodzaju, najlepsze
            win[1] = i+1; // wpisujemy, jesli za pierwszym przejściem, zobacz, że i=3, więc jakie oczko cztery razy wylosowaliśmy?
                          // no 4, inaczej, które oczko zliczamy pod trzecim indexem ? no 4 oczka, więc +1 bo od 0 indeksujemy
        }else if(4 < win[0] && player[i]==3){ // zobacz, że jest to wygrana numer 4, więc 1 2 3 są lepsze, więc robimy to tylko w tedy gdy nie mamy "lepszych ( niższych) wygranych.
            win[0] = 4; // to ustawiamy na 4, tak samo, wyżej jest <, bo jeśli mamy powtórzenie np [ 0 0 1 3 ] to nie chcemy by nam wbijało tu, bo innej opcji nie ma, ale też dlatego,
                        // aby gdyby coś to aby nie zmieniło nam wartości deterministycznej na mniejszą
            win[1] = i+1; // tak jak wyżej
        }else if(5 < win[0] && player[i] == 2) // jeśli <5, czyli jeszcze wcale nie wygraliśmy, i mamy jakąkolwiek dwójkę ( zauważ, że sytuację z dwoma dwójkami [ 0 0 2 2 ] rozpatrzyliśmy wyżej
            // a jeśli były dwie dwójki, to win[0] jest MNIEJSZY od 5 ( dokładnie ma wartość 3) więc warunek 5 < win[0] nie zostałby spełniony.
        {
            win[0] = 5;   // wygrana 5 rodzaju
            win[1] = i+1; // element znaczący
        }
    }
    // powrót do maina
}

int chooseWinner(int* a,int* b){
    if (a[0] < b[0]) // gracz a ma wygraną "lepszego typu" czyli wyżej w tabeli, np wylosował 4 4 4 4, to ma najmniejszy typ wygranej
        return 1;
    if (b[0] < a[0]) // b wygrał
        return -1;

    // tu wchodzimy tylko jeśli wygrane są tego samego typu
    if (a[1] > b[1]) // liczba determinująca, czyli np  A = 1 3 3 3  B = 1 2 2 2 to a[1] = winA[1] = 3 b[1] = winB[1] = 2 im większa tym lepiej
        return 1; // wygrał gracz a
    else if (a[1] < b[1])
        return -1; // wygrał b
    else if (a[2] > b[2]) // jesli są takie same np A = 1 1 3 3  B = 2 2 3 3 więc a[1]=b[1] = 3, to bierzemy sumę, większa suma wygrywa
        return 1; // suma a jest większa, więc a wygrywa
    else if (a[2] <b[2])
        return -1; // b wygrał

    return 0; // jeśli nikt nie wygrał to jest remis.
    // powrót do maina
}

// tu zacznij czytać, przeskakuj do kolejnych funkcji jesli pierwszy raz jest wyowłana

/* o co chodzi z 'z'-x*1, gdzie x to jakaś literka z przedziału a-z x='a' ( w 118 linii)
 * to A*1 jest z przyzwyczajenia, lepiej dać niż nie, bo czasami bez tego się coś psuje
 * literki zrzutowane (odczytanie) na inty dają nam kody asci, więc np dla x='a'
 * to jest tak jakby były 122-97 ascii więc to namd da 25, można od a do z (x*1-'a')*(-1) to masz tablice od 0 iluś tam, ewentualnie 122 - (x*1-'a'), ale zobacz że to jest nadmierne.
 * (to *1 jest po to, aby otrzymać kod asci 'a')
 */

/*
int stats[26][3]; // statystyki dla wszystkich graczy 26 liter a-z, 3 pozycje win, los, remis 'a' = 97, 'z' = 122 czyli 'z'-'a'*1 = 122-97 = 25
// od z do a stats[0] = player z; natomiast stats[25] = player a

int main()
{
    int n;    // ilość rozgrywek
    char A,B; // nazwy graczy a-z
    int playerA[4]={0},playerB[4]={0}; // Tablice z rzutami aktualnych graczy
    int winA[3]={0},winB[3]={0},win;   // tablice winA[0] - typ wygranej, im mniejszy tym lepiej, [1] - liczba która determinuje wygraną 1 3 3 3 i 1 2 2 2 to winA[1] = 3 winB[1] = 2 do porównań. większa = lepiej
    // [2] - suma wszystkich oczek, większa = lepiej
    // win = 1 - gracz A wygrał, win = -1 - gracz B wygrał win=0 remis

    cin>>n; // pobieramy ilość rozgrywek

    for (int i=0;i<n;i++){ // dla każdego "meczu"
        playerData(A,playerA); // Przekazujemy dane z wejścia A = a-z playerA - tablica z rzutami
        playerData(B,playerB);
        determineWin(playerA, winA); // sprawdzamy jakie zwycięstwo ma gracz A, wynik będzie w winA
        determineWin(playerB, winB); // tak samo dla gracza B

        win = chooseWinner(winA,winB); // przekazujemy wyniki graczy A i B
        if (win == 1){
            stats['z'-A*1][0]++; // dodajemy wygraną do statów gracza A 'z'-A*1 da nam inta wyżej opisane  stats[0][0] to wygrana
            stats['z'-B*1][2]++; // stats[x][2] to przegrana
        }else if(win == 0){ // jest remis
            stats['z'-A*1][1]++; // do remisu dodajemy
            stats['z'-B*1][1]++;
        }else{                  // B wygrał
            stats['z'-A*1][2]++;
            stats['z'-B*1][0]++;
        }
        clearPlayers(playerA,playerB); // czyszczenie wartości wylosowań graczy
        // zaczynamy zabawę z kolejną linią, czyli kolejną rozgrywką między dwoma graczami, tak n razy
    }

    double w,r,l; // win , remis, lose
    double suma; // ile rozegrał do % i do wyświetlania
    char znak; // jaka literka gracza

    for (int i=25;i>=0;i--) // dla wszystkich graczy po kolei
    {
        znak = 1*'z'-i; // musimy dać - aby się zgadzało, ma być w kolejności alfabetycznej, w pierwszym dla 'a' powino być 97, sprawdźmy, 'z' to 122, i to 25 (bo pierwsza literacja)
        // więc 122-25 = 97, zgadza się, w kolejnych bedizemy odejmowac coraz mniejsze liczby, więc w ostatnim dojdziemy do 122 czyli do z. o to nam chodzi
        w = stats[i][0]; // odczytanie ilości wygranych
        r = stats[i][1]; // remisów
        l = stats[i][2]; // przegranych
        suma = w+r+l;    // sumujemy, wszystkie rozegrane "mecze"
        if (suma)
        {
            cout<<"gracz "<<znak<<"\n"; // jak w wyjściu, gracz a

            if (w>0)
                cout<<"     wygrane: "<<w/suma*100<<"%\n"; // spacje, wygrane... w/suma*100 aby było 24.5 dopisujemy %
            if (r>0)
                cout<<"     remisy: "<<r/suma*100<<"%\n";
            if (l>0)
                cout<<"     przegrane: "<<l/suma*100<<"%\n";
            cout<<"\n"; // linijka odstępu
        }
    }
    // koniec programu
    return 0;
}
 */