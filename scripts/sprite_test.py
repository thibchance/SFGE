from SFGE import *


class SpriteTest(Component):
    def __init__(self, game_object):
        Component.__init__(self, game_object)
        self.speed = 4.0
        self.direction = Vector2f(2.0, 4.0)
        
    def update(self, dt):
        print("Update from python sprite_test")
        current_pos = self.game_object.transform.get_position()
        delta_pos = self.direction*self.speed*dt
        self.game_object.transform.set_position(current_pos+delta_pos)