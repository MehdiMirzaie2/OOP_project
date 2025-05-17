#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int size = 56;
Vector2f offset(28, 28);

int cell_width = 30;
int cell_height = 30; 


int board[18][30]  = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0},
{0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0},
{0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0},
{0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0},
{0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

Sprite deck_sprites[4];
int deck_view[4] = {1,2,3,4};

void loadDeck() {
	int k = 0;
	
	for (int i = 0; i < 4; i++) {
		int card = deck_view[i];
		int x = card - 1;
		int y = 1;
		deck_sprites[i].setTextureRect(IntRect(size * x, size * y, size, size));
		deck_sprites[i].setScale(30.f / 56.f, 30.f / 56.f);
	       	deck_sprites[i].setPosition(10, (size * i) + 100);	
	}

}

int main() {
	RenderWindow window(VideoMode(1110, 560), "clash");

	Texture map_texture;
	map_texture.loadFromFile("pixil-frame-0.png");
	Sprite map_sprite(map_texture);
	map_sprite.setPosition(100, 0);


	//creating the deck
	Texture unit_textures;
	unit_textures.loadFromFile("figures.png");
	for (int i = 0; i < 4; i++) deck_sprites[i].setTexture(unit_textures);

	loadDeck();

	bool isMove = false;
	float dy = 0, dx = 0;
	int deployed_index = 0;
	Vector2f oldpos;

	while (window.isOpen()) {
		Vector2i mouse_pos = Mouse::getPosition(window); //might need to offset
		
		Event e;

		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::MouseButtonPressed) {
				if (e.key.code == Mouse::Left) {
					for (int i = 0; i < 4; i++) {
						if (deck_sprites[i].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
						{
							isMove = true;
							deployed_index = i;
							dx = mouse_pos.x - deck_sprites[i].getPosition().x;
							dy = mouse_pos.y - deck_sprites[i].getPosition().y;
							oldpos = deck_sprites[i].getPosition();
						}
					}
				}
			}

			if (e.type == Event::MouseButtonReleased) {
				if (e.key.code == Mouse::Left) {
					isMove = false;
					Vector2f p = deck_sprites[deployed_index].getPosition() + Vector2f(size / 2, size / 2);
					int row = int((p.x - 100) / cell_width), col = int((p.y) / cell_height);
						std::cout << col << " " << row << std::endl;

					if (board[col][row] == -1) {
						deck_sprites[deployed_index].setPosition(oldpos);
					}
					else {
					std::cout << (cell_width * row) + 100 << std::endl;
					Vector2f newPos = Vector2f((cell_width * row) + 100, cell_height * col);
					deck_sprites[deployed_index].setPosition(newPos);
					}
				}
			}
		}

		if (isMove)
			deck_sprites[deployed_index].setPosition(mouse_pos.x - dx, mouse_pos.y - dy);

		window.clear();
		window.draw(map_sprite);
		for (int i = 0; i < 4; i++)
			window.draw(deck_sprites[i]);
		window.display();
	}
	return 0;

}
