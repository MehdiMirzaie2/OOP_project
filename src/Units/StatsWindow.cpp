#include "../../include/StatsWindow.hpp"

// Constructor: Loads fonts, textures, and sets up initial text properties.
StatsWindow::StatsWindow() {
    // Load font
    // Ensure the path to the font file is correct relative to your executable
    if (!m_font.loadFromFile("./src/Fonts/Quicksand-Bold.ttf")) {
        std::cerr << "Error: Could not load font './src/Fonts/Quicksand-Bold.ttf' for StatsWindow!" << std::endl;
        // Consider a fallback font or exiting if font is critical
    }

    // Load background texture
    // Ensure the path to the texture file is correct
    if (!m_stats_bg_texture.loadFromFile("src/Textures/statTexture.png")) {
        std::cerr << "Error: Could not load background texture 'src/Textures/statTexture.png' for StatsWindow!" << std::endl;
        // Fallback: create a simple colored background if texture fails
        m_stats_bg_texture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
        sf::Image tempImage;
        tempImage.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color(30, 30, 30, 255)); // Dark gray
        m_stats_bg_texture.update(tempImage);
        m_stats_bg_sprite.setTexture(m_stats_bg_texture); // Set texture for sprite
    } else {
        m_stats_bg_sprite.setTexture(m_stats_bg_texture);
        // Scale background to fit window dimensions
        m_stats_bg_sprite.setScale(
            static_cast<float>(WINDOW_WIDTH) / m_stats_bg_texture.getSize().x,
            static_cast<float>(WINDOW_HEIGHT) / m_stats_bg_texture.getSize().y
        );
    }


    // Setup text objects (positions are placeholders, adjust as needed)
    setupText(m_titleText, "Player Statistics", 40, sf::Color::White, WINDOW_WIDTH / 2.f, 70.f);
    setupText(m_player1StatsText, "Player 1: Loading...", 30, sf::Color::White, WINDOW_WIDTH / 2.f, 180.f);
    setupText(m_player2StatsText, "Player 2: Loading...", 30, sf::Color::White, WINDOW_WIDTH / 2.f, 240.f);
    setupText(m_backButtonText, "Back to Menu", 30, sf::Color::Yellow, WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 80.f);
}

// Helper function to configure sf::Text objects.
void StatsWindow::setupText(sf::Text& textObject, const std::string& content, int charSize, sf::Color color, float x, float y) {
    textObject.setFont(m_font);
    textObject.setString(content);
    textObject.setCharacterSize(charSize);
    textObject.setFillColor(color);
    textObject.setOutlineColor(sf::Color::Black);
    textObject.setOutlineThickness(1.f);

    // Center text origin for easier positioning
    sf::FloatRect textRect = textObject.getLocalBounds();
    textObject.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    textObject.setPosition(x, y);
}

// Loads statistics from the specified file and updates the display text.
void StatsWindow::loadStats(const std::string& filename) {
    std::ifstream statFile(filename);
    std::string line1, line2;
    int p1_wins, p2_wins, p1_losses, p2_losses = 0;

    if (statFile.is_open()) {
        // Read Player 1 stats
        if (std::getline(statFile, line1)) {
            std::stringstream ss1(line1);
            std::string tempWord; // To consume "Player", "1", "-"
            char slash;
            // Expected format: "Player 1 - <wins>/<losses>"
            if (!(ss1 >> tempWord >> tempWord >> tempWord >> p1_wins >> slash >> p1_losses)) {
                 p1_wins = -1; p1_losses = -1; // Parsing error
            }
        }
        // Read Player 2 stats
        if (std::getline(statFile, line2)) {
            std::stringstream ss2(line2);
            std::string tempWord;
            char slash;
            // Expected format: "Player 2 - <wins>/<losses>"
            if (!(ss2 >> tempWord >> tempWord >> tempWord >> p2_wins >> slash >> p2_losses)) {
                p2_wins = -1; p2_losses = -1; // Parsing error
            }
        }
        statFile.close();
    } else {
        std::cerr << "Error: Could not open stats file: " << filename << std::endl;
        // Stats will remain "N/A" or "Loading..." as set initially
    }

    m_player1StatsText.setString("Player 1: Wins - " + std::to_string(p1_wins) + " / Losses - " + std::to_string(p1_losses));
    m_player2StatsText.setString("Player 2: Wins - " + std::to_string(p2_wins) + " / Losses - " + std::to_string(p2_losses));

    // Re-center text after changing string content, as bounds might change
    setupText(m_player1StatsText, m_player1StatsText.getString(), 30, sf::Color::White, WINDOW_WIDTH / 2.f, 180.f);
    setupText(m_player2StatsText, m_player2StatsText.getString(), 30, sf::Color::White, WINDOW_WIDTH / 2.f, 240.f);
}

// Main loop for the StatsWindow.
int StatsWindow::runWindow(const std::string& statfile) {
    // m_window is a std::unique_ptr<sf::RenderWindow> from the base class Window.
    // It needs to be initialized.
    if (!m_window) { // Check if already initialized (e.g., by a previous call or in base)
        m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Player Statistics", sf::Style::Default);
    } else { // If window exists, ensure it's open and set title (though it should be new)
        if (!m_window->isOpen()) {
             m_window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Player Statistics", sf::Style::Default);
        } else {
            m_window->setTitle("Player Statistics");
        }
    }
    m_window->setFramerateLimit(60);

    loadStats(statfile); // Load/reload stats each time the window is shown

    while (m_window->isOpen()) {
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window->close();
                return -1; // Indicate window was closed via 'X', could mean exit game
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
                    if (m_backButtonText.getGlobalBounds().contains(mousePos)) {
                        m_window->close(); // Close this window
                        return STATS_WINDOW_BACK; // Signal to Game class to return to main menu
                    }
                }
            }
        }

        m_window->clear(sf::Color(50, 50, 50)); // Clear with a default color
        m_window->draw(m_stats_bg_sprite);    // Draw background first
        m_window->draw(m_titleText);
        m_window->draw(m_player1StatsText);
        m_window->draw(m_player2StatsText);
        m_window->draw(m_backButtonText);
        m_window->display();
    }
    return -1; // Should ideally not be reached if closed properly
}
