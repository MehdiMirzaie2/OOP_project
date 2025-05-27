#include "../../include/Drawable.hpp"

Drawable::Drawable() {}

Drawable::Drawable(std::string a, std::string b, std::string c)
	:m_projectileTextureName(a),
	m_unitTextureIdleName(b),
	m_unitTextureAttackingName(c)
{
	if (!m_unitTextureIdle.loadFromFile("src/Textures/" + std::string(m_unitTextureIdleName)))
    {
        std::cout << "Unable to load Idle texture!\n";
    }

    if (!m_unitTextureAttacking.loadFromFile("src/Textures/" + std::string(m_unitTextureAttackingName)))
    {
        std::cout << "Unable to load attacking texture!\n";
    }

    if (!m_deadTexture.loadFromFile("src/Textures/death.png"))
    {
        std::cout << "Couldnt load death soul\n";
    }
}


std::string Drawable::getProjectileTextureName() {
    return m_projectileTextureName;
}

std::string Drawable::getIdleTextureName() {
    return m_unitTextureIdleName;
}

std::string Drawable::getAttackingTextureName() {
    return m_unitTextureAttackingName;
}
