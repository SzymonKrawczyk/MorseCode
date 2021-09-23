//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                      Klasa translateToString (plik .h)                               //
//                                                                                      //
//  Klasa ma za zadanie zamiane roznych typow na typ std::string                        //
//                                                                                      //
//    Dostepna funkcjonalnosc:                                                          //
//                                                                                      //
//      Za pomoca konstruktora nastepuje zamiana wspieranych typow                      //
//      na std::string przechowywany w polu _str                                        //
//                                                                                      //
//          translateToString przyklad1(/* dowolny wspierany typ */);                   //
//          translateToString przyklad2 = /* dowolny wspierany typ */;                  //
//                                                                                      //
//          Wspierane typy (oraz ich stale odpowiedniki):                               //
//                     std::string                                                      //
//                          char                                                        //
//                          char*                                                       //
//                 unsigned short (nastepuje konwersja na int)                          //
//                          short (nastepuje konwersja na int)                          //
//                 unsigned int                                                         //
//                          int                                                         //
//                 unsigned long                                                        //
//                          long                                                        //
//                 unsigned long long                                                   //
//                          long long                                                   //
//                          float                                                       //
//                          double                                                      //
//                          long double                                                 //
//                                                                                      //
//      std::cout << translateToString              // Wyswietlenie pola _str           //
//                                                                                      //
//      translateToString.getString()               // Zwraca pole _str                 //
//      translateToString.getStringCopy()           // Zwraca kopie pola _str           //
//                                                                                      //
//      translateToString.setString(std::string)    // Ustawia nowy string w polu _str  //
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
//              |                                                   |                   //
//  20/11/2019  | Poprawa komentarzy                                | Szymon Krawczyk   //
//              | Zmiana setterow na zwracanie wartosci             |                   //
//              |                                                   |                   //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef TRANSLATETOSTRING_H
#define TRANSLATETOSTRING_H

#include <string>
#include <iostream>

namespace KrawczykS {

    class translateToString {

    private:
        std::string _str;

    public:
        translateToString();
        translateToString(const translateToString&  );

        translateToString(         std::string);      // kopiowanie string na string

        translateToString(   const char*      );      // zamiana char* na string
        translateToString(         char       );      // zamiana char  na string

        translateToString(         int        );      // zamiana int       na string
        translateToString(         long       );      // zamiana long      na string
        translateToString(         long long  );      // zamiana long long na string

        translateToString(unsigned int        );      // zamiana unsigned int       na string
        translateToString(unsigned long       );      // zamiana unsigned long      na string
        translateToString(unsigned long long  );      // zamiana unsigned long long na string

        translateToString(         float,       int =  7);    // zamiana float       na string z zadana precyzja
        translateToString(         double,      int = 15);    // zamiana double      na string z zadana precyzja
        translateToString(         long double, int = 15);    // zamiana long double na string z zadana precyzja

        virtual ~translateToString();           // Destruktor wirtualny zapewnia wywolanie destruktorow klas pochodnych
                                                //  dzieki temu zapobieagmy mozliwym bledom, 
                                                //  poniewaz niewywolanie destruktora klasy pochodnej moze prowadzic do np.: wyciekow pamieci



        std::string& getString();               // Mozemy 'dobrac sie' do pola _str i je potem zmieniac
        std::string  getStringCopy() const;     // Kopia pola _str

        std::string  setString(const std::string&);

        translateToString & operator= (const translateToString&);

        friend std::ostream & operator << (std::ostream&, const translateToString&);    // Wyswietlanie pola _str
    };
}

#endif

/*
    //
    // Na poczatku klasa miala zamieniac rozne typy na tablice char, jednak
    // strcpy_s nie jest w standardzie; dodatkowo latwosc implementacji stoi po stronie std::string
    //
*/