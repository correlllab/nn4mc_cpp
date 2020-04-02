#include <exception>
#include <iostream>

class ParserException : public std::exception
{
    public: 
        explicit ParserException(){};
        explicit ParserException (const exception&){};
        ParserException & operator= (const exception&){};
        virtual ~ParserException(){};
        virtual const char* what(){};

};
