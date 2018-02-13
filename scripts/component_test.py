from SFGE import *


class ComponentTest(Component):
    def __init__(self, gameObject):
        print("Init Component Test with "+str(gameObject))
        self.timer = Timer(1.0,1.0)
        
        
    def update(self, dt):
        print("Hello update from Python with dt: "+str(dt))
        self.timer.update(dt)
        if(self.timer.is_over()):
            print("Timer over, reset")
            self.timer.reset()
            
    def __del__(self):
        print("Delete ComponentTest"+str(self))