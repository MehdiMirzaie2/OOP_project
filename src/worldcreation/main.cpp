#include <SFML/Graphics.hpp>
using namespace sf;


Sprite f[32];
std::string position = "";
Vector2f offset(28, 28);
int size = 56;

int board[8][8] = {
	-1, -2, -3, -4, -5, -3, -2, -1,
	-6, -6, -6, -6, -6, -6, -6, -6,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	6, 6, 6, 6, 6, 6, 6, 6,
	1, 2, 3, 4, 5, 3, 2, 1,
};

//void move(std::string str) {
	//Vector2f old
	
void loadPosition() {
	int k = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++) {
			int n = board[i][j];
			if (!n)
				continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			f[k].setTextureRect(IntRect(size * x, size * y, size, size));
			f[k].setPosition(size * j, size * i);
			k++;
		}
//	for (int i = 0; i < position.length(); i += 5)
//		move(position.substr(i, 4));
}


int main() {
	RenderWindow window(VideoMode(454, 455), "the game");

	Texture t1, t2;

//	t1.loadFromFile("figures.png");
	t2.loadFromFile("board0.png");

//	for (int i = 0; i < 32; i++) f[i].setTexture(t1);
	Sprite sBoard(t2);

//	loadPosition();

	while (window.isOpen()) {
//		Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);

		Event e;

		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sBoard);
//		for (int i = 0; i < 32; i++)
//			window.draw(f[i]);
		window.display();
	}
	return 0;
}

