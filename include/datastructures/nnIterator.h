

class nn_iterator
{
  public:
    typedef iterator nn_iterator; //Not sure I need this.
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int difference_type;

    nn_iterator(NeuralNetwork &nn_) : nn(nn_) {}

    nn_iterator operator++(); //Prefix, increment return.
    nn_iterator operator++(int dummy); //Postfix, return increment.
    reference operator*() {return *nn;}
    pointer operator->() {return nn;}
    bool operator==(const nn_iterator &rhs) {return nn == rhs.nn;}
    bool operator!=(const nn_iterator &rhs) {return nn != rhs.nn;}

  private:
    NeuralNetwork &nn;
    LayerNode &node
};

nn_iterator operator++() //Prefix
{

}

nn_iterator operator++(int dummy) //Postfix
{

}
