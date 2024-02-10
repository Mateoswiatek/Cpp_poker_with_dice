/*
#include <iostream>

using namespace std;

int main() {
    int n;
    char nazwaA, nazwaB;
    int win[nazwaA*1-'a'], remis[nazwaB*1-'a'];

    cin>>n; // zapisujemy ilość rozgrywek
    for(int z=0;z<n;z++) // dla każdej z linii
    {   // a 1 2 1 1 c 1 2 3 3
        int x, A[4] = {0}, B[4] = {0}, wynik=0;
        cin >> nazwaA;
        for (int j=0;j<4;j++){
            cin >> x;
            A[x-1] = A[x-1] + 1;
        }

        cin>>nazwaB;
        for(int j=0;j<4;j++) {
            cin >> x;
            B[x-1] = B[x-1] + 1;
        }

        // w tablicach mamy wystąpienia
        // A=[0,1,2,1] wylosował 2, 3, 3, 4

        // wynik 1=pierwszy, 2=drugi 3=remis
        wynik = 0;
        int flag_a, flag_b, oczka_a, oczka_b; // zmienne pomocnicze

        for(int i=3; i>=0; i--){ // sprawdzam czy wystąpiła u któregoś 1 sytuacja 4 4 4 4 = [ 0 0 0 4 ]
            if(A[i] != 4 and B[i] != 4){ continue;}
            if(A[i] == 4 and B[i] != 4){wynik=1; break;}
            if(A[i] != 4 and B[i] == 4){wynik=2; break;}
            if(A[i] == 4 and B[i] == 4){wynik=3; break;}
        }
        if(wynik == 0){
            flag_a=1;
            flag_b=1;
            for (int i=0; i<4; i++) { // sprawdzam czy wystąpiła u któregoś 2 sytuacja  1 2 3 4 = [ 1 1 1 1]
                if (A[i] != 1){flag_a = 0;}
                if (B[i] != 1){flag_b = 0;}
            }
            if(flag_a and flag_b) { wynik = 3;} // 1 1
            else{                          // 10, 01, 00
                if(flag_a) { wynik = 1;} // 10
                else {
                    if (flag_b) { wynik = 2; } // 01
                }
            }

            if(wynik == 0){ // jeśli do tej pory nie wiadomo kto wygra
                flag_a = 0;
                flag_b = 0;                  // czy wystąpiła u któregoś 3 sytuacja 4 4 2 2 = [ 0 2 0 2 ]
                for (int i = 0; i < 4; i++) { //  od najmniejszej, w liczbie będzie największa sprawdzam
                    // jeśli flaga będzie równa 1, to jest 5 przypadek, tak samo sprawdzić czy flabaa / b = 1, a jak nie to zależy
                    if(A[i] == 2) { flag_a+=1, oczka_a=i+1;} // ostatnie wywołanie będzie dla największej pary
                    if(B[i] == 2) { flag_b+=1; oczka_b=i+1;}
                }
                if(flag_a==2 and flag_b==2) { // 1 1
                    if ( oczka_a == oczka_b ){ // xx 44  yy 44
                        // tu trezba dopisac tą sume
                        wynik = 3;
                    }
                    else if ( oczka_a > oczka_b){
                        wynik = 1;
                    }
                    else wynik = 2;

                }
                else{                          // 10, 01, 00
                    if(flag_a==2) { wynik = 1;} // 10
                    else {
                        if (flag_b==2) { wynik = 2; } // 01
                    }
                }

                if(wynik == 0){
                    for (int i=3; i>=0; i--) { // sprawdzam czy wystąpiła u któregoś 4 sytuacja  4 4 4 1 = [ 1 0 0 3 ]
                        if(A[i] != 3 and B[i] != 3){ continue;}
                        if(A[i] == 3 and B[i] != 3){wynik=1; break;}
                        if(A[i] != 3 and B[i] == 3){wynik=2; break;}
                        if(A[i] == 3 and B[i] == 3){wynik=3; break;}
                    }
                    if(wynik == 0){
                        flag_a = 0;
                        flag_b = 0; // od poczatku, więc
                        for (int i=0; i<4; i++) { // sprawdzam czy wystąpiła u któregoś 5 sytuacja  4 4 2 1 = [ 1 1 0 2 ]
                            if (A[i] == 2){flag_a += 1; oczka_a=i+1;} // ostatnie jest najwieksze
                            if (B[i] == 2){flag_b += 1; oczka_b=i+1;}
                        }
                        if(flag_a == 1 and flag_b == 1){
                            if(oczka_a > oczka_b){ wynik = 1;}
                            else wynik = 2;
                            // tu trezba dopisac tą sume
                        }
                    }
                }
            }
        }

        cout<< "wygral gracz" << wynik;




    }

    return 0;
}

*/

// reguły:

// przechowywanie wyników graczy - słownik gdzie klucz to nazwa gracza, a wartość to tablica [wygrane, remis, przegrane] ilosc rozgrywek to suma tych trzech. wynik. gdy wygrywa +1, w wyświetlaniu robimy raz sumę, i później wyświetlamy wynik[i] / suma przemnożone przez 100
// wyświetlanie tylko jeśli statystyka jest różna od 0. czyli jeśli wynik[i] = 0, nic nie piszemy

// 4 ścianki są, więc jednaka tylko 4 będą
//liczba oczek 1 2 3 4 = i
//    indexy   0 1 2 3
//  kostki = [         ]
// 1 punkt lista zliczająca które liczby ile razy zostały wyrzucone, literujemy po wyrzuceniach, aktualna liczba to i, zwiększamy tab[i-1] o 1 ( początkowo tab dajemy na 0) jest 6 elementów , bo od 0 mamy tablice.
// 2 dodatkowe zmienne typu uint_8, wynik, liczba która doprowadziła ( i to ta liczba która doporawdziła, aby rozstrzygać remisy). prezz wskaźniki, bo nie można klas i struktur F
// jeśli będzie remis, to porównujemy liczby które doporwadziły do remisu, ten co większe wygrywa
//
// jeśli te liczby będą takie same, to: zawsze będziemy robić sumę oczek, aby przekazywać do porównania. jeśli żadne inne nie będą, abysmy nie musieli się wracać
// inaczej robimy sumę wszystkich oczek, jeśli nie ma żadnych lepszych. czyli robimy sumę tab[i-1]*i, czyli ilość wystąpień i tego wyniku, razy ten wynik.


// Wejście: Cin
/* Pierwsza dana to N - ilośc rozgrywek (kolejnych wierszy)
 *  każda rozgrywkarozgrywka to osobna linia:
 *  idA a1 a2 a3 a4 idB b1 b2 b3 b4
 *
 *  idA = a - z
 *  ax, bx to wyniki 1-4
 *
 *  a 4 4 4 4 b 1 2 3 4
 */

//Wyjście Cout
/* Dla każdego gracza który brał udział w rozgrywkach, ma zostać wypisany rekord
 * W kolejności alfabetycznej mają być wypisywane
 *
 * Nagłówek (gracz a)
 * Statystyki (4 spacje, jeno ze słów wygrane, remisy, przegrane: 1-100%
 * (pusta linia)
 *
 *
 */