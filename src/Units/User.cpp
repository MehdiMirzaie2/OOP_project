#include "../../include/User.hpp"
#include <iostream>

User::User() {};

User::User(std::string name)
{
    m_name = name;
    m_wins = 0;
    m_losses = 0;
    // towers = {nullptr};
    m_unitDeck = std::make_unique<Deck>();
    m_king = m_unitDeck->generateKing(0);

    sf::Sprite king_sprite = m_king->getSkin();
    sf::Vector2f current_scale = king_sprite.getScale();
    king_sprite.setScale(current_scale.x * 5, current_scale.y * 5);

    m_king->describe();
    m_elixir = std::make_unique<Elixir>();
}

User::User(std::string name, int left_or_right)
{
    m_name = name;
    m_wins = 0;
    m_losses = 0;
    // towers = {nullptr};
    m_unitDeck = std::make_unique<Deck>(left_or_right);

    m_king = std::shared_ptr<Unit>(m_unitDeck->generateKing(left_or_right));
    sf::Sprite king_sprite = m_king->getSkin();
    sf::Vector2f current_scale = king_sprite.getScale();
    int flip = left_or_right == 0 ? 1 : -1;

    std::cout << "current scale: " << current_scale.x << std::endl;
    king_sprite.setScale(flip * current_scale.x * 5.f, current_scale.y * 5.f);
    std::cout << "current scale: " << king_sprite.getScale().x << std::endl;

    m_king->setSkin(king_sprite);
    m_king->setisActive(true);
    m_king->setisTower(true);

    m_king->describe();

    if (left_or_right == 0){
        std:: cout << "Left king alliance: " << m_king->getAlliance() << std::endl;
    }

    for (int i = 0; i < 2; i++)
    {
        m_towers[i] = std::shared_ptr<Unit>(m_unitDeck->generateTowers(left_or_right));
        sf::Sprite skin = m_towers[i]->getSkin();
        sf::Vector2f current_scale = skin.getScale();
        skin.setScale(current_scale.x * 3.f, current_scale.y * 3.f);
        m_towers[i]->setSkin(skin);
        m_towers[i]->setisActive(true);
        m_towers[i]->setisTower(true);
    }
    float offset = 8;
    sf::Vector2f top_left(WINDOW_WIDTH / 4.5 - offset, WINDOW_HEIGHT / 6 - 3*offset);
    sf::Vector2f top_right(WINDOW_WIDTH - WINDOW_WIDTH / 4.5 + offset, WINDOW_HEIGHT / 6 - 3*offset);
    sf::Vector2f bottom_left(WINDOW_WIDTH / 4.5 - offset, WINDOW_HEIGHT - WINDOW_HEIGHT / 6 - 7*offset);
    sf::Vector2f bottom_right(WINDOW_WIDTH - WINDOW_WIDTH / 4.5 + offset, WINDOW_HEIGHT - WINDOW_HEIGHT / 6 - 7*offset);

    if (left_or_right == 0)
    {
        m_towers[0]->setLocation(top_left);
        m_towers[1]->setLocation(bottom_left);
        
        std::cout << "Left tower alliance: " << m_towers[0]->getAlliance() << " " << m_towers[1]->getAlliance() << std::endl;
    }
    else
    {
        m_towers[0]->setLocation(top_right);
        m_towers[1]->setLocation(bottom_right);
    }

    Unit::active_units.push_back(m_towers[0]);
    Unit::active_units.push_back(m_towers[1]);
    Unit::active_units.push_back(m_king);
    m_elixir = std::make_unique<Elixir>();
}

User::~User() {

    if (m_elixir) delete m_elixir;
    if (unitDeck) delete unitDeck;

    delete m_elixir;
    delete unitDeck; 
}

Elixir *User::getElixir()
{
    return m_elixir.get();
}

void User::update(sf::Vector2i mouse_pos)
{
    m_elixir->update();
    elixirBar.update(m_elixir->getElixir());

    for (const auto &unit : m_unitDeck->getUnits())
    {
        unit->moveIfPicked(mouse_pos);
    }
}

void User::setLosses(int l)
{
    m_losses = l;
}

void User::setWins(int w)
{
    m_wins = w;
}

void User::setName(std::string new_name)
{
    m_name = new_name;
}

int User::getWins() { return m_wins; }
int User::getLosses() { return m_losses; }
std::string User::getName() { return m_name; }

void User::draw(sf::RenderWindow *window)
{
    m_unitDeck->draw(window);
    m_king->draw(window);

    for (auto &tower : m_towers)
    {
        tower->draw(window);
    }
}


// need to change to smart ptr
Deck *User::getDeck()
{
    return m_unitDeck.get();
}
/*
void User::deploy(int index, sf::Vector2f dep_loc)
{
    int col = dep_loc.x / 30, row = dep_loc.y / 30;
    std::cout << row << " " << col << std::endl;
    Unit* unit = unitDeck->getUnits()[index].get();
    //sf::Vector2i screen_pos = sf::Vector2i(30 * dep_loc.x, 30 * dep_loc * 30);
    //dep_loc.x *= 30;
    //dep_loc.y *= 30;
    sf::Vector2f a = sf::Vector2f(col * 30, row * 30);
    unit->setLocation(a);
    std:: cout << "UNITS LOCATION: " << unit->getLocation().x << std::endl;
    unit->setisActive(true);
}

*/
