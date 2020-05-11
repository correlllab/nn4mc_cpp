import conv1d as layer
from testing_output_files.template_test import TemplateTest
import tensorflow as tf
import numpy as np

class Conv1DTest(TemplateTest):
    """
        Conv1D
    """
    def __init__(self, layer):
        self.layer = layer
        self.activation_dictionary = {'softmax' : 0x00,
                'elu' : 0x02, 'selu' : 0x03,
                'softplus' : 0x04, 'softsign' : 0x05,
                'relu' : 0x06, 'tanh' : 0x07, 'sigmoid' : 0x08,
                'hard_sigmoid' : 0x09, 'exponential' : 0xA, 'linear' : 0xB,
                'custom' : 0xC}

        self.padding_dictionary = {'valid' : 0x00, 'causal' : 0x02, 'same' : 0x03}

        self.dataformat_dictionary = {'channels_last' : 0x00, 'channels_first' : 0x02}

    def generate_sample(self):
        pass

    def __c_build(self):
        pass

    def __keras_build(self, build_dict : dict):
        return tf.keras.layers.Conv1D(
                    filters = build_dict['filters'],
                    kernel_size = build_dict['kernel_size'],
                    strides = build_dict['strides'],
                    padding = build_dict['padding'],
                    data_format = build_dict['data_format'],
                    dilation_rate =  build_dict['dilation_rate'],
                    activation = build_dict['activation'],
                    use_bias = build_dict['use_bias']
                    )

    def __c_fwd(self, build_dict : dict):
        return buildConv1D()

    def __keras_fwd(self, config_dict : dict):

        pass

    def test_fwd(self) -> bool:
        pass

    def passes(self) -> bool:
        # returns (test_sigmoid and test_hard_sigmoid and ...)
        pass

if __name__=='__main__':
    c1d = Conv1DTest(layer)
    print(dir(c1d.layer))
