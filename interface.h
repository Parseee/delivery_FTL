#pragma once
#include <SFML/Graphics.hpp>

#include "gui.h"

void Interface(sf::RenderWindow &window);
void HandleEvent(sf::Event event);
void CreateBranch(double x, double y, Branch *&prev);
void CreateExistBranch(Branch *&prev, Branch *&cur);
void BranchesNotActive();
void DrawBranches(sf::RenderWindow &window);
void CheckLines(sf::RenderWindow &window);

void HandleInputs(sf::Event event);
bool HandleSetCouriers(sf::Event event, bool &is_set);
bool HandleStart(sf::Event event);
bool HandlePause(sf::Event event);
bool HandleStop(sf::Event event);
void HandleIntervals(sf::Event event);
void HandleClickBranch(sf::Event event);