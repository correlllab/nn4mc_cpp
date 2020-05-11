from abc  import ABC, abstractmethod

class TemplateTest(ABC):
    def __init__(self):
        pass

    @abstractmethod
    def passes(self) -> bool:
        pass
