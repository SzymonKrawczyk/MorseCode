//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//                      Klasa translateToString (plik .cpp)                             //
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
//                                                                                      //
//  Notka: Klasa jest slabo rozbudowana,                                                //
//         w przyszlosci mozna dodac np.: settery przyjmujace wiele typow               //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////

#include "translateToString.h"

#include <sstream> // dla liczb zmiennoprzecinkowych, std::ostringstream


namespace KrawczykS {

    // Konstruktory, destruktor
    //  (niektore mozna zapisac w jednej linii, 
    //  jednak w przypadku dodania nowych pol bedzie trzeba ponownie wszystko edytowac)
    //
    // Nie mozna uniknac powtarzania kodu w kontruktorach, poniewaz np.: unsigned int nie zawsze mozna zapisac za pomoca int
    //  trzeba rownoczesnie stworzyc konstruktory dla int, long oraz long long ze wzgledu na wydajnosc pamieciowa 
    //  oraz niejednoznacznosc uzycia odpowiedniego konstruktora (do np int moze pasowac wiele konstruktorow, jak np char, long itp)
    //

        translateToString::translateToString() 
            :
                _str("")
        {}

        translateToString::translateToString(const translateToString & input_) 
            :
                _str(input_._str)
        {}


        translateToString::translateToString(std::string input_)
            :
                _str(input_)
        {}


        translateToString::translateToString(const char* input_)
            :
                _str(input_)
        {}

        translateToString::translateToString(char input_)
            :
                _str("")
        {
            _str = input_;
        }


        // Do zamiany liczb korzystamy z std::to_string()
        //
        translateToString::translateToString(int input_)
            :
                _str("")
        {
            _str = std::to_string(input_);
        }

        translateToString::translateToString(long input_)
            :
                _str("")
        {
            _str = std::to_string(input_);
        }

        translateToString::translateToString(long long input_)
            :
                _str("")
        {
            _str = std::to_string(input_);
        }


        translateToString::translateToString(unsigned int input_)
            :
            _str("")
        {
            _str = std::to_string(input_);
        }

        translateToString::translateToString(unsigned long input_)
            :
            _str("")
        {
            _str = std::to_string(input_);
        }

        translateToString::translateToString(unsigned long long input_)
            :
            _str("")
        {
            _str = std::to_string(input_);
        }


        // Liczby zmiennoprzecinkowe
        //
        //  std::to_string() do tej pory dzialalo dobrze, jednak przeszkoda w przypadku liczb zmiennoprzecinkowych
        //  jest stala wartosc precyzji (6)
        //   Aby to obejsc, stosowany jest std::ostringstream - klasa strumieni do operacji na stringach
        //          [ http://www.cplusplus.com/reference/sstream/ostringstream/ ]
        //
        //   std::ostringstream dziala podobnie do std::ostream - szczegolnie wazne jest tutaj formatowanie precyzji
        //   za pomoca precision()
        //    std::ostringstream zawiera w sobie obiekt string, do ktorego kopii mozna sie dostac za pomoca str()
        //


            // funkcja statyczna (o zasiegu jednostki translacji) pomocnicza, wychwytujaca nieprawidlowe wartosci precyzji

                namespace {

                    int checkIfGoodPrecision(int input_, int defaultValue) {
                        try {

                            if (input_ < 1) {
                                throw "Zla wartosc precyzji!\n";
                            }
                            return input_;
                        }
                        catch (const char* err) {

                            std::cout << err
                                      << "Ustawienie precyzji na " << defaultValue << "\n";
                            return defaultValue;
                        }
                    }
                }
            //

            translateToString::translateToString(float input_, int precision)
                :
                _str("")
            {
                std::ostringstream strStream;
                strStream.precision(checkIfGoodPrecision(precision, 7));
                strStream << input_;
                _str = strStream.str();
            }

            translateToString::translateToString(double input_, int precision)
                :
                    _str("")
            {
                std::ostringstream strStream;
                strStream.precision(checkIfGoodPrecision(precision, 15));
                strStream << input_;
                _str = strStream.str();
            }

            translateToString::translateToString(long double input_, int precision)
                :
                _str("")
            {
                std::ostringstream strStream;
                strStream.precision(checkIfGoodPrecision(precision, 15));
                strStream << input_;
                _str = strStream.str();
            }
        //

        translateToString::~translateToString() {}
    //


    //Gettery

        std::string& translateToString::getString()           { return _str; }

        std::string  translateToString::getStringCopy() const { return _str; }
    //


    // Settery

        std::string translateToString::setString(const std::string& input_) { _str = input_; return _str; }
    //


    // Operator =

        translateToString & translateToString::operator=(const translateToString & input_) {

            if (this != &input_) {

                _str = input_._str;

            }

            return *this;
        }
    //


    // Wyswietlanie obiektow

        std::ostream & operator << (std::ostream& O, const translateToString & obj_) { 

            O << obj_._str; 

            return O; 
        }
    //
}