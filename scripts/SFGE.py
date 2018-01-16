

class Module:
    def init(self):
        pass
    
    def update(self, dt):
        pass
    
    def destroy(self):
        pass


class SpriteManager:
    pass


class TextureManager:
    pass    


class GraphicsManager(Module):
    pass


class Engine:
    instance = None

    def __init__(self):
        self.modules = []
        instance = Engine.instance

    @staticmethod
    def get_instance():
        return Engine.instance


class GameObject:
    def __init__(self):
        self.components = []


class Component:
    def __init__(self, gameObject):
        self.gameObject = gameObject
    
    def update(self, dt):
        pass
    