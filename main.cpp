#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

#include "car_courier.h"
#include "default_courier.h"
#include "dispatcher.h"
#include "interface.h"
#include "gui.h"
#include "request.h"

#define WEEK_DAY_MINUTES 480
#define WEEK_DAYS 5

// рандомизировать создание заявки

#ifdef DEBUG
int TEST_DEFAULT_COURIER_AMOUNT = 1;
int TEST_CAR_COURIER_AMOUNT = 1;
#endif

int main() {
#ifndef DEBUG
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Delivery");

    sf::Event event;
    Dispatcher dispatcher(2, 2);
    while (window.isOpen()) {
        // while (dispatcher.get_days() < WEEK_DAYS) {
        //     while (dispatcher.get_simulated_time() < WEEK_DAY_MINUTES) {
        //         dispatcher.assign_new_request(dispatcher.create_new_request());
        //         dispatcher.tick();
        //     }
        //     dispatcher.update_days();
        // }
        while (window.pollEvent(event)) {
        }
        window.clear(sf::Color::White);
        Interface(window);
        window.display();
    }
#endif

#ifdef DEBUG
    Dispatcher dispatcher(TEST_DEFAULT_COURIER_AMOUNT, TEST_CAR_COURIER_AMOUNT);

    try {
        dispatcher.assign_new_request(dispatcher.create_new_request());
        dispatcher.assign_new_request(dispatcher.create_new_request());
    } catch (const std::logic_error& e) {
        std::cout << e.what() << '\n';
    }

    for (int i = 0; i < TEST_DEFAULT_COURIER_AMOUNT + TEST_CAR_COURIER_AMOUNT;
         ++i) {
        try {
            std::cout << "Courier sucsessfully got\n";
            Courier* courier = dispatcher.get_last_courier_and_kill();
            std::cout << courier->get_curent_request().start_time << '\n';
            delete courier;
        } catch (const std::logic_error& e) {
            std::cout << e.what() << '\n';
        }
    }
#endif
}
