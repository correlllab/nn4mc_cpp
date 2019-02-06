#include <iostream>
#include <string>
#include <vector>

class Weights {
    private:
        std::vector<int> dimensions;
        std::string identifier;

    public:
        virtual void Weights() = 0; // making this an abstract class

        virtual void loadWeights{
            //Cooper's TODO. 
        }

        Weights(std::vector<int> dims, std::string id){ 
            // common non-abstract constructor
            this.identifier= id;
            for(int i=0; i<dims.size(); i++){
                this.dimensions.push_back(dims.at[i]);
            }
        } 
};


class Weight2D : public Weights{
    public:

        virtual void Weight2D() = 0;

        virtual void loadWeights(){
            //Cooper's TODO.
        }

};

class Weight3D : public Weights{
    public:
        virtual void Weight2D() = 0;

        virtual void loadWeights(){
            //Cooper's TODO.
        } 

};

class Weight4D : public Weights{
    public:
        virtual void Weight4D() = 0;

        virtual void loadWeights(){
            //Cooper's TODO
        }

};
