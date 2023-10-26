#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Text {
   public:
    Text() {
        x_ = 0;
        y_ = 0;
        text_ = "";
    }
    void setData(double x, double y, int size, std::string text,
                 sf::Color color = sf::Color::Black) {
        x_ = x;
        y_ = y;
        size_ = size;
        text_ = text;
        color_ = color;
    }
    void updateText(char c) { text_ += c; }
    void draw(sf::RenderWindow &window);
    int getSize() { return size_; };

   private:
    double x_, y_;
    std::string text_;
    sf::Color color_ = sf::Color::Black;
    double size_;
};

class Field {
   public:
    Field() = default;
    void setData(double x, double y, double width, double height) {
        x_ = x;
        y_ = y;
        width_ = width;
        height_ = height;
    }
    virtual void draw(sf::RenderWindow &window);
    virtual void setText(std::string text, int size,
                         sf::Color color = sf::Color::Black) {
        double x = x_ + (width_ - text.length() * (int)(size / 1.6)) / 2.0;
        double y = y_ + (height_ - size) / 2.0;
        text_.setData(x, y, size, text, color);
    }
    void setColor(sf::Color color) { color_ = color; }
    void setImage(std::string image) {
        is_img_ = true;
        image_ = image;
    }

   protected:
    double x_, y_;
    double width_, height_;
    bool is_img_ = false;
    std::string image_ = "";
    sf::Color color_;
    Text text_;
};

class Button : public Field {
   public:
    Button() = default;
    bool isClicked(sf::Event event);

   private:
};

class InputField : public Field {
   public:
    InputField() = default;
    void draw(sf::RenderWindow &window);
    void clicked(sf::Event event);
    bool isButtonClicked(sf::Event event) { return ok_button.isClicked(event); }
    void setButton() {
        ok_button.setData(x_ + width_ + 10, y_, height_, height_);
        ok_button.setImage("images/ok.png");
    }
    void setText(std::string text, int size,
                 sf::Color color = sf::Color::Black) {
        text_.setData(x_ + 4, y_ + 2, size, text, color);
    }

   private:
    bool is_active_ = false;
    Button ok_button;
};