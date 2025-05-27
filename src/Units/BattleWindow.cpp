#include "../../include/BattleWindow.hpp"
#include <cmath>

// int unitsDeployedCount = 0;

/*need to change the background png, made a mistake, some rows are narrower than others*/
BattleWindow::BattleWindow()
{
	m_user1 = new User("Player 1", 0);
	m_user2 = new User("Player 2", 1);
	m_window = nullptr;
	m_turn = 0;
}

int BattleWindow::winner = 0;

void BattleWindow::deploye(sf::Event event)
{
	(void)event;
	User *user = (m_turn == 0) ? m_user1 : m_user2;
	Deck *unitDeck = user->getDeck();								// ownership with the unit
	std::shared_ptr<Unit> unitToDeploy = unitDeck->getPickedUnit(); // ownership with the unitDeck

	if (unitToDeploy == nullptr)
	{
		std::cout << "could not find picked\n";
		return;
	}

	sf::Vector2f p = unitToDeploy->getLocation() + sf::Vector2f(-85.f, 15.f);
	int col = int(p.x / 30), row = int(p.y / 30);

	unitToDeploy->setIsPicked(false);
	if (m_gameMap.getMapGrid()[row][col] != 0 || user->getElixir()->getElixir() < unitToDeploy->getCost() || !m_gameMap.isValid(row, col))
	{
		std::cout << "did not deploy, because not enought elixir\n";
		unitToDeploy->setLocation(unitToDeploy->getDeckPosition());
		return;
	}

	if (m_gameMap.getMapGrid()[row][col] == 0 && ((m_turn == 0 && col < 14) || (m_turn == 1 && col > 15)) && user->getElixir()->getElixir() > unitToDeploy->getCost())
	{

		std::cout << "\n\ndeploying unit\n\n";
		sf::Vector2f a = sf::Vector2f((col * 30) + 100, row * 30);
		unitToDeploy->setLocation(a);

		unitToDeploy->setPath(m_gameMap.aStarSearch(std::make_pair(row, col), unitToDeploy->getClosestTower()));

		unitToDeploy->setisActive(true);
		m_turn = (m_turn == 0) ? 1 : 0;
		Unit::active_units.push_back(unitToDeploy);

		user->getElixir()->decreaseElixir(unitToDeploy->getCost());

		unitToDeploy->startMovingForward();

		unitDeck->swapDeployedUnit(unitToDeploy);
	}
	unitToDeploy->setIsPicked(false);
}

void BattleWindow::selectUnit(sf::Event event)
{
	User *user = (m_turn == 0) ? m_user1 : m_user2;
	Deck *deck = user->getDeck();

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
}

int BattleWindow::runWindow()
{
	this->m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BattleWindow");
	printf("running window\n");
	while (m_window->isOpen())
	{
		m_gameClock.restart();
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(*(m_window));
		sf::Event event;

		while (m_window->pollEvent(event) && BattleWindow::winner == 0)
		{
			if (event.type == sf::Event::Closed)
				return 2;

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

		updateUnits();
		updateAttacks();
		checkCollisions();
		checkWinner();
		if (BattleWindow::winner != 0){
			m_window->close();
			return winner;
		}

		draw_all(m_window.get());
		m_user1->update(mouse_pos);
		m_user2->update(mouse_pos);
	}
	return winner;
}

void BattleWindow::checkWinner()
// checks if anybody has won, if they have then increments their win counter and increments losser's loss counter.
{
	// check if user1's tower is dead
	auto towers_1 = m_user1->getTowers();
	auto towers_2 = m_user2->getTowers();
	
	for(auto tower : towers_1){
		if (tower->getisDead()){
			BattleWindow::winner = 2;
			m_user2->setWins(m_user2->getWins() + 1);
			m_user1->setLosses(m_user1->getLosses() + 1);
			std:: cout << "winner: p2\n";
			return;
		}
	}
	for(auto tower : towers_2){
		if (tower->getisDead()){
			BattleWindow::winner = 1;
			m_user1->setWins(m_user1->getWins() + 1);
			m_user2->setLosses(m_user2->getLosses() + 1);
			std:: cout << "winner: p1\n";
			return;
		}
	}

}

void BattleWindow::updateUnits()
{
	for (size_t i = 0; i < Unit::active_units.size(); i++)
	{ // Updates all active units

		if (Unit::active_units[i]->getisActive())
		{
			startUnitAttack(Unit::active_units[i].get());
			Unit::active_units[i]->update(m_gameMap);
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
			// They are already fighting or are same alliance
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
	m_gameMap.draw(window);

	m_user1->draw(window);
	m_user2->draw(window);
	for (auto &attack_projectile : Unit::active_attacks)
	{

		if (attack_projectile != nullptr && attack_projectile->getisActive())
		{
			attack_projectile->update();
			attack_projectile->draw(window);
		}
	}

	for (auto active_unit : Unit::active_units)
		active_unit->draw(window);
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

BattleWindow::~BattleWindow()
{
	std:: cout << "Exiting battle\n";
	delete m_user1;
	delete m_user2;
}