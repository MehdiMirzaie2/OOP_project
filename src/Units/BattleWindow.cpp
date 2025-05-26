#include "../../include/BattleWindow.hpp"
#include <cmath>

int unitsDeployedCount = 0;

/*need to change the background png, made a mistake, some rows are narrower than others*/

/*need to change the background png, made a mistake, some rows are narrower than others*/

BattleWindow::BattleWindow()
{
	user1 = User("Adi", 0);
	user2 = User("Mehdi", 1);
	window = nullptr;
	m_turn = 0;
}

void BattleWindow::deploye(sf::Event event)
{
	std::cout << "this is user " << m_turn << "\n";
	(void)event;
	User *user = (m_turn == 0) ? &user1 : &user2;
	Deck *unitDeck = user->getDeck();				// ownership with the unit
	Unit *unitToDeploy = unitDeck->getPickedUnit(); // ownership with the unitDeck

	if (unitToDeploy == nullptr)
	{
		std::cout << "could not find picked\n";
	}

	if (unitToDeploy != nullptr)
	{
		// sf::Vector2f p = sf::Vector2f(event.mouseButton.x, event.mouseButton.y) + sf::Vector2f(15.f - 100.f, 15.f);
		sf::Vector2f p = unitToDeploy->getLocation() + sf::Vector2f(-85.f, 15.f);
		int col = int(p.x / 30), row = int(p.y / 30);
		// int col = (event.mouseButton.x - 100) / 30, row = event.mouseButton.y / 30;
		std::cout << "current pos = " << row << " " << col << "\n";
		unitToDeploy->setIsPicked(false);
		if (gameMap.getMapGrid()[row][col] != 0 || user->getElixir()->getElixir() < 1)
		{
			std::cout << "did not deploy, because not enought\n";
			unitToDeploy->setLocation(unitToDeploy->getDeckPosition());
			return;
		}

		if (gameMap.getMapGrid()[row][col] == 0 && ((m_turn == 0 && col < 14) || (m_turn == 1 && col > 15)) && user->getElixir()->getElixir() > 0)
		{
			sf::Vector2f a = sf::Vector2f((col * 30) + 100, row * 30);
			unitToDeploy->setLocation(a);

			Unit::active_units.push_back(std::shared_ptr<Unit>(unitToDeploy));
			unitsDeployedCount++;
			unitToDeploy->startMovingForward();
			unitToDeploy->setPath(gameMap.aStarSearch(std::make_pair(row, col), unitToDeploy->getClosestTower()));

			unitToDeploy->setisActive(true);
			m_turn = (m_turn == 0) ? 1 : 0;
			num_deployed[m_turn]++;
			gameMap.getMapGrid()[row][col] = 2; // should be enums
			user->getElixir()->decreaseElixir(3);

			// active_units.push_back(unitToDeploy);
			unitsDeployedCount++;
			unitToDeploy->startMovingForward();
			// unitToDeploy->useAttack();

			std::cout << "\n\n\ndepoyed unit\n\n\n\n";
		}
	}
}

void BattleWindow::selectUnit(sf::Event event)
{
	//(void)event;
	User *user = (m_turn == 0) ? &user1 : &user2;
	Deck *deck = user->getDeck();

	// sf::Vector2i mouse_pos = sf::Mouse::getPosition(this-window);
	std::cout << "sellecting units\n";

	std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
	for (auto unit : deck->getUnits())
	{
		// std::cout << "checking if sprte was slected\n";
		sf::Sprite sprite = unit->getSprite();
		std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
		if (sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		{
			unit->setIsPicked(true);
			std::cout << "updated location for a unit\n";

			sf::Vector2i dydx(
				event.mouseButton.x - sprite.getPosition().x,
				event.mouseButton.y - sprite.getPosition().y);
			unit->setDydx(dydx);
			break;
		}
	}
	std::cout << "\n\n";
}

int BattleWindow::runWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BattleWindow");
	int winner = 0;
	while (window->isOpen() && !winner)
	{
		gameClock.restart();
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(*(this->window));
		sf::Event event;

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					selectUnit(event);
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					deploye(event);
				}
			}
		}

		// updateUnits(gameClock.getElapsedTime());
		updateUnits();
		updateAttacks();
		checkCollisions();
		checkWinner(int& winner);

		draw_all(window.get());
		user1.update(mouse_pos);
		user2.update(mouse_pos);

	}
	return winner;
}

void BattleWindow::checkWinner(int& winner)
{
	if (user1.getKing()->getisDead()){
		winner = 2;
	}
	else if(user2.getKing()->getisDead()){
		winner = 1;
	}
}

void BattleWindow::updateUnits()
{
	for (size_t i = 0; i < Unit::active_units.size(); i++)
	{ // Updates all active units

		if (Unit::active_units[i]->getisActive())
		{

			startUnitAttack(Unit::active_units[i].get());
			Unit::active_units[i]->update(gameMap);
		}
		else
		{
			Unit::active_units.erase(Unit::active_units.begin() + i);
			i--;
		}
	}
}

void BattleWindow::startUnitAttack(Unit *attacker)
{
	for (auto &unit : Unit::active_units)
	{
		auto unit_ptr = unit.get();
		if (unit_ptr == attacker || attacker->getisDead() || unit_ptr->getisDead() || attacker->getTarget() == unit_ptr || unit_ptr->getAlliance() == attacker->getAlliance())
		{
			// They are already fighting
			continue;
		}
		sf::Vector2f attacker_loc = attacker->getLocation();
		sf::Vector2f target_loc = unit_ptr->getLocation();
		float distance = std::sqrt((attacker_loc.x - target_loc.x) * (attacker_loc.x - target_loc.x) + (attacker_loc.y - target_loc.y) * (attacker_loc.y - target_loc.y));

		if (abs(distance) <= attacker->getRadius_of_attack())
		{
			attacker->useAttack(unit_ptr);
		}
	}
}

void BattleWindow::updateAttacks()
{
	for (auto &attack : Unit::active_attacks)
	{
		attack->update();
	}
}

void BattleWindow::draw_all(sf::RenderWindow *window)
{
	window->clear();
	gameMap.draw(window);

	user1.draw(window);
	user2.draw(window);
	for (auto &attack_projectile : Unit::active_attacks)
	{

		if (attack_projectile != nullptr && attack_projectile->getisActive())
		{
			attack_projectile->update();
			attack_projectile->draw(window);
		}
	}
	window->display();
}

void BattleWindow::checkCollisions()
{
	for (size_t i = 0; i < Unit::active_attacks.size(); i++)
	{

		if (Unit::active_attacks[i]->isHit(Unit::active_units))
		{
			std::cout << "Attack hit detected\n";
		};
	}
}
