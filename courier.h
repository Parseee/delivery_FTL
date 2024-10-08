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

    Request get_current_request();
    // void add_new_request(Request request);
    void set_request(Request request);
    Request give_away_current_request();
    void draw(sf::RenderWindow& window, int time_);
    int get_delivery_duration();
    bool is_busy() { return is_busy_; }
    // bool is_request();
    void add_wasted_time(int time_to_add);
    int get_wasted_time() { return wasted_time_; }
    int get_consumed_time() { return consumed_time_; }
    int get_courier_number() { return number_; }
    int get_amount_of_processed_requests() {
        return completed_requests_.size();
    }
    bool is_active() { return is_active_; }
    bool is_clicked(sf::Event event);
    void clicked() { is_active_ = true; }
    void not_clicked() { is_active_ = false; }
    sf::Time courier_time;
    sf::Clock courier_clock;
    void draw_info(sf::RenderWindow &window);

   protected:
    unsigned int number_;
    // std::priority_queue<Request> pending_request_;
    bool is_busy_ = false;
    Request current_request_;
    std::vector<Request> completed_requests_;
    unsigned int current_location_;
    unsigned int consumed_time_;
    int wasted_time_;
    double x_, y_;
    bool is_active_ = false;
};