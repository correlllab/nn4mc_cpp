.. nn4mc documentation master file, created by
   sphinx-quickstart on Mon Sep 23 16:28:51 2019.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. nn4mc: Neural Networks for Microcontrollers
.. ============================================

`nn4mc` is a C++ library that compiles C code for neural networks to run on off-the-shelf microcontrollers!

.. toctree::
   :maxdepth: 1
   :caption: Contents:

   installation
   usage
   dev

.. Note about Tensorflow 2.0:
.. =============================================

Make sure that the first layer in the neural network specifies the `input_shape` field when using Tensorflow 2.0 in order to get an appropriately functioning result.


.. Citing nn4mc:
.. =============


::

   Aguasvivas Manzano, Sarah, et al. “Embedded Neural Networks for Robot Autonomy.” International Symposium on Robotics Research, 2019.

Or

::

   Manzano, S. A., Hughes, D., Simpson, C., Patel, R., & Correll, N. (2019). Embedded Neural Networks for Robot Autonomy. arXiv preprint arXiv:1911.03848.

Or

::

   @misc{nn4mc,
           title={Embedded Neural Networks for Robot Autonomy},
           author={Sarah Aguasvivas Manzano and Dana Hughes and Cooper Simpson and Radhen Patel and Nikolaus Correll},
           year={2019},
           eprint={1911.03848},
           archivePrefix={arXiv},
           primaryClass={cs.RO}
       }
