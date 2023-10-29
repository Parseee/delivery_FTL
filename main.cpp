#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

#include "car_courier.h"
#include "default_courier.h"
#include "dispatcher.h"
#include "gui.h"
#include "interface.h"
#include "request.h"

#define WEEK_DAY_MINUTES 480
#define WEEK_DAYS 5

extern int default_courier_amount, car_courier_amount;
bool is_set_couriers = false, is_start = false, is_stop = false;
extern std::vector<Branch*> branches;

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
    Dispatcher dispatcher;
    sf::Time elapsedTime;
    sf::Clock clock;
    while (window.isOpen()) {
        window.clear(sf::Color::White);
        // while (dispatcher.get_days() < WEEK_DAYS) {
        //     while (dispatcher.get_simulated_time() < WEEK_DAY_MINUTES) {
        //         dispatcher.assign_new_request(dispatcher.create_new_request());
        //         dispatcher.tick();
        //     }
        //     dispatcher.update_days();
        // }
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (!is_set_couriers && !is_start) {
                HandleInputs(event);
            }
            if (!is_start) {
                if (HandleSetCouriers(event))
                    is_set_couriers = true;
                else if (branches.size() < 7)
                    HandleClickBranch(event);
                dispatcher.set_dispatcher();
            }
            // if (is_set_couriers && branches.size() >= 1) {
            //     if (HandleStart(event)) is_start = true;
            // }
            // if (HandlePause(event)) is_stop = true;
            // if (HandleStop(event)) {
            //     // ...
            // }
            HandleIntervals(event);
            HandleEvent(event);
        }
        elapsedTime = clock.getElapsedTime();
        if (elapsedTime > sf::milliseconds(10)) {
            CheckLines(window);
            elapsedTime = clock.restart();
        }
        Interface(window);
        DrawBranches(window);
        dispatcher.drawCouriers(window);
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
