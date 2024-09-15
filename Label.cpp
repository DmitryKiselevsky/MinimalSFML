// Класс для лейбла
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Label {
public:
    Label(const sf::Vector2f& position, const sf::String& text) {
        font.loadFromFile("roboto.ttf");
        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::White);
        label.setPosition(position);
    }

    void setText(const sf::String& text) {
        label.setString(text);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(label);
    }

private:
    sf::Text label;
    sf::Font font;
};