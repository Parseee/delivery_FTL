#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Line {
   public:
    Line() = default;
    Line(double x1, double y1, double x2, double y2) {}
    void draw(sf::RenderWindow &window){
        return;
    }

   private:
    int length_;
    // angle_
};

class Text {
   public:
    Text() {
        x_ = 0;
        y_ = 0;
        text_ = "";
    }
    Text(double x, double y, int size, std::string text,
         sf::Color color = sf::Color::Black) {
        x_ = x;
        y_ = y;
        size_ = size;
        text_ = text;
        color_ = color;
    }
    void setData(double x, double y, int size, std::string text,
                 sf::Color color = sf::Color::Black) {
        x_ = x;
        y_ = y;
        size_ = size;
        text_ = text;
        color_ = color;
    }
    // ?
    void updateText(char c) { text_ += c; }
    //
    void draw(sf::RenderWindow &window);
    int getSize() { return size_; };
    std::string getText() { return text_; }

   private:
    double x_, y_;
    std::string text_;
    sf::Color color_ = sf::Color::Black;
    double size_;
};

class Field {
   public:
    Field() = default;
    Field(double x, double y, double width, double height) {
        x_ = x;
        y_ = y;
        width_ = width;
        height_ = height;
    }
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
    bool isClicked(sf::Event event);
    bool isActive() { return is_active_; }
    virtual void clicked() { is_active_ = true; }
    virtual void notClicked() { is_active_ = false; }

   protected:
    double x_, y_;
    double width_, height_;
    bool is_img_ = false;
    std::string image_ = "";
    sf::Color color_;
    Text text_;
    bool is_active_ = false;
};

class Button : public Field {
   public:
    Button() = default;
    Button(double x, double y, double width, double height) {
        x_ = x;
        y_ = y;
        width_ = width;
        height_ = height;
    }
};

class InputField : public Field {
   public:
    InputField() = default;
    InputField(double x, double y, double width, double height,
               sf::Color color = sf::Color(211, 211, 211)) {
        x_ = x;
        y_ = y;
        width_ = width;
        height_ = height;
        color_ = color;
    }
    void draw(sf::RenderWindow &window);
    void setText(std::string text, int size,
                 sf::Color color = sf::Color::Black) {
        text_.setData(x_ + 4, y_ + 2, size, text, color);
    }
    void updateText(std::string text) { this->setText(text, 20); }
    std::string getText() { return text_.getText(); }
    void clicked();
    void notClicked();
};

class Branch : public Button {
   public:
    Branch(double x, double y, int number) {
        x_ = x;
        y_ = y;
        height_ = 45;
        width_ = 75;
        this->setImage("images/branch.png");
        this->setText(std::to_string(number), 25);
    }
    double getX() { return x_; }
    double getY() { return y_; }
};