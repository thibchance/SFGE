#include <SFML/Audio.hpp>

int main()
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("data/audio/sounds/Laser.ogg"))
		return -1;
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	system("pause");
	return EXIT_SUCCESS;

}