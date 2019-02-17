#ifndef _LSTM_H
#def _LSTM_H

class LSTM
{
    private:
        int units;
        std::string activation;
        std::string recursive_activation;
        bool use_bias;
        float dropout;
        float recurrent_dropout;
        int implementation;
        bool go_backwards;
        bool stateful;
        bool unroll;
    public:
};

#endif
