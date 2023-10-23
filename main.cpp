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

#define RELEASE

// please use mt as randomizer!!! -- implemented

// i think its need to use vector with current active couriers to update status (and location) 
// for each courier -- using priority_queue

#ifdef DEBUG
int TEST_DEFAULT_COURIER_AMOUNT = 2;
int TEST_CAR_COURIER_AMOUNT = 2;
#endif

int main() {
    // some code for gui

    // time_t start_time = time(nullptr); // deprecated

#ifndef DEBUG
    // somehow get default and car courier amount here
    Dispatcher dispatcher(2, 2);
    while (dispatcher.get_days() < WEEK_DAYS) {
        while (dispatcher.get_simulated_time() < WEEK_DAY_MINUTES) {
            dispatcher.assign_new_request(dispatcher.create_new_request());
            dispatcher.tick();
        }
    }
#endif

#ifdef DEBUG
    Dispatcher dispatcher(TEST_DEFAULT_COURIER_AMOUNT, TEST_CAR_COURIER_AMOUNT);

    dispatcher.assign_new_request(dispatcher.create_new_request());
    dispatcher.assign_new_request(dispatcher.create_new_request());

    
    for (int i = 0; i < TEST_DEFAULT_COURIER_AMOUNT + TEST_CAR_COURIER_AMOUNT; ++i) {
        try {
        Courier *courier = dispatcher.get_last_courier_and_kill();
        std::cout << "Courier sucsessfully got\n";
        std::cout << courier->is_car() << '\n';
        std::cout << courier->get_curent_request().start_time << '\n';
        delete courier;
        } catch (const std::logic_error& e) {
            std::cout << e.what() << '\n';
        }
    }
    
#endif
    //in cycle we will update status for each courier because they can deliver requests in parallel
}
