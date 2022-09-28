#include "mechanics.h"
#include <ctime>

bool LoadFromFile(Turn& turn)
{
	std::string sSaveData;
	if (!GetTextFromFile(sSaveData, "save.txt"))
		return false;
	size_t separ = sSaveData.find('\n');
	turn.city.name = sSaveData.substr(0, separ);
	size_t anotherSepar = sSaveData.find('\n', separ + 1);
	turn.city.accumStarvedToDeath = stof(sSaveData.substr(separ, anotherSepar - separ));
	int iSaveData[11];
	for (size_t i = 0; i < 11; i++)
	{
		separ = anotherSepar + 1;
		anotherSepar = sSaveData.find('\n', separ + 1);
		iSaveData[i] = stoi(sSaveData.substr(separ, anotherSepar - separ));
	}
	turn.city.population = iSaveData[0];
	turn.city.area = iSaveData[1];
	turn.city.wheat = iSaveData[2];
	turn.turnNumber = iSaveData[3];
	turn.starvedToDeath = iSaveData[4];
	turn.newComers = iSaveData[5];
	turn.wasPlague = iSaveData[6];
	turn.totalHarvest = iSaveData[7];
	turn.harvestPerAcre = iSaveData[8];
	turn.harvestEatenByRats = iSaveData[9];
	turn.acreCost = iSaveData[10];
	return true;
}
void Start(Turn& turn, const std::string name)
{
	turn.city.name = name;
	turn.city.population = 100;
	turn.city.area = 1000;
	turn.city.wheat = 2800;
	turn.city.accumStarvedToDeath = 0;
	turn.turnNumber = 1;
}

bool UpdateParam(Turn& turn, Input input)
{
	turn = { turn.city, turn.turnNumber, 0, 0, 0, 0, 0, 0, 0 };
	const int kHarvestPerAcreLowerLimit = 1;
	const int kHarvestPerAcreUpperLimit = 6;
	const int kHarvestEatenByRatsLowerLimitPercent = 1;
	const int kHarvestEatenByRatsUpperLimitPercent = 7;
	const int kBushelsPerPerson = 20;
	const float kMaxStarvedToDeathPart = 0.45;
	const int kPlagueProbabilityPercent = 15;

	turn.turnNumber++;
	turn.city.wheat -= input.acresToSow / 2;
	turn.city.area += input.acresToBuy - input.acresToSell;
	turn.city.wheat -= (input.acresToBuy - input.acresToSell) * turn.acreCost;
	turn.harvestPerAcre = kHarvestPerAcreLowerLimit + rand() % kHarvestPerAcreUpperLimit + 1;
	turn.totalHarvest = turn.harvestPerAcre * input.acresToSow;
	turn.city.wheat += turn.totalHarvest;
	turn.harvestEatenByRats = float(kHarvestEatenByRatsLowerLimitPercent + rand() % kHarvestEatenByRatsUpperLimitPercent + 1) / 100 * turn.city.wheat;
	turn.city.wheat -= turn.harvestEatenByRats; 
	int canEat = input.bushelsToEat / kBushelsPerPerson;
	int wheatConsumed = turn.city.population * kBushelsPerPerson;
	if (wheatConsumed <= input.bushelsToEat)
	{
		turn.city.wheat -= wheatConsumed;
		turn.starvedToDeath = 0;
	}
	else
	{
		turn.city.wheat -= canEat * kBushelsPerPerson;
		turn.starvedToDeath = turn.city.population - canEat;
		if (float(turn.starvedToDeath) / turn.city.population > kMaxStarvedToDeathPart)
			return false;
		turn.city.population = canEat;
		turn.city.accumStarvedToDeath += float(turn.starvedToDeath) / 10 / turn.city.population;
	}
	turn.newComers = turn.starvedToDeath / 2 + (5 - turn.harvestPerAcre) * turn.city.wheat / 600 + 1;
	turn.newComers = (turn.newComers < 0) ? 0 : (turn.newComers > 50) ? 50 : turn.newComers;
	turn.city.population += turn.newComers;
	if (rand() % 101 < kPlagueProbabilityPercent + 1)
	{
		turn.wasPlague = true;
		turn.city.population /= 2;
	}
	else
		turn.wasPlague = false;
	input = { 0, 0, 0, 0 };
	return true;
}

bool Save(const Turn turn)
{
	std::ofstream fout("save.txt");
	if (fout)
	{
		std::string saveInfo = turn.city.name + '\n';
		saveInfo += std::to_string(turn.city.accumStarvedToDeath) + '\n';
		saveInfo += std::to_string(turn.city.population) + '\n';
		saveInfo += std::to_string(turn.city.area) + '\n';
		saveInfo += std::to_string(turn.city.wheat) + '\n';
		saveInfo += std::to_string(turn.turnNumber) + '\n';
		saveInfo += std::to_string(turn.starvedToDeath) + '\n';
		saveInfo += std::to_string(turn.newComers) + '\n';
		saveInfo += std::to_string(turn.wasPlague) + '\n';
		saveInfo += std::to_string(turn.totalHarvest) + '\n';
		saveInfo += std::to_string(turn.harvestPerAcre) + '\n';
		saveInfo += std::to_string(turn.harvestEatenByRats) + '\n';
		saveInfo += std::to_string(turn.acreCost) + '\n';
		fout << saveInfo;
		return 1;
	}
	else
		return 0;
}
void PrintMainMenu()
{
	std::cout << "Welcome to Glorious Ruler of Egypt!\n\n\t1. Load the last game\n\t2. Start a new game\n\t3. Read the rules\n\t4. Exit\n\nTo pick a point from the menu press the corresponding number + ENTER\n";
}
void PrintRules()
{
	std::cout << "In this game you play as a ruler of an Egyptian city. The game is turn-based and consists of 10 rounds. Each round\nrepresents a year. Your task is to manage city resources in order to achieve its wealth.\nThe resourses are:\n\t1. Population : how many people live in your city. Each citizen can cultivate a number of acres of land per\nyear. In case of lack of food, citizens die. If more than 45 percent of the city population die of starvation in\none year, the game is over.\n\t2. Wheat: how many bushels of wheat you have in your barns. It is grown on the land of your city.A bushel can\neither be eaten or its seeds may be used to grow more wheat. Otherwise, it is kept in storage. Furthermore, you can\nuse bushels from your storage as currency to buy or sell land.\n\t3. Land: how many acres of land your city occupies. The more acres you have, the more wheat can grow up in a\nyear.\n\nPress ENTER to return to the main menu.\n";
}
void PrintCityStats(const City& city)
{
	std::cout << "CITY: " << city.name << "   \tPOPULATION: " << city.population << "\tAREA: " << city.area << "\tWHEAT: " << city.wheat << "\n\n";
}
void PrintTurnResults(const Turn& turn)
{
	system("cls");
	PrintCityStats(turn.city);
	std::cout << "My Lord, allow me to inform you about the news in our great capital " << turn.city.name << ".\n\n";
	std::cout << "It is year " << turn.turnNumber << " of your blessed reign.";
	if (turn.turnNumber == 10)
		std::cout << " Remember it is the last year of your reign, my Lord.\n";
	else
		std::cout << '\n';
	if(turn.starvedToDeath)
		std::cout << turn.starvedToDeath << " citizens have deceased due to starvation.\nOn the other hand, ";
	if (turn.newComers)
		std::cout << turn.newComers << " people have arrived to " << turn.city.name << ".\n";
	if (turn.wasPlague)
		std::cout << "Unfortunately, a horrible plague pandemic burst out and half of the city population fell victims to it.\n";
	std::cout << "Our farmers harvested " << turn.harvestPerAcre << " bushels of wheat from an acre making the total harvest equal " << turn.totalHarvest << "\n";
	std::cout << "Today I was told that disgusting rats devoured " << turn.harvestEatenByRats << " bushels of our finest wheat. What a misery!\n";
	float P = turn.city.accumStarvedToDeath * 100;
	int L = float(turn.city.area) / turn.city.population;
}
void PrintTotalResults(const City city)
{
	float P = city.accumStarvedToDeath * 100;
	int L = float(city.area) / city.population;
	system("cls");
	PrintCityStats(city);
	std::cout << "Yout reign is over! Your results are displayed below:\n";
	std::cout << "Death rate due to starvation: " << P << " %\n";
	std::cout << "Area per 1 citizen: " << L << " acres\n";

	if (P > 33 && L < 7)
		std::cout << "\nYOUR GRADE: D. Your reign was a complete failure. Those peasants who hadn't died of starvation banished you to the\nburning sands of The Desert. Your are doomed to inglorious death...";
	else if (P > 10 && L < 9)
		std::cout << "\nYOUR GRADE: C. Some future historians will put you on a par with Ivan the Terrible and Nero. As your reign came to an\nend, the people of your city sighed with a relief: no one will vote for you anymore...";
	else if (P > 3 && L < 10)
		std::cout << "\nYOUR GRADE: B. You did pretty well. Of course, you made some mistakes in your orders, but who doesn't. Furthermore,\naccording to preliminary vote, some would like to see as their ruler again...";
	else
		std::cout << "\nYOUR GRADE: A. Magnificent! You are a natural born ruler! Your actions were flawless and thoroughly planned. Your rule\nwill be remembered as the time of wealth and prosperity...";
}