
class Timer:
    def __init__(self, time, period):
        pass
    
    def reset(self):
        pass
    
    def update(self, dt):
        pass
    
    def get_current(self):
        pass
    
    def get_current_time(self):
        pass
    
    def is_over(self):
        pass

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

    def __init__(self):
        self.modules = []
    


class GameObject:
    def __init__(self):
        self.components = []


class Component:
    def __init__(self, gameObject):
        self.gameObject = gameObject
    
    def update(self, dt):
        pass
    
engine = Engine()
    