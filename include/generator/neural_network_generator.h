#include <string>
#include <map>


#ifndef __NEURAL_NETWORK_GENERATOR_H__
#define __NEURAL_NETWORK_GENERATOR_H__

class NNGenerator
{
    private:
    
        std::string include_template_path;
		std::string src_template_path;
    
        void loadTemplates();
        
    public:
    
        NNGenerator();
        ~NNGenerator();
        
        void dump();

};

#endif