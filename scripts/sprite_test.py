from SFGE import *
import sys


class SpriteTest(Component):
    def __init__(self, game_object):
        Component.__init__(self, game_object)
        print("__init__ SpriteTest with gameObject: "+str(game_object))

    def init(self):
        #print("Init SpriteTest with "+str(self.game_object))
        self.speed = 4.0
        self.direction = Vector2f(2.0, 4.0)
        
    def update(self, dt):
        print("Update from python sprite_test")
        current_pos = self.game_object.transform.get_position()
        delta_pos = self.direction*self.speed*dt
        self.game_object.transform.set_position(current_pos+delta_pos)
    
    def __del__(self):
        sys.stderr.write("DELETING SPRITE TEST PYTHON\n")
        sys.stderr.flush()