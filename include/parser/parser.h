#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <string>

class Parser{
    // Abstract class for parser obejcts.
    // Any parser (h5 or picke) should inherit from this
    public: 
            std::string file_format;
            std::string file_name;
            virtual int parse() = 0;
            virtual ~Parser() = default;
};


#endif
