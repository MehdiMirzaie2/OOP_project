#include "../../include/User.hpp"

User::User() {};

User::User(std::string name, int left_or_right)
{
    m_name = name;
    m_wins = 0;
    m_losses = 0;
    // towers = {nullptr};
    m_unitDeck = std::make_unique<Deck>(left_or_right);

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
        //m_towers[0]->dead();
        m_towers[1]->setLocation(bottom_left);
        
        m_towers[0]->setDeckPosition(sf::Vector2f(3, 7));
        m_towers[1]->setDeckPosition(sf::Vector2f(14, 7));
        std::cout << "Left tower alliance: " << m_towers[0]->getAlliance() << " " << m_towers[1]->getAlliance() << std::endl;
    }
    else
    {
        m_towers[0]->setLocation(top_right);
        //m_towers[0]->dead();
        m_towers[1]->setLocation(bottom_right);
    }

    Unit::active_units.push_back(m_towers[0]);
    Unit::active_units.push_back(m_towers[1]);
    // Unit::active_units.push_back(m_king);
    m_elixir = std::make_unique<Elixir>();
}

Elixir *User::getElixir()
{
    return m_elixir.get();
}

std::array<std::shared_ptr<Unit>,2> User::getTowers(){
    return m_towers;
};


void User::update(sf::Vector2i mouse_pos)
{
    m_elixir->update();

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
