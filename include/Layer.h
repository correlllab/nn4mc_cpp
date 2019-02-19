#ifndef _LAYER_H__
#define _LAYER_H__


#include <iostream>
#include <string>
#include <vector>

class Layer{
    private:
      std::string identifier;

    public:

      Layer(std::string id){
          this->identifier = id;
      };
};


#endif
