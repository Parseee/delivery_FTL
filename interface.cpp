#include "interface.h"

#include "gui.h"

void Interface(sf::RenderWindow &window) {
    Text text_by_car(30, 20, 25, "Number of couriers by car");
    text_by_car.draw(window);
    InputField input_by_car(30, 55, 100, 30);
    input_by_car.setButton();
    input_by_car.setColor(sf::Color(211, 211, 211));
    input_by_car.draw(window);
    Text text_foot(30, 105, 25, "Number of foot couriers");
    text_foot.draw(window);
    InputField input_foot(30, 140, 100, 30);
    input_foot.setColor(sf::Color(211, 211, 211));
    input_foot.setButton();
    input_foot.draw(window);

    Button start_button(30, 810, 70, 70);
    start_button.setImage("images/start.png");
    start_button.draw(window);
    Button pause_button(110, 810, 70, 70);
    pause_button.setImage("images/pause.png");
    pause_button.draw(window);
    Button stop_button(190, 810, 70, 70);
    stop_button.setImage("images/stop.png");
    stop_button.draw(window);

    Text current_time_text(30, 760, 30, "TIME ");
    current_time_text.draw(window);
}

// void DrawBranches(sf::RenderWindow &window) {}
