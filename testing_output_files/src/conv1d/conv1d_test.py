import conv1d as layer
from testing_output_files.template_test import TemplateTest

class Conv1DTest(TemplateTest):
    """
        Conv1D
    """
    def __init__(self, layer):
        self.layer = layer
    def generate_sample(self):
        pass

    def test_build(self) -> bool:
        pass

    def test_fwd(self) -> bool:
        pass

    def passes(self) -> bool:
        # returns (test_sigmoid and test_hard_sigmoid and ...)
        pass

if __name__=='__main__':
    c1d = Conv1DTest(layer)
