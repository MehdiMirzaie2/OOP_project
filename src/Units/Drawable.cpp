#include "../../include/Drawable.hpp"

Drawable::Drawable(std::string pname, std::string idleName, std::string aName)
	:m_projectileTextureName(pname), m_unitTextureIdleName(idleName), m_unitTextureAttackingName(aName) {
	
	if (!m_unitTextureIdle.loadFromFile("src/Textures/" + std::string(m_unitTextureIdleName)))
    {
        std::cout << "Unable to load Idle texture!\n";
    }

    if (!m_unitTextureAttacking.loadFromFile("src/Textures/" + std::string(m_unitTextureAttackingName)))
    {
        std::cout << "Unable to load attacking texture!\n";
    }

	if (!m_projectileTexture.loadFromFile("src/Textures/" + std::string(m_projectileTextureName)))
    {
        std::cout << "Unable to load project texture!\n";
    }

    if (!m_deadTexture.loadFromFile("src/Textures/death.png"))
    {
        std::cout << "Couldnt load death soul\n";
    }
}