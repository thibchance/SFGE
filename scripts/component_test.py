from SFGE import *


class ComponentTest(Component):
    def __init__(self, gameObject):
        print("Init Component Test with "+str(gameObject))
        
    def update(self, dt):
        print("Hello update from Python with dt: "+str(dt))