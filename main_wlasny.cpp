//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                      Klasa morse (plik pokazujacy mozliwosci klasy)                  //
//                                                                                      //
//  Autor: Szymon Krawczyk                                                              //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
// Changelog:                                                                           //
//  Data        |  Zmiany                                           | Przez kogo        //
// -------------|-------------------------------------------------- |------------------ //
//  16/11/2019  | Utworzenie programu                               | Szymon Krawczyk   //
//              |                                                   |                   //
//  17/11/2019  | Dodanie komentarzy                                | Szymon Krawczyk   //
//              | Dodanie debugowania                               |                   //
//              |                                                   |                   //
//  20/11/2019  | Dodanie przykladu wlasnego manipulatora           | Szymon Krawczyk   //
//              |                                                   |                   //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "morse.h"



// Manipulatory mozna pisac samemu, wazne jest, zeby byly takie: void <nazwa>(KrawczykS::morse& <nazwa>)
//                                                                 // obiekt mors nawet nie  musi byc wykorzystywany przez dany manipulator
//  Przyklad manipulatora napisanego przez uzytkownika:

    void helloManip(KrawczykS::morse& dowolna_nazwa) {

        std::cout << "\nHello World!!";
        std::cout << "  \/\/Jestem manipulatorem wlasnym uzytkownika :)\n";

        // Dowolne dozwolone zachowania
        //
        // . . .
        //
    }
//



int main() {

    using KrawczykS::translateToString; // Dla pokazania dzialania klasy pomocniczej
    using KrawczykS::morse;
    using KrawczykS::pause;             // Manipulator pause

    using std::cin;
    using std::cout;

    morse m;

    cout << "Gdy podamy niewlasciwa wartosc czestotliwosci lub czasu, klasa o tym powiadomi\n"
         << " oraz ustawi wartosci domyslne:\n";
    m.setFrequency(-1000);
    m.setPause(50);
    m.setDotTime(-100);
    m.setDashTime();
    m.setCharPause(100);


    cout << "\n<Enter> aby kontynuowac\n";
    cin.get();


    cout << "\n Parametry obecnego obiektu\n"
         << "\n  Czestotliwosc:               " << m.getFrequency() << "Hz"
         << "\n  Czas . :                     " << m.getDotTime()   << "ms"
         << "\n  Czas - :                     " << m.getDashTime()  << "ms"
         << "\n  Odstep pomiedzy . oraz - :   " << m.getPause()     << "ms"
         << "\n  Odstep pomiedzy symbolami :  " << m.getCharPause() << "ms"
         << "\n\n"
        ;


    cout << "\n<Enter> aby kontynuowac\n";
    cin.get();


    cout << "\nKlasa pomocnicza translateToString (przyklady)\n";
    cout << "\n                     1.123456789123456789 => " <<                    1.123456789123456789 << "\n";
    cout << "\n  (translateToString)1.123456789123456789 => " << (translateToString)1.123456789123456789 << "\n\n";

    cout << "\n                     1.7E308 => "              <<                    1.7E308 << "\n";
    cout << "\n  (translateToString)1.7E308 => "              << (translateToString)1.7E308 << "\n\n";

    cout << "Nalezy zauwazyc, ze liczby rzutowane na typ translateToString sa zapisane jako std::string\n";


    cout << "\n<Enter> aby kontynuowac\n";
    cin.get();
    system("CLS");


    cout << "m << \"SOS\" << helloManip << 420;\n";
             m <<  "SOS"  << helloManip << 420; // uzycie wlasnego manipulatora


    cout << "\n<Enter> aby kontynuowac\n";
    cin.get();


    cout << " Aby lepiej zrozumiec zamiane na kod morsa, wlaczmy tryb debugowania:\n"
         << "    m.setShowDebug()\n\n";
    m.setShowDebug();
    cout << "  .  // Wyswietlany podczas czytania .\n"
         << "  -  // Wyswietlany podczas czytania -\n"
         << "  x  // Wyswietlany pomiedzy . oraz - w pojedynczym symbolu\n"
         << "  0  // Wyswietlany podczas czytania spacji oraz po kazdej sekwencji w symbolu\n"
         << "  #  // Wyswietlany podczas czytania niezaimplementowanych symboli\n"
         << "  Q  // Wyswietlany w funkcji pause\n\n"
        ;

    cout << "\n<Enter> aby kontynuowac\n";
    cin.get();


    cout << "m << \"SOS\" << 420\n";
             m <<  "SOS"  << 420; 

    cout << "\n<Enter> aby kontynuowac\n";
    cin.get();


    cout << "m << \"Al@ ma kot@\" << pause;\n";
             m <<  "Al@ ma kot@"  << pause;
    cout << "\n\nm << ' ' << 1.1234567890123 << ' ';\n";
                 m << ' ' << 1.1234567890123 << ' ';


    cout << "\n\n<Enter> aby kontynuowac\n";
    cin.get();


    cout << " Tryb debugowania mozna wylaczyc\n"
         << "    m.setShowDebug(false)\n\n";

    m.setShowDebug(false);

    cout << "m << \"SOS\" << 420\n";
             m <<  "SOS"  << 420;

    cout << "\n\n - - Koniec - - \n\n";
    cin.get();

    return 0;
}
