//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                      Klasa morse (plik .cpp)                                         //
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
//              | Dodanie obslugi manipulatorow                     |                   //
//              | Dodanie manipulatora pause                        |                   //
//              | Dodanie debugowania                               |                   //
//              |                                                   |                   //
//  20/11/2019  | Dodanie komentarzy                                | Szymon Krawczyk   //
//              | Zmiana setterow na zwracanie wartosci obiektu     |                   //
//              |                                                   |                   //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#include "morse.h"

#include <cctype>   // tolower()
#include <iostream> // do debugowania

namespace KrawczykS {


    // Stale do debugowania

        namespace { 
            // nienazwana przestrzen nazw daje pewnosc, ze bedzie widoczna tylko w tej jednostkce translacji

            const char DebugMorseSymbol_Dot        = '.';    // symbol wyswietlany podczas czytania .
            const char DebugMorseSymbol_Dash       = '-';    // symbol wyswietlany podczas czytania -
            const char DebugMorseSymbol_Pause      = 'x';    // symbol wyswietlany pomiedzy . oraz - w pojedynczym symbolu
            const char DebugMorseSymbol_CharPause  = '0';    // symbol wyswietlany podczas czytania spacji oraz po kazdej sekwencji . oraz - w symbolu
            const char DebugMorseSymbol_Unknown    = '#';    // symbol wyswietlany podczas czytania niezaimplementowanego symbolu
            const char DebugMorseSymbol_PauseManip = 'Q';    // symbol wyswietlany w funkcji pause
        }
    //



    // Konstruktory i dektruktor

        morse::morse()
            :
                frequency (0)
            ,   dotTime   (0)
            ,   dashTime  (0)
            ,   pause     (0)
            ,   charPause (0)
            ,   showDebug (false)
        {}

        morse::morse(const morse & inputMorse_)
            :
                frequency (inputMorse_.frequency)
            ,   dotTime   (inputMorse_.dotTime)
            ,   dashTime  (inputMorse_.dashTime)
            ,   pause     (inputMorse_.pause)
            ,   charPause (inputMorse_.charPause)
            ,   showDebug (inputMorse_.showDebug)
        {}

        morse::~morse() {}
    //

    // Operator =

        morse & morse::operator=(const morse & inputMorse_) {

            if (this != &inputMorse_) {

                frequency = inputMorse_.frequency;
                dotTime   = inputMorse_.dotTime;
                dashTime  = inputMorse_.dashTime;
                pause     = inputMorse_.pause;
                charPause = inputMorse_.charPause;
                showDebug = inputMorse_.showDebug;
            }       

            return *this;
        }
    //


    // Settery

        int morse::setFrequency(const int  input_) { 

            try {

                if (input_ <= 0x25 || input_ >= 0x7FFF) {   // Zakres wartosci z dokumentacji funkcji Beep()
                                                            //  https://docs.microsoft.com/en-gb/windows/win32/api/utilapiset/nf-utilapiset-beep?redirectedfrom=MSDN

                    throw "\nNieprawidlowa wartosc czestotliwosci (musi byc w przedziale (37 - 32767))\n";
                }
                frequency = input_;
            }
            catch (const char* err) {

                std::cout << err
                          << "Zmiana frequency na 1000Hz\n";
                frequency = 1000;
            }
            return frequency;    // Zwraca ostateczna czestotliwosc obiektu
        }


        // funkcja statyczna (o zasiegu jednostki translacji) pomocnicza, wychwytujaca nieprawidlowe wartosci czasu

            namespace {

                int checkIfGoodTimeInput(int toCheck, int defaultIfBad) {

                    try {

                        if (toCheck <= 0) {
                            throw "\nNieprawidlowa wartosc czasu (musi byc wieksza od 0)\n";
                        }
                        return toCheck;
                    }
                    catch (const char* err) {

                        std::cout << err
                            << "Zmiana wartosci na " << defaultIfBad << "ms\n";
                        return defaultIfBad;
                    }
                }
            }
        //

        int  morse::setDotTime  (int  input_) { dotTime   = checkIfGoodTimeInput(input_, 100); return dotTime; }

        int  morse::setDashTime (int  input_) { dashTime  = checkIfGoodTimeInput(input_, 200); return dashTime; }

        int  morse::setPause    (int  input_) { pause     = checkIfGoodTimeInput(input_,  50); return pause; }

        int  morse::setCharPause(int  input_) { charPause = checkIfGoodTimeInput(input_, 100); return charPause; }

        bool morse::setShowDebug(bool input_) { showDebug = input_; return showDebug;}
    //


    // Gettery

        int  morse::getFrequency() const { return frequency; }

        int  morse::getDotTime()   const { return dotTime; }

        int  morse::getDashTime()  const { return dashTime; }

        int  morse::getPause()     const { return pause; }

        int  morse::getCharPause() const { return charPause; }

        bool morse::getShowDebug() const { return showDebug; }
    //


    // Obsluga strumienia

        morse & operator<<(morse & m, const translateToString & input_) {

            std::string strTemp = input_.getStringCopy();

            for (int i = 0; strTemp[i]; i++) {

                toBeep(m, strTemp[i]);  // wypikuje znak
                Sleep(m.charPause);     // przerwa pomiedzy znakami

                if (m.showDebug) {
                    std::cout << DebugMorseSymbol_CharPause; // debug
                }
            }

            return m;
        }


        void toBeep(const morse& m,  char input_) {

            std::string symbol = "";

            // Ponizsza instrukcja switch zostala skopiowana a nastepnie zmodyfikowana ze strony:
            // [ http://www.cplusplus.com/forum/beginner/209405/2/#msg985465 ]
            //

            switch (toupper(input_)) {
            
                case 'A': symbol = ".-";     break;
                case 'B': symbol = "-...";   break;
                case 'C': symbol = "-.-.";   break;
                case 'D': symbol = "-..";    break;
                case 'E': symbol = ".";      break;
                case 'F': symbol = "..-.";   break;
                case 'G': symbol = "--.";    break;
                case 'H': symbol = "....";   break;
                case 'I': symbol = "..";     break;
                case 'J': symbol = ".---";   break;
                case 'K': symbol = "-.-";    break;
                case 'L': symbol = ".-..";   break;
                case 'M': symbol = "--";     break;
                case 'N': symbol = "-.";     break;
                case 'O': symbol = "---";    break;
                case 'P': symbol = ".--.";   break;
                case 'Q': symbol = "--.";    break;
                case 'R': symbol = ".-.";    break;
                case 'S': symbol = "...";    break;
                case 'T': symbol = "-";      break;
                case 'U': symbol = "..-";    break;
                case 'V': symbol = "...-";   break;
                case 'W': symbol = ".--";    break;
                case 'X': symbol = "-..";    break;
                case 'Y': symbol = "-.-";    break;
                case 'Z': symbol = "--.";    break;

                case ' ': symbol = " ";      break;

                case '0': symbol = "-----";  break;
                case '1': symbol = ".----";  break;
                case '2': symbol = "..---";  break;
                case '3': symbol = "...--";  break;
                case '4': symbol = "....-";  break;
                case '5': symbol = ".....";  break;
                case '6': symbol = "-....";  break;
                case '7': symbol = "--...";  break;
                case '8': symbol = "---..";  break;
                case '9': symbol = "----.";  break;

                case ',': symbol = "--..--"; break;
                case '.': symbol = ".-.-.-"; break;
                case '?': symbol = "..--.."; break;
                case '!': symbol = "-.-.--"; break;

                case '+': symbol = ".-.-.";  break;
                case '-': symbol = "-....-"; break;

                default:  symbol = "#";      break;
            }

            for (int i = 0; symbol[i]; i++) {

                switch (symbol[i]) {



                case '.':

                    Beep(m.frequency, m.dotTime);

                    if (m.getShowDebug()) {
                        std::cout << DebugMorseSymbol_Dot;          // debug
                    }

                    if (i != symbol.size() -1) {    // jezeli to ostania . nie wstawiaj przerwy

                        Sleep(m.pause);             // przerwa pomiedzy kropkami i kreskami w danym znaku

                        if (m.getShowDebug()) {
                            std::cout << DebugMorseSymbol_Pause;    // debug
                        }
                    }

                    break;



                case '-':

                    Beep(m.frequency, m.dashTime);

                    if (m.getShowDebug()) {
                        std::cout << DebugMorseSymbol_Dash;         // debug
                    }

                    if (i != symbol.size() -1) {    // jezeli to ostania - nie wstawiaj przerwy

                        Sleep(m.pause);             // przerwa pomiedzy kropkami i kreskami w danym znaku

                        if (m.getShowDebug()) {
                            std::cout << DebugMorseSymbol_Pause;    // debug
                        }
                    }

                    break;



                case ' ':

                    Sleep(m.charPause);

                    if (m.getShowDebug()) {
                        std::cout << DebugMorseSymbol_CharPause;    // debug
                    }

                    break;



                case '#':

                    Sleep(m.charPause);

                    if (m.getShowDebug()) {
                        std::cout << DebugMorseSymbol_Unknown;      // debug
                    }

                    break;



                }
            }
        }


        morse & operator << (morse& m, void (*pt)(morse&)) {  // obsluga napotkanych funkcji

            pt(m);      // wywolanie napotkanej funkcji na rzecz danego obiektu morse
            return m; 
        }
    //


    // Manipulatory (funkcje)

        void pause(morse& m) {

            Sleep(m.getCharPause());

            if (m.getShowDebug()) {
                std::cout << DebugMorseSymbol_PauseManip;           // debug
            }
        }
    //
}