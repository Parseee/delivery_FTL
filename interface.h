#pragma once
#include <SFML/Graphics.hpp>
#include "gui.h"

void Interface(sf::RenderWindow &window);
void HandleEvent(sf::Event event);
void CreateBranch(double x, double y, Branch *&prev);
void DrawBranches(sf::RenderWindow &window);
void CheckLines(sf::RenderWindow &window);