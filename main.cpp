#include <iostream>
#include <random>
#include <vector>

#include "car_courier.h"
#include "default_courier.h"
#include "dispatcher.h"
#include "request.h"

// i'm adding 2 minutes every iteration so 8hr * 60min
#define WEEK_DAY_MINUTES 480
#define WEEK_DAYS 5

#define DEBUG

#ifdef DEBUG
int TEST_DEFAULT_COURIER_AMOUNT = 1;
int TEST_CAR_COURIER_AMOUNT = 1;
#endif

int main() {
    // some code for gui

    // time_t start_time = time(nullptr); // deprecated -- what ??

#ifndef DEBUG
    // somehow get default and car courier amount here
    Dispatcher dispatcher(2, 2);
    while (dispatcher.get_days() < WEEK_DAYS) {
        while (dispatcher.get_simulated_time() < WEEK_DAY_MINUTES) {
            dispatcher.assign_new_request(dispatcher.create_new_request());
            dispatcher.tick();
        }
        dispatcher.update_days();
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
            Courier *courier = dispatcher.get_last_courier_and_kill();
            std::cout << courier->get_curent_request().start_time << '\n';
            delete courier;
        } catch (const std::logic_error& e) {
            std::cout << e.what() << '\n';
        }
    }
#endif
}
