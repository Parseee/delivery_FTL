#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <queue>
#include <vector>

#include "gui.h"
#include "request.h"

class Courier {
   public:
    Courier(int number, int location);
    Courier(const Courier&) = delete;  // we don't need clones!
    Courier(Courier&& courier);
    virtual ~Courier() = default;
    virtual bool is_car() const = 0;
    int get_location() const { return current_location_; }
    void add_consumed_time(int time_to_add);

    Request get_curent_request();
    void add_new_request(Request request);
    Request give_away_current_request();
    void draw(sf::RenderWindow& window);
    int get_delivery_duration();
    bool is_request();
    void add_wasted_time(int time_to_add);
    int get_wasted_time() { return wasted_time_; }

   protected:
    unsigned int number_;
    std::priority_queue<Request> pending_request_;
    std::vector<Request> completed_requests_;
    unsigned int current_location_;
    unsigned int consumed_time_;
    int wasted_time_;
};