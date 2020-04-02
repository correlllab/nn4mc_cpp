#include <iostream>
#include "parser/parser_exception.h"

struct FileException : public ParserException {
    const char * what () const throw (){
        return "File Exception: ";
    }
};
