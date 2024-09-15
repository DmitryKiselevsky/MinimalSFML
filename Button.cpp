#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Класс для кнопки
class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& text) {
        button.setSize(size);
        button.setPosition(position);
        button.setFillColor(sf::Color::Black);

        font.loadFromFile("roboto.ttf");
        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::White);
        label.setPosition(
            position.x + (size.x - label.getGlobalBounds().width) / 2,
            position.y + (size.y - label.getGlobalBounds().height) / 2
        );
    }

    void draw(sf::RenderWindow& window) {
        window.draw(button);
        window.draw(label);
    }

    bool isClicked(const sf::Vector2i& mousePos) {
        return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

private:
    sf::RectangleShape button;
    sf::Text label;
    sf::Font font;
};