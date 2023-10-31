#include <fstream>
#include <string>
#include <iostream>
#include "dispatcher.h"
#include "courier.h"

class Database {
 public:
    Database() {
        output_stream = std::ofstream("statistics.txt");
    }

    void put_data_to_file(Dispatcher &dispatcher) {
        for (auto courier : dispatcher.get_couriers()) {
            output_stream << "Courier " << courier->get_courier_number() << " :\n";
            output_stream << "Request processed: " << courier->get_amount_of_processed_requests() << '\n';
            output_stream << "Time spent: " << courier->get_consumed_time() << " , idle: " << courier->get_wasted_time() << '\n';
            output_stream << '\n';
        }
    }
 private:
    std::ofstream output_stream;
};