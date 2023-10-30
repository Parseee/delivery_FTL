#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "gui.h"

struct Request {
    time_t start_time;
    time_t end_time;
    unsigned int source;
    unsigned int destination;
    unsigned int urgency;
    
    Request() = default;
    Request(time_t start_time, time_t end_time, unsigned int source,
            unsigned int destination, unsigned int urgency)
        : start_time(start_time),
          end_time(end_time),
          source(source),
          destination(destination),
          urgency(urgency) {
    }

    bool operator<(const Request req) const {
        return this->urgency > req.urgency;
    }
    void draw(sf::RenderWindow &window) {
        Field req(1370, 670, 200, 200);
        req.setColor(sf::Color(211, 211, 211));
        Text req_text(1380, 680, 25, "NEW REQUEST", sf::Color::Red);
        Text source_text(1380, 715, 25, "from: " + std::to_string(source));
        Text destination_text(1380, 750, 25,
                              "to: " + std::to_string(destination));
        Text urgency_text(1380, 785, 25, "urgency: " + std::to_string(urgency));
        req.draw(window);
        req_text.draw(window);
        source_text.draw(window);
        destination_text.draw(window);
        urgency_text.draw(window);
    }
};