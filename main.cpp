#include <iostream>
#include <random>
#include <vector>

#include "car_courier.h"
#include "default_courier.h"
#include "dispatcher.h"
#include "request.h"

#define DEBUG

// please use mt as randomizer!!!

// i think its need to use vector with current active couriers to update status (and location) 
// for each courier

#ifdef DEBUG
int TEST_DEFAULT_COURIER_AMOUNT = 2;
int TEST_CAR_COURIER_AMOUNT = 2;
#endif

int main() {
    // some code for gui
    Dispatcher dispatcher(TEST_DEFAULT_COURIER_AMOUNT, TEST_CAR_COURIER_AMOUNT);
    time_t start_time = time(nullptr);

#ifdef RELEASE
    while (std::difftime(dispatcher.get_current_time(), start_time) < 128 /* the number is abstract */) {
        // create, assign and process request etc...        
    }
#endif

#ifdef DEBUG
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
