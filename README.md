<img src="docs/assets/nn4mcArt.png" align="right" width=25%/>
<img align="right" src="docs/assets/MFM-logo.png" width="25%"/>

# nn4mc: Neural Networks for Microcontrollers

[![Docs](https://readthedocs.org/projects/nn4mc/badge)](https://nn4mc.readthedocs.io/en/latest/)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/correlllab/nn4mc/blob/master/LICENSE.md)

##### By the Correll Lab, University of Colorado Boulder

This repository is a generalization of the [esp 32 neural network](https://github.com/danathughes/esp32_neural_net) created by Dana Hughes.

In multiple areas of our research, we become interested in online estimation through regression or classification. Specifically, we found the need to be able to flash a microcontroller with a neural network model (which we trained offline, in a more capable computer) with a code that is easy to use, reusable and high performance for a microcontroller.  

This library is intended to be used in any microcontroller that supports C code after the neural network has been trained in a machine with Keras, Tensorflow, etc. and the parameters are saved. This enables the microcontroller to make online predictions. It is compatible with any freeRTOS code, the ESP32 and Arduino systems.

### More Information

- [Documentation](https://nn4mc.readthedocs.io/en/latest/)
- [Installation Instructions](https://nn4mc.readthedocs.io/en/latest/nn4mc_cpp/docs/installation.html)
- [Tutorials](https://github.com/correlllab/nn4mc/tree/master/examples)

### Quick Usage:

**Install**

```
$ ./scripts/setup_linux.sh 
```

```
$ ./build/h5_nn4mc --help
NN4MC Options:
  -h [ --help ]             help screen
  -s [ --source ] arg       name of the hdf5 file
  -t [ --target ] arg       name of the target folder the code will be 
                            offloaded
  -v [ --verbose ] arg (=1) print neural network configuration json
```

**Exporting code:**
```
$ ./build/h5_nn4mc --source "/path/to/hdf5" --target "path/to/output/files"	
```

### Technical Questions

Please direct your technical questions to [Stack Overflow](https://stackoverflow.com) using the [nn4mc](https://stackoverflow.com/questions/tagged/nn4mc) tag or e-mail Sarah.AguasvivasManzano@colorado.edu. Also feel free to initiate a new issue in our github repository.

### Getting Involved

- For bug report or feature requests please submit a [GitHub issue](https://github.com/correlllab/nn4mc/issues).
- For contributions please submit a [pull request](https://github.com/correlllab/nn4mc/pulls)


### Citing nn4mc:

We encourage to use the following citation references for academic use of nn4mc.

**BibTeX citation:**

```
@misc{nn4mc,
        title={Embedded Neural Networks for Robot Autonomy},
        author={Sarah {Aguasvivas Manzano} and Dana Hughes and Cooper Simpson and Radhen Patel and Nikolaus Correll},
        year={2019},
        eprint={1911.03848},
        archivePrefix={arXiv},
        primaryClass={cs.RO}
    }
```

**APA Format:**

```
Manzano, S. A., Hughes, D., Simpson, C., Patel, R., & Correll, N. (2019). Embedded Neural Networks for Robot Autonomy. arXiv preprint arXiv:1911.03848. 
```


### Contributors:

nn4mc is supported by the [Correll Lab](http://correll.cs.colorado.edu/) at the University of Colorado Boulder. We also receive support from the Airforce Office of Scientific Research (AFOSR), we are very grateful for this support. 

