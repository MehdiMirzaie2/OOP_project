#include "../../include/BattleWindow.hpp"

int unitsDeployedCount = 0;

BattleWindow::BattleWindow(){
    user1 = User("Adi");
    window = nullptr;
    active_units = {};
}

int BattleWindow:: runWindow() // Used prompt to do deployment (Not my part)
{
    
    Deck* unitDeck = user1.getDeck();
    std::cout << "Populating deck initially..." << std::endl;
    for(int i = 0; i < MAX_UNITS; i++){
        Unit* newUnit = director.buildSwords();
        if (newUnit) {
            unitDeck->addUnit(newUnit); // addUnit should handle current_no_units
            std::cout << "Added unit " << i << " to deck. Initial loc: " << newUnit->getLocation().x << "," << newUnit->getLocation().y << " Active: " << newUnit->getisActive() << std::endl;
        } else {
            std::cerr << "Failed to build ranger for deck population." << std::endl;
        }
    }
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "BattleWindow");
    while(window->isOpen()){
        gameClock.restart();
        sf::Event event;
        while(window->pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window->close();
            }

            if (event.type == sf::Event::MouseButtonReleased){
                if (event.mouseButton.button == sf::Mouse::Left){
                    if (unitsDeployedCount < MAX_UNITS) {
                        // Deploy the unit at index 'unitsDeployedCount'
                        Unit* unitToDeploy = unitDeck->getUnits()[unitsDeployedCount];

                        if (unitToDeploy != nullptr && !unitToDeploy->getisActive()) {
                            sf::Vector2i deployPos(event.mouseButton.x, event.mouseButton.y);
                            std::cout << "Attempting to deploy unit " << unitsDeployedCount
                                      << " at (" << deployPos.x << ", " << deployPos.y << ")" << std::endl;

                            user1.deploy(unitsDeployedCount, deployPos); // Pass index and position
                            active_units.push_back(unitToDeploy);
                            unitsDeployedCount++;
                            unitToDeploy->startMovingForward();
                            unitToDeploy->useAttack();
                            
                            std::cout << "Successfully deployed unit. Total deployed: " << unitsDeployedCount << "/" << MAX_UNITS << std::endl;
                        } else if (unitToDeploy == nullptr) {
                             std::cout << "Cannot deploy: Unit at index " << unitsDeployedCount << " is null." << std::endl;
                        }
                        // If unitToDeploy is already active, it means something is off with tracking unitsDeployedCount
                        // or units are being activated elsewhere. For this dev fix, we assume it's not active.

                    } else {
                        std::cout << "All " << MAX_UNITS << " units have been deployed. No more deployments allowed." << std::endl;
                    }
                }
            }
        }
        
        updateUnits(gameClock.getElapsedTime());
        updateAttacks();
        checkCollisions();

        window->clear(sf::Color::Black); // Clear with a distinct color for debugging
        draw_all(window);
        window->display();
    }
    return 0;
}

void BattleWindow::updateUnits(sf::Time time_passed)
{
    for(Unit* unit : active_units){ // Updates all active units
        if (unit->getisActive() && !unit->getisDead()){
            unit->update(time_passed);
        }
    }
}

void BattleWindow::updateAttacks()
{
    for(Attack* attack : Unit::active_attacks){
        attack->update();
    }
}

void BattleWindow::draw_all(sf::RenderWindow* window){
    gameMap.draw(window);
    
    user1.draw(window);   

    for (Attack* attack_projectile : Unit::active_attacks) {
        if (attack_projectile != nullptr && attack_projectile->getisActive()) {
            attack_projectile->draw(window);
        }
    }
}

void BattleWindow::checkCollisions()
{
    for(long unsigned int i = 0; i < Unit::active_attacks.size(); i++)
    {
        if (Unit::active_attacks[i]->isHit(active_units)){
            std:: cout << "Attack hit detected\n";
        };
    }
}

