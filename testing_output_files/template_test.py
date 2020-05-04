from abc  import ABC

class TemplateTest(ABC):
    def __init__(self):
        pass

    @abstractmethod:
    def passes(self) -> bool:
        pass
