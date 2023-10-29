#include "gui.h"

#include <SFML/Graphics.hpp>

void Text::draw(sf::RenderWindow &window) {
    if (text_.length() != 0) {
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

bool Field::isClicked(sf::Event event) {
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

void InputField::clicked() {
    is_active_ = true;
    this->setColor(sf::Color(169, 169, 169));
}

void InputField::notClicked() {
    is_active_ = false;
    this->setColor(sf::Color(211, 211, 211));
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
}

void Line::draw(sf::RenderWindow &window) {
    sf::RectangleShape shape;
    shape.move(x_, y_);
    shape.setFillColor(sf::Color::Black);
    shape.setSize(sf::Vector2f(length_, 2));
    shape.setRotation(angle_);
    num_.draw(window);
    window.draw(shape);
}

Line::Line(double x1, double y1, double x2, double y2) {
    x_ = x1;
    y_ = y1;
    length_ = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    if (x2 >= x1 && y2 >= y1) {
        angle_ = atan(fabs(y1 - y2) / fabs(x1 - x2)) * 180.0 / PI;
        num_.setData((x1 + x2) / 2.0 + 20, (y1 + y2) / 2.0 - 20, 18,
                     std::to_string((int)ceil(length_) / 10));
    } else if (x2 <= x1 && y2 >= y1) {
        angle_ = atan(fabs(x1 - x2) / fabs(y1 - y2)) * 180.0 / PI + 90;
        num_.setData((x1 + x2) / 2.0 - 40, (y1 + y2) / 2.0 - 20, 18,
                     std::to_string((int)ceil(length_) / 10));
    } else if (x2 <= x1 && y2 <= y1) {
        num_.setData((x1 + x2) / 2.0 + 20, (y1 + y2) / 2.0 - 20, 18,
                     std::to_string((int)ceil(length_) / 10));
        angle_ = atan(fabs(y1 - y2) / fabs(x1 - x2)) * 180.0 / PI + 180;
    } else if (x2 >= x1 && y2 <= y1) {
        num_.setData((x1 + x2) / 2.0 - 40, (y1 + y2) / 2.0 - 20, 18,
                     std::to_string((int)ceil(length_) / 10));
        angle_ = atan(fabs(x1 - x2) / fabs(y1 - y2)) * 180.0 / PI + 270;
    }
}