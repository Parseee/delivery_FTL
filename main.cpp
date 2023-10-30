#include <unistd.h>

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "car_courier.h"
#include "default_courier.h"
#include "dispatcher.h"
#include "gui.h"
#include "interface.h"
#include "request.h"

#define WEEK_DAY_MINUTES 540
#define WEEK_DAYS 5

extern int default_courier_amount, car_courier_amount;
bool is_set_couriers = false, is_start = false, is_pause = false,
     is_set = false;
extern std::vector<Branch*> branches;
extern std::pair<int, int> deviation;
extern double slp;

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
    sf::Time elapsedTime, request_time;
    sf::Clock clock, request_clock;
    Request* current_request = nullptr;
    while (window.isOpen()) {
        auto t = std::chrono::seconds(1000);
        if (is_start) {
            while (dispatcher.get_simulated_time() / WEEK_DAY_MINUTES <
                   WEEK_DAYS) {
                while (dispatcher.get_simulated_time() % WEEK_DAY_MINUTES <
                       WEEK_DAY_MINUTES) {
                    window.clear(sf::Color::White);
                    if (!is_pause) {
                        sleep(slp / 1000.0);
                        if (dispatcher.probability(
                                dispatcher.get_simulated_time() %
                                WEEK_DAY_MINUTES)) {
                            Request temp_request =
                                dispatcher.create_new_request(deviation);
                            current_request = &temp_request;
                            dispatcher.assign_new_request(temp_request);
                        }
                        dispatcher.tick();
                    }
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) window.close();
                        HandleFast(event);
                        HandleSlow(event);
                        HandleIntervals(event);
                        if (HandlePause(event)) is_pause = true;
                        if (HandleStart(event)) is_pause = false;
                        // if (HandleStop(event)) {
                        //     // ...
                        // }
                    }
                    request_time = request_clock.getElapsedTime();
                    if (request_time < sf::seconds(2) &&
                        current_request != nullptr) {
                        current_request->draw(window);
                    } else if (!is_pause) {
                        current_request = nullptr;
                        request_time = request_clock.restart();
                    }
                    Interface(window);
                    DrawBranches(window);
                    dispatcher.drawCouriers(window);
                    dispatcher.print_time(window);
                    window.display();
                }
            }
        } else {
            window.clear(sf::Color::White);
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (!is_set_couriers && !is_start) {
                    HandleInputs(event);
                }
                if (!is_start) {
                    is_set_couriers = HandleSetCouriers(event, is_set);
                    if (!is_set_couriers) HandleClickBranch(event);
                    dispatcher.set_dispatcher();
                }
                if (is_set && branches.size()) {
                    if (HandleStart(event)) is_start = true;
                }
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
