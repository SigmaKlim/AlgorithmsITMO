#pragma once
#include <iostream>
#include <string>
#include "service.h"

struct City
{
	std::string name;

	float accumStarvedToDeath;

	int population;
	int area;
	int wheat;
};
struct Turn
{
	City city;
	int turnNumber;
	int starvedToDeath;
	int newComers;
	bool wasPlague;
	int totalHarvest;
	int harvestPerAcre;
	int harvestEatenByRats;
	int acreCost;
};

struct Input
{
	int acresToBuy;
	int acresToSell;
	int bushelsToEat;
	int acresToSow;
};
void Start(Turn& turn, const std::string name);
bool UpdateParam(Turn& turn, Input input); //returns false if at this turn the player loses the game
bool LoadFromFile(Turn& turn);
bool Save(const Turn turn);
void PrintMainMenu();
void PrintRules();
void PrintCityStats(const City& city);
void PrintTurnResults(const Turn& turn);
void PrintTotalResults(const City city);