//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                      Klasa morse (plik .h)                                           //
//                                                                                      //
//  Klasa ma za zadanie zamiane danych na sekwencje kodu  morsa                         //
//  przy uzyciu klasy pomocniczej translateToString                                     //
//                                                                                      //
//    Dostepna funkcjonalnosc:                                                          //
//                                                                                      //
//     Zamiana na sekwencje audio:                                                      //
//      morse << translateToString << translateToString;                                //
//                                                                                      //
//          // Przy zapisie np.: morse << "tekst" wszystko dziala zgodnie               //
//          //  z oczekiwaniami, poniewaz nastepuje niejawna konstrukcja obiektu        //
//          //  translateToString za pomoca odpowiedniego konstruktora                  //
//          //                                                                          //
//          //      Liste wspieranych typow mozna sprawdzic w pliku                     //
//          //          [ translateToString.h ]                                         //
//          //                                                                          //
//                                                                                      //
//     morse.setFrequency(int );    // Ustawienie czestotliwosci w Hz                   //
//                                  //  (domyslnie 1000Hz)                              //
//                                  //  Oraz zwraca czestotliwosc obiektu               //
//                                                                                      //
//     morse.setDotTime  (int );    // Ustawienie dlugosci . w ms                       //
//                                  //  (domyslnie  100ms)                              //
//                                  //  Oraz zwraca dlugosc .                           //
//                                                                                      //
//     morse.setDashTime (int );    // Ustawienie dlugosci - w ms                       //
//                                  //  (domyslnie  200ms)                              //
//                                  //  Oraz zwraca dlugosc -                           //
//                                                                                      //
//     morse.setPause    (int );    // Ustawienie przerwy pomiedzy - . w ms             //
//                                  //  (domyslnie   50ms)                              //
//                                  //  Oraz zwraca dlugosc tej przerwy                 //
//                                                                                      //
//     morse.setCharPause(int );    // Ustawienie przerwy pomiedzy symbolami            //
//                                  //  (domyslnie  100ms)                              //
//                                  //  Oraz zwraca dlugosc tej przerwy                 //
//                                                                                      //
//     morse.setShowDebug(bool);    // Wlacza wyswietlanie . - oraz znakow specjalnych  //
//                                  //  (zdefiniowanych w .cpp; domyslnie true)         //
//                                  //  Oraz zwraca aktualne ustawienia                 //
//                                                                                      //
//  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
//                                                                                      //
//  Domyslne symbole wyswietlane w trybie debugowania (mozliwa zmiana w .cpp)           //
//      .  // Wyswietlany podczas czytania .                                            //
//      -  // Wyswietlany podczas czytania -                                            //
//      x  // Wyswietlany pomiedzy . oraz - w pojedynczym symbolu                       //
//      0  // Wyswietlany podczas czytania spacji oraz po kazdej sekwencji w symbolu    //
//      #  // Wyswietlany podczas czytania niezaimplementowanego symbolu                //
//      Q  // Wyswietlany w funkcji pause                                               //
//                                                                                      //
//  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
//                                                                                      //
//     morse.getFrequency();        // Zwraca czestotliwosc w Hz                        //
//     morse.getDotTime();          // Zwraca dlugosc . w ms                            //
//     morse.getDashTime();         // Zwraca dlugosc - w ms                            //
//     morse.getPause();            // Zwraca przerwe pomiedzy - . w ms                 //
//     morse.getCharPause();        // Zwraca pomiedzy symbolami w ms                   //
//                                                                                      //
//     morse.getShowDebug();        // Zwraca true, jesli morse jest                    //
//                                  //  w trybie wyswietlania znakow                    //
//                                                                                      //
//     Obsluga manipulatorow:                                                           //
//      morse << manipulator;                                                           //
//                                                                                      //
//          Wbudowane manipulatory:                                                     //
//                                                                                      //
//              pause       // Sleep(morse.getCharPause())                              //
//                          //   Czyli zatrzymuje program tak, jak jest zatrzymywany    //
//                          //   po kazdym symbolu                                      //
//                                                                                      //
//                                                                                      //
//                                                                                      //
//  Autor: Szymon Krawczyk                                                              //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
// Changelog:                                                                           //
//  Data        |  Zmiany                                           | Przez kogo        //
// -------------|-------------------------------------------------- |------------------ //
//  16/11/2019  | Utworzenie klasy                                  | Szymon Krawczyk   //
//              |                                                   |                   //
//  17/11/2019  | Dodanie komentarzy                                | Szymon Krawczyk   //
//              | Dodanie manipulatora pause                        |                   //
//              | Dodanie pola showDebug                            |                   //
//              |                                                   |                   //
//  20/11/2019  | Dodanie komentarzy                                | Szymon Krawczyk   //
//              | Zmiana setterow na zwracanie wartosci obiektu     |                   //
//              |                                                   |                   //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef MORSE_H
#define MORSE_H

#include <Windows.h>

#include "translateToString.h"

namespace KrawczykS {

    class morse {
    private:
        int frequency;
        int dotTime;
        int dashTime;
        int pause;
        int charPause;
        // 'komunikacja' z tymi polami tylko przez metody

    protected:
        bool showDebug;     // Protected dla latwosci pracy w klasach dziedziczacych

    public:
        morse();
        morse(const morse&);
        virtual ~morse();       // Destruktor wirtualny zapewnia wywolanie destruktorow klas pochodnych
                                //  dzieki temu zapobieagmy mozliwym bledom, 
                                //  poniewaz niewywolanie destruktora klasy pochodnej moze prowadzic do np.: wyciekow pamieci

        morse & operator=(const morse&);

        int  setFrequency (int  = 1000);
        int  setDotTime   (int  =  100);
        int  setDashTime  (int  =  200);
        int  setPause     (int  =   50);
        int  setCharPause (int  =  100);
        bool setShowDebug (bool = true);

        int  getFrequency () const;
        int  getDotTime   () const;
        int  getDashTime  () const;
        int  getPause     () const;
        int  getCharPause () const;
        bool getShowDebug () const;

        friend morse & operator << (morse &, const translateToString&);     // Obsluga obiektow klasy pomocniczej

        friend morse & operator << (morse &, void (*pt)(morse&));           // Obsluga funkcji (manipulatorow)

        // Funkcja pomocnicza
        
            friend void toBeep(const morse&, char);     // Zamiana symbolu (znaku) na sekwencje audio
        //
        
    };

    // Manipulatory wbudowane (funkcje)

        void pause(morse&);
    //

    
}

#endif

/*
    //
    // Problem pause mozna rozwiazac na przyklad rowniez w taki sposob:
    //      const translateToString pause = " ";
    //
    //  Jednak nie jest to najlepsze rozwiazanie z powodow:
    //      1) Bylaby to prosta zamiana slowa pause na pojedyncza spacje w pozniejszym kodzie,
    //         co nie jest rozwiazaniem z podejsciem obiektowym
    //      2) Z uwagi na budowe wypikiwania symboli, spacja tlumaczona jest
    //         na dwie przerwy charPause, a dzieki rozwiazaniu z funkcja
    //         otrzymujemy prawidlowo tylko jedna przerwe
    //
    //  Funkcje pozwalaja rowniez na definiowanie dowolnych innych zachowan, np.:
    //  mozemy miec funkcje imperial(), ktora po uzyciu w programie wypika caly marsz imperialny.
    //  (nie ograniczamy sie wiec do uzycia znakow, mozemy uzyskac praktycznie kazde dozwolone zachowanie)
    //
*/