import sys, os
sys.path.append(os.path.join(os.environ['HOME'], 'nn4mc'))

import conv1d as layer
from testing_output_files.template_test import TemplateTest
import tensorflow as tf
import numpy as np
import unittest

class Conv1DTest(TemplateTest, unittest.TestCase):
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

    def generate_sample(self, input_dims):
        return np.random.normal(0.0, 20, size = input_dims)

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

    def __c_fwd(self, build_dict : dict, input_, weight, bias):
        layer = self.layer.buildConv1D(weight[0], bias[0], \
                        build_dict['kernel_size'], build_dict['strides'], \
                        input_.shape[1], input_.shape[2], build_dict['filters'], \
                        self.activation_dictionary[build_dict['activation']], \
                        self.padding_dictionary[build_dict['padding']], \
                        self.dataformat_dictionary[build_dict['data_format']], \
                        build_dict['dilation_rate'])
        return self.layer.fwdConv1D(layer, input_.flatten().tolist())

    def __keras_fwd(self, config_dict : dict, input_, weight, bias):
        layer = self.__keras_build(config_dict)
        layer.w = tf.Variable(weight)
        layer.b = tf.Variable(bias)
        return layer(input_)

    def test_fwd(self) -> bool:
        batch_size = 1
        N = 100
        for _ in range(N):
            build_dict = {'filters': 32, 'kernel_size' : 3, 'strides' : 1, 'padding' : 'valid', \
                    'data_format' : 'channels_last', 'dilation_rate' : 1, 'activation' : 'linear', \
                    'use_bias' : True}

            shape = np.random.randint(100, size = 2).tolist()

            input_dims = (batch_size, shape[0] , shape[1])

            weight = np.random.normal(0.0, 20., size = (build_dict['kernel_size'],\
                                            input_dims[-1], build_dict['filters'])).astype(np.float32)
            bias = np.random.normal(0.0, 20, size = (build_dict['filters'])).astype(np.float32)

            input_ = self.generate_sample(input_dims)

            self.assertEqual(self.__c_fwd(build_dict, input_, weight.flatten().tolist(),\
                        bias.flatten().tolist()), self.__keras_fwd(build_dict, input_, weight, bias))

    def passes(self) -> bool:
        # returns (test_sigmoid and test_hard_sigmoid and ...)
        pass

if __name__=='__main__':
    c1d = Conv1DTest(layer)
    print(c1d.test_fwd())
