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
    Text(double x, double y, int size, std::string text)
        : x_(x), y_(y), size_(size), text_(text) {}
    void setText(std::string text) { text_ = text; }
    void setSize(double size) { size_ = size; }
    void setColor(sf::Color color) { color_ = color; }
    void setPosition(double x, double y) {
        x_ = x;
        y_ = y;
    }
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
    Field(double x, double y, double width, double height)
        : x_(x), y_(y), width_(width), height_(height) {}
    virtual void draw(sf::RenderWindow &window);
    virtual void setText(std::string text, sf::Color color, int size) {
        text_.setText(text);
        text_.setColor(color);
        text_.setSize(size);
        text_.setPosition(
            x_ + (width_ - text.length() * (int)(size / 1.6)) / 2.0,
            y_ + (height_ - size) / 2.0);
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
    Button(double x, double y, double width, double height)
        : Field(x, y, width, height) {}
    void setPosition(double x, double y) {
        x_ = x;
        y_ = y;
    }
    void setSize(double width, double height) {
        width_ = width;
        height_ = height;
    }
    bool isClicked(sf::Event event);

   private:
};

class InputField : public Field {
   public:
    InputField() = default;
    InputField(double x, double y, double width, double height)
        : Field(x, y, width, height) {}
    void draw(sf::RenderWindow &window);
    void clicked(sf::Event event);
    bool isButtonClicked(sf::Event event) { return ok_button.isClicked(event); }
    void setButton() {
        ok_button.setImage("images/ok.png");
        ok_button.setPosition(x_ + width_ + 10, y_);
        ok_button.setSize(height_, height_);
    }
    void setText(std::string text, sf::Color color, int size) {
        text_.setText(text);
        text_.setColor(color);
        text_.setSize(size);
        text_.setPosition(x_ + 4, y_ + 2);
    }

   private:
    bool is_active_ = false;
    Button ok_button;
};