#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include "Drawable.hpp"

class Weapon : public Drawable
// modifies the unit's damage/range and cost on the basis of the weapon chosen, gun increases radius atk
{
    private:
        std::string name; // The identifying name of the weapon (e.g., "Iron Sword", "Longbow").
        float damageModifier; // Factor or flat value to modify unit's base damage.
        float rangeModifier; // Factor or flat value to modify unit's attack range/radius.
        int costModifier; // Value to add to the unit's deployment cost.
        sf::Texture weaponTextureSheet; // The sprite sheet containing all frames for the weapon.
        sf::Sprite currentSprite; // The current visual sprite of the weapon to be drawn.
        std::string attackTypeCompatibility; // Specifies the type of attack this weapon is suited for (e.g., "Melee", "Ranged").    
        std::map<std::string, std::vector<sf::IntRect>> animations; // Stores animation frames; key is state (e.g., "idle", "attacking"), value is a vector of sf::IntRect for frames from the texture sheet.
        std::string currentAnimationState; // The current animation state of the weapon (e.g., "idle").
        unsigned int currentFrameIndex; // Index of the current frame in the active animation sequence.
        float animationClock; // Timer to control animation frame progression.
        float frameDuration; // Time each frame is displayed.
        bool isAnimated; // Flag to indicate if the weapon has animations.

    public:
        void useWeapon();
        Weapon(const std::string& name, const std::string& texturePath, float dmgMod, float rangeMod, int costMod, const std::string& compatibleType); // Constructor to initialize a weapon with its properties and texture.

        ~Weapon(); // Destructor, if needed for manual resource management (though SFML/STL often handle this).

        // --- Getters for Modifiers and Properties ---

        std::string getName() const;

        float getDamageModifier() const;

        float getRangeModifier() const;

        int getCostModifier() const;

        std::string getAttackTypeCompatibility() const;    

        const sf::Sprite& getSprite() const; // Allows the Unit to get the current sprite for positioning.

// --- Core Functionality ---

        void applyStats(float& baseDamage, float& baseRange, int& baseCost) const; // Modifies provided unit stats with weapon's modifiers.

        void update(float deltaTime, sf::Vector2f unitPosition, float unitRotation); // Updates weapon's state, animation, and position based on the unit.

        void draw(sf::RenderWindow* window); // Draws the weapon's current sprite to the screen.    

        // --- Animation Management ---

        void loadAnimation(const std::string& stateName, const std::vector<sf::IntRect>& frames, float duration, bool looping = true); // Loads a new animation sequence.

        void setAnimationState(const std::string& stateName); // Changes the current animation state (e.g., to "attacking").                            
        

}

#endif // WEAPON_HPP_