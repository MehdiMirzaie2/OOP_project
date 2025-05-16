#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int main() {
	RenderWindow window(VideoMode(453, 453), "mehdi");

	Texture t1;
	t1.loadFromFile("golum.png");
	Sprite s(t1);

	bool isMove = false;
	float dx = 0, dy = 0;

	while (window.isOpen()) {
		Event e;
		Vector2i pos = Mouse::getPosition(window);

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			
			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Button::Left)
					if (s.getGlobalBounds().contains(pos.x, pos.y)) {
						isMove = true;
						dx = pos.x - s.getPosition().x;
						dy = pos.y - s.getPosition().y;
					}
			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Button::Left)
					isMove = false;
		}
		if (isMove)
			s.setPosition(pos.x - dx, pos.y - dy);
		window.clear();
		window.draw(s);
		window.display();
	}
	return 0;

}
