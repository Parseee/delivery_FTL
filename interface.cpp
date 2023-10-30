#include "interface.h"

#include <map>
#include <string>
#include <vector>

#include "courier.h"
#include "gui.h"

/*
рандомизация заявок
прописать изменение локации курьеров
кнопка ускорение и замедление
*/

std::vector<Branch *> branches;
std::vector<std::pair<Branch *, Branch *>> branches_list;
std::vector<std::pair<int, int>> car_courier_list;
std::vector<std::pair<int, int>> default_courier_list;
std::map<int, Branch *> branches_map;
std::pair<int, int> deviation;

double mouse_x, mouse_y;

int default_courier_amount = 0, car_courier_amount = 0;

Button input_by_car_button(140, 55, 30, 30);
Button input_foot_button(140, 140, 30, 30);
InputField input_by_car(30, 55, 100, 30);
InputField input_foot(30, 140, 100, 30);

// Button interval_minus_first(25, 295, 20, 20);
// InputField interval_field_first(60, 290, 50, 30);
// Button interval_plus_first(125, 295, 20, 20);
// Button interval_minus_second(25, 335, 20, 20);
// InputField interval_field_second(60, 330, 50, 30);
// Button interval_plus_second(125, 335, 20, 20);

Button deviation_minus_first(25, 445, 20, 20);
InputField deviation_field_first(60, 440, 50, 30);
Button deviation_plus_first(125, 445, 20, 20);
Button deviation_minus_second(25, 485, 20, 20);
InputField deviation_field_second(60, 480, 50, 30);
Button deviation_plus_second(125, 485, 20, 20);

Button set_couriers(30, 650, 230, 70);

Button slow_button(30, 810, 70, 70);
Button start_button(110, 810, 70, 70);
Button fast_button(190, 810, 70, 70);
Button pause_button(270, 810, 70, 70);
Button stop_button(350, 810, 70, 70);

void Interface(sf::RenderWindow &window) {
    Text text_by_car(30, 20, 25, "Number of couriers by car");
    text_by_car.draw(window);
    input_by_car_button.setImage("images/ok.png");
    input_by_car_button.draw(window);
    input_by_car.draw(window);
    Text text_foot(30, 105, 25, "Number of foot couriers");
    text_foot.draw(window);
    input_foot_button.setImage("images/ok.png");
    input_foot_button.draw(window);
    input_foot.draw(window);

    start_button.setImage("images/start.png");
    start_button.draw(window);
    pause_button.setImage("images/pause.png");
    pause_button.draw(window);
    stop_button.setImage("images/stop.png");
    stop_button.draw(window);
    slow_button.setImage("images/slow.png");
    slow_button.draw(window);
    fast_button.setImage("images/fast.png");
    fast_button.draw(window);

    // Text interval_text(30, 250, 25, "Interval:");
    // interval_text.draw(window);
    // interval_plus_first.setImage("images/plus.png");
    // interval_plus_first.draw(window);
    // interval_field_first.draw(window);
    // interval_minus_first.setImage("images/minus.png");
    // interval_minus_first.draw(window);

    // interval_plus_second.setImage("images/plus.png");
    // interval_plus_second.draw(window);
    // interval_field_second.draw(window);
    // interval_minus_second.setImage("images/minus.png");
    // interval_minus_second.draw(window);

    Text deviation_text(30, 400, 25, "Delivery time deviation:");
    deviation_text.draw(window);
    deviation_plus_first.setImage("images/plus.png");
    deviation_plus_first.draw(window);
    deviation_field_first.draw(window);
    deviation_minus_first.setImage("images/minus.png");
    deviation_minus_first.draw(window);

    deviation_plus_second.setImage("images/plus.png");
    deviation_plus_second.draw(window);
    deviation_field_second.draw(window);
    deviation_minus_second.setImage("images/minus.png");
    deviation_minus_second.draw(window);

    set_couriers.setText("Set couriers", 25);
    set_couriers.draw(window);

    Text current_time_text(30, 760, 30, "TIME ");
    current_time_text.draw(window);
}

void HandleEvent(sf::Event event) {
    if (event.type == sf::Event::MouseMoved) {
        mouse_x = event.mouseMove.x;
        mouse_y = event.mouseMove.y;
    }
}

void HandleIntervals(sf::Event event) {
    // if (interval_field_first.getText().length() == 0)
    //     interval_field_first.updateText("2");
    // if (interval_field_second.getText().length() == 0)
    //     interval_field_second.updateText("20");
    if (deviation_field_first.getText().length() == 0)
        deviation_field_first.updateText("-5");
    if (deviation_field_second.getText().length() == 0)
        deviation_field_second.updateText("30");

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // if (interval_minus_first.isClicked(event)) {
            //     std::string str = interval_field_first.getText();
            //     int num = std::stoi(str);
            //     num = std::max(2, num - 1);
            //     interval_field_first.updateText(std::to_string(num));
            // }
            // if (interval_plus_first.isClicked(event)) {
            //     std::string str = interval_field_first.getText();
            //     int num = std::stoi(str);
            //     num = std::min(std::stoi(interval_field_second.getText()) -
            //     1,
            //                    num + 1);
            //     interval_field_first.updateText(std::to_string(num));
            // }
            // if (interval_minus_second.isClicked(event)) {
            //     std::string str = interval_field_second.getText();
            //     int num = std::stoi(str);
            //     num = std::max(num - 1,
            //                    std::stoi(interval_field_first.getText()) +
            //                    1);
            //     interval_field_second.updateText(std::to_string(num));
            // }
            // if (interval_plus_second.isClicked(event)) {
            //     std::string str = interval_field_second.getText();
            //     int num = std::stoi(str);
            //     ++num;
            //     interval_field_second.updateText(std::to_string(num));
            // }

            if (deviation_minus_first.isClicked(event)) {
                std::string str = deviation_field_first.getText();
                int num = std::stoi(str);
                num = std::max(-5, num - 1);
                deviation_field_first.updateText(std::to_string(num));
            }
            if (deviation_plus_first.isClicked(event)) {
                std::string str = deviation_field_first.getText();
                int num = std::stoi(str);
                num = std::min(std::stoi(deviation_field_second.getText()) - 1,
                               num + 1);
                deviation_field_first.updateText(std::to_string(num));
            }
            if (deviation_minus_second.isClicked(event)) {
                std::string str = deviation_field_second.getText();
                int num = std::stoi(str);
                num = std::max(num - 1,
                               std::stoi(deviation_field_first.getText()) + 1);
                deviation_field_second.updateText(std::to_string(num));
            }
            if (deviation_plus_second.isClicked(event)) {
                std::string str = deviation_field_second.getText();
                int num = std::stoi(str);
                ++num;
                deviation_field_second.updateText(std::to_string(num));
            }
            deviation.first = std::stoi(deviation_field_first.getText());
            deviation.second = std::stoi(deviation_field_second.getText());
        }
    }
}

void HandleInputs(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (input_by_car_button.isClicked(event) ||
                !input_by_car.isClicked(event)) {
                input_by_car.notClicked();
                if (input_by_car.getText().length() == 0)
                    car_courier_amount = 0;
                else
                    car_courier_amount = std::stoi(input_by_car.getText());
            } else
                input_by_car.clicked();
            if (input_foot_button.isClicked(event) ||
                !input_foot.isClicked(event)) {
                input_foot.notClicked();
                if (input_foot.getText().length() == 0)
                    default_courier_amount = 0;
                else
                    default_courier_amount = std::stoi(input_foot.getText());
            } else
                input_foot.clicked();
        }
    }
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            char symb = static_cast<char>(event.text.unicode);
            if (input_by_car.isActive()) {
                if (std::stoi(input_by_car.getText() + symb) <= 5)
                    input_by_car.updateText(input_by_car.getText() + symb);
            } else if (input_foot.isActive()) {
                if (std::stoi(input_foot.getText() + symb) <= 5)
                    input_foot.updateText(input_foot.getText() + symb);
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace) {
            if (input_by_car.isActive()) {
                if (input_by_car.getText().length() > 0) {
                    std::string str = input_by_car.getText().erase(
                        input_by_car.getText().length() - 1, 1);
                    input_by_car.updateText(str);
                }
            } else if (input_foot.isActive()) {
                if (input_foot.getText().length() > 0) {
                    std::string str = input_foot.getText().erase(
                        input_foot.getText().length() - 1, 1);
                    input_foot.updateText(str);
                }
            }
        }
    }
}

void HandleClickBranch(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (event.mouseButton.x >= 350) {
                Branch *prev = nullptr;
                Branch *cur = nullptr;
                for (int i = 0; i < branches.size(); ++i) {
                    if (branches[i]->isClicked(event) && cur == nullptr) {
                        cur = branches[i];
                        branches[i]->clicked();
                    } else if (branches[i]->isActive() && prev == nullptr)
                        prev = branches[i];
                }
                if (cur == nullptr && branches.size() < 7) {
                    CreateBranch(event.mouseButton.x, event.mouseButton.y,
                                 prev);
                    BranchesNotActive();
                } else if (cur != nullptr && prev != nullptr) {
                    CreateExistBranch(prev, cur);
                    BranchesNotActive();
                }
            }
        }
    }
}

void CreateBranch(double x, double y, Branch *&prev) {
    Branch *new_branch =
        new Branch(x - 75 / 2.0, y - 45 / 2.0, (int)branches.size() + 1);
    branches.push_back(new_branch);
    branches_map[branches.size() - 1] = new_branch;
    if (prev != nullptr) {
        branches_list.push_back({new_branch, prev});
    }
}

void CreateExistBranch(Branch *&prev, Branch *&cur) {
    branches_list.push_back({cur, prev});
}

void DrawBranches(sf::RenderWindow &window) {
    for (int i = 0; i < branches_list.size(); ++i) {
        auto br = branches_list[i];
        Line line(br.first->getX() + 75 / 2.0, br.first->getY() + 45 / 2.0,
                  br.second->getX() + 75 / 2.0, br.second->getY() + 45 / 2.0);
        line.draw(window);
    }
    for (int i = 0; i < branches.size(); ++i) {
        branches[i]->draw(window);
    }
}

void CheckLines(sf::RenderWindow &window) {
    for (int i = 0; i < branches.size(); ++i) {
        if (branches[i]->isActive()) {
            Line line(branches[i]->getX() + 75 / 2.0,
                      branches[i]->getY() + 45 / 2.0, mouse_x, mouse_y);
            line.draw(window);
        }
    }
}

bool HandleSetCouriers(sf::Event event, bool &is_set) {
    if (set_couriers.isClicked(event)) {
        if (set_couriers.isActive())
            set_couriers.notClicked();
        else if (default_courier_amount != 0 && car_courier_amount != 0) {
            set_couriers.clicked();
            return true;
        }
    }
    if (set_couriers.isActive()) {
        for (int i = 0; i < branches.size(); ++i) {
            if (branches[i]->isClicked(event)) {
                if (default_courier_list.size() < default_courier_amount) {
                    default_courier_list.push_back(
                        {default_courier_list.size() + car_courier_list.size() +
                             1,
                         branches[i]->getNum() - 1});
                } else if (car_courier_list.size() < car_courier_amount) {
                    car_courier_list.push_back({default_courier_list.size() +
                                                    car_courier_list.size() + 1,
                                                branches[i]->getNum() - 1});
                }
                return true;
            }
        }
    }
    if (car_courier_list.size() == car_courier_amount &&
        default_courier_list.size() == default_courier_amount) {
        set_couriers.notClicked();
        is_set = true;
    }
    return false;
}

void BranchesNotActive() {
    for (int i = 0; i < branches.size(); ++i) {
        branches[i]->notClicked();
    }
}

bool HandleStart(sf::Event event) {
    if (start_button.isClicked(event)) return true;
    return false;
}