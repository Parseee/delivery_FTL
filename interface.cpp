#include "interface.h"

#include "gui.h"

InputField input_by_car;
InputField input_foot;
Button start_button;
Button pause_button;
Button stop_button;

void Interface(sf::RenderWindow &window) {
    Text text_by_car;
    text_by_car.setData(30, 20, 25, "Number of couriers by car");
    text_by_car.draw(window);
    input_by_car.setData(30, 55, 100, 30);
    input_by_car.setButton();
    input_by_car.setColor(sf::Color(211, 211, 211));
    input_by_car.draw(window);
    Text text_foot;
    text_foot.setData(30, 105, 25, "Number of foot couriers");
    text_foot.draw(window);
    input_foot.setData(30, 140, 100, 30);
    input_foot.setColor(sf::Color(211, 211, 211));
    input_foot.setButton();
    input_foot.draw(window);

    start_button.setData(30, 810, 70, 70);
    start_button.setImage("images/start.png");
    start_button.draw(window);
    pause_button.setData(110, 810, 70, 70);
    pause_button.setImage("images/pause.png");
    pause_button.draw(window);
    stop_button.setData(190, 810, 70, 70);
    stop_button.setImage("images/stop.png");
    stop_button.draw(window);

    Text current_time_text;
    current_time_text.setData(30, 760, 30, "TIME ");
    current_time_text.draw(window);
}

// void DrawBranches(sf::RenderWindow &window) {}
