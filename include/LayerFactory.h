#ifndef __LAYER_FACTORY_H__
#define __LAYER_FACTORY_H__

#include "LayerBuilder.h"

class LayerFactory{
    // Abstract Factory that instantiates LayerFactory depending on the type.
    public:
        LayerBuilder *create()=0;
};
// See src/LayerFactory.cpp for specific subclasses

#endif
