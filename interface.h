#pragma once
#include <SFML/Graphics.hpp>

void Interface(sf::RenderWindow &window);
void HandleEvent(sf::Event event, sf::RenderWindow &window);
void CreateBranch(double x, double y);
void DrawBranches(sf::RenderWindow &window);