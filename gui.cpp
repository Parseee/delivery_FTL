#include "gui.h"

#include <SFML/Graphics.hpp>

void Text::draw(sf::RenderWindow &window) {
    sf::Font font;
    if (font.loadFromFile("Gilroy-Semibold.ttf")) {
        sf::Text text;
        text.setFont(font);
        text.setString(text_);
        text.setCharacterSize(size_);
        text.setFillColor(color_);
        text.setPosition(x_, y_);
        window.draw(text);
    }
}

void Field::draw(sf::RenderWindow &window) {
    if (is_img_) {
        sf::Texture texture;
        texture.loadFromFile(image_);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        auto size = texture.getSize();
        std::pair<double, double> scale = {(double)width_ / size.x,
                                           (double)height_ / size.y};
        sprite.setScale(sf::Vector2f(scale.first, scale.second));
        // sprite.setScale(sf::Vector2f(width_, height_));
        sprite.setPosition(x_, y_);
        window.draw(sprite);
    } else {
        sf::RectangleShape field;
        field.move(x_, y_);
        field.setFillColor(color_);
        field.setSize(sf::Vector2f(width_, height_));
        window.draw(field);
    }
    text_.draw(window);
}

void InputField::clicked(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            double mouse_x = event.mouseButton.x;
            double mouse_y = event.mouseButton.y;
            if (mouse_x >= x_ && mouse_x <= x_ + width_ && mouse_y >= y_ &&
                mouse_y <= y_ + height_) {
                is_active_ = true;
            }
        }
    }
}

void InputField::draw(sf::RenderWindow &window) {
    sf::RectangleShape button;
    button.move(x_, y_);
    button.setFillColor(color_);
    button.setSize(sf::Vector2f(width_, height_));
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color::Black);
    window.draw(button);
    text_.draw(window);
    ok_button.draw(window);
}

bool Button::isClicked(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            double mouse_x = event.mouseButton.x;
            double mouse_y = event.mouseButton.y;
            if (mouse_x >= x_ && mouse_x <= x_ + width_ && mouse_y >= y_ &&
                mouse_y <= y_ + height_) {
                return true;
            }
        }
    }
    return false;
}