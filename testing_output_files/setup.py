#! /usr/bin/env python
"""
    Code file taken from https://scipy-cookbook.readthedocs.io/items/SWIG_NumPy_examples.html
"""
# System imports
from distutils.core import *
from distutils      import sysconfig

# Third-party modules - we depend on numpy for everything
import numpy

# Obtain the numpy include directory.  This logic works across numpy versions.
try:
    numpy_include = numpy.get_include()
except AttributeError:
    numpy_include = numpy.get_numpy_include()

# ezrange extension module
_ezrange = Extension("",
                   ["",""],
                   include_dirs = [numpy_include],
                   )

# ezrange setup
setup(  name        = "range function",
        description = "range takes an integer and returns an n element int array where each element is equal to its index",
        author      = "nn4mc",
        version     = "1.0",
        ext_modules = [_ezrange]
        )
