#ifndef _GRU_
#define _GRU_

class GRU
{
    private:
        int units;
        std::string activation;
        std::string recurrent_activation;
        bool use_bias;
        float dropout;
        float recurrent dropout;
        bool go_backwards;
        bool stateful;
        bool unrool;
        bool reset_after;
    public:
};

#endif
