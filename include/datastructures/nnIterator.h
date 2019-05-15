

class nn_iterator
{
  public:
    typedef LayerNode value_type;
    typedef LayerNode& reference;
    typedef LayerNode* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef void difference_type; //Doesnt really make sense in this case to have anything else.

    nn_iterator(NeuralNetwork* nn_, LayerNode* node_) : nn(nn_), node(node_) {}
    nn_iterator() {}

    nn_iterator& operator++(); //Prefix, increment return.
    nn_iterator operator++(int dummy); //Postfix, return increment.
    reference operator*() {return *node;} //Needs to be diferent
    // pointer operator->() {return nn;} //Needs to be diferent
    nn_iterator& operator=(const nn_iterator &rhs) {nn = rhs.nn; node = rhs.node; return *this;}
    bool operator==(const nn_iterator &rhs) {return (nn == rhs.nn && node == rhs.node);}
    bool operator!=(const nn_iterator &rhs) {return (nn != rhs.nn || node != rhs.node);}

  private:
    NeuralNetwork* nn;
    LayerNode* node
};

nn_iterator operator++() //Prefix
{

}

nn_iterator operator++(int dummy) //Postfix
{

}
