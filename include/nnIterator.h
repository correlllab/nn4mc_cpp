

class nn_iterator : std::iterator<random_access_iterator_tag,
                                                LayerNode,
                                                std::ptrdiff_t,//Maybe vector?
                                                LayerNode*,
                                                LayerNode&>
{


public:
  nn_iterator ();

}
