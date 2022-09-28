#include <ctime>
#include "service.h"
#include "mechanics.h"
//std::string textPath = "text\\";

int main()
{
	const int kAcreCostUpperLimit = 26;
	const int kAcreCostLowerLimit = 17;
	srand(time(0));
	int iCommandInput = 0;
	/*City city;*/
	Turn turn;
	while (1)
	{
		while ((iCommandInput != 1) && (iCommandInput != 2))
		{
			system("cls");
			PrintMainMenu();
			std::string sInputCommand;
			std::cin >> sInputCommand;
			iCommandInput = ConvertInput(sInputCommand);
			switch (iCommandInput)
			{
			case 1:
				system("cls");
				LoadFromFile(turn);
				break;
			case 2:
			{
				system("cls");
				std::cout << "Please, type in the name for your great city:\n";
				std::string name;
				std::cin >> name;
				system("cls");
				Start(turn, name);
			}
			break;
			case 3:
				system("cls");
				PrintRules();
				WaitUntilEnterPressed();
				break;
			case 4:
				return 0;
			default:
				std::cout << "Invalid input! Press Enter.\n";
				WaitUntilEnterPressed();
				break;
			}
		}
		
		bool hasNotLost = 1;
		do
		{
			Input input = {0, 0, 0, 0};
			iCommandInput = 0;
			turn.acreCost = kAcreCostLowerLimit + rand() % kAcreCostUpperLimit + 1;
			while (iCommandInput != 5)
			{
				system("cls");
				PrintCityStats(turn.city);
				if (turn.turnNumber > 1)
					PrintTurnResults(turn);
				else
				{
					std::cout << "My Lord, I welcome you as the new ruler of our city of " << turn.city.name << "!\n";
				}
				std::cout << "Each acre of land costs " << turn.acreCost << " bushels.\n";

				std::cout << "\nMy lord, I am listening to your orders!\n";
				std::cout << "\t1. Purchase some land.\n\t2. Sell some land\n\t3. Let citizens have some wheat for food. \n\t4. Sow some land with wheat.\n\t5. Finish\n\t0. Quit the game\n\n";
				std::cout << "Choose the command by pressing the number + ENTER. Previous order will be revoked.\n\nYour active orders:\n";
				std::cout << "\tLand to purchase: " << input.acresToBuy << " acres.\n";
				std::cout << "\tLand to sell: " << input.acresToSell << " acres.\n";
				std::cout << "\tWheat for food: " << input.bushelsToEat << " bushels.\n";
				std::cout << "\tLand to sow: " << input.acresToSow << " acres.\n";
				std::string sCommandInput;
				std::cin >> sCommandInput;
				iCommandInput = ConvertInput(sCommandInput);
				switch (iCommandInput)
				{
				case 1:
					std::cout << "Purchase some land... How many acres?\n";
					std::cin >> input.acresToBuy;
					if (input.acresToBuy * turn.acreCost > turn.city.wheat + input.acresToSell * turn.acreCost)
					{
						std::cout << "\nMy Lord, we don't have enough wheat. I am begging, rethink your order!\nPress ENTER and try again\n";
						input.acresToBuy = 0;
						WaitUntilEnterPressed();
					}
					break;
				case 2:
					std::cout << "Sell some land... How many acres?\n";
					std::cin >> input.acresToSell;
					if (input.acresToSell  > turn.city.area + input.acresToBuy)
					{
						std::cout << "\nMy Lord, we don't have enough land. I am begging, rethink your order!\nPress ENTER and try again\n";
						input.acresToSell = 0;
						WaitUntilEnterPressed();
					}
					break;
				case 3:
					std::cout << "Give out some wheat for food... How many bushels?\n";
					std::cin >> input.bushelsToEat;
					if (input.bushelsToEat > turn.city.wheat + input.acresToSell * turn.acreCost)
					{
						std::cout << "\nMy Lord, we don't have enough wheat. I am begging, rethink your order!\nPress ENTER and try again\n";
						input.bushelsToEat = 0;
						WaitUntilEnterPressed();
					}
					break;
				case 4:
					std::cout << "Sow some land with wheat.. How many acres?\n";
					std::cin >> input.acresToSow;
					if (input.acresToSow > turn.city.area + input.acresToBuy)
					{
						std::cout << "\nMy Lord, we don't have enough land. I am begging, rethink your order!\nPress ENTER and try again\n";
						input.acresToSow = 0;
						WaitUntilEnterPressed();
					}
					else if (turn.city.population * 10 < input.acresToSow)
					{
						std::cout << "\nMy Lord, we don't have enough people for that much work. I am begging you, rethink your order!\nPress ENTER and try again\n";
						input.acresToSow = 0;
						WaitUntilEnterPressed();
					}
					break;
				case 5:
					break;
				case 0:
				{
					std::cout << "Are you leaving so soon, my Lord?\nPress 0 + ENTER to save the progress; press any other key + ENTER to return to the game.\n";
					std::string sCommandInput_;
					std::cin >> sCommandInput_;
					if (ConvertInput(sCommandInput_) == 0)
					{
						if (Save(turn))
							std::cout << "\nProgress saved. Press ENTER to quit.\n";
						else
							std::cout << "\nSaving error. Press ENTER to quit.";
						WaitUntilEnterPressed();
						return 0;
					}
				}
					break;
				default:
					std::cout << "I do not understand you, my Lord. Press ENTER and try again";
					WaitUntilEnterPressed();
					break;
				}
			}
			hasNotLost = UpdateParam(turn, input);
		}
		while (turn.turnNumber < 11 && hasNotLost);

		if (!hasNotLost)
		{
			system("cls");
			std::cout << "My Lord! There is not enough food on out storages! Many have died of hunger. The others are very angry. These filthy\npeasants gathered at the front gate of your castle and they want your head on a pole. I am afraid we have to flee!\n\n";
			std::cout << "GAME OVER!\nPress ENTER to return to the main menu.\n";
			WaitUntilEnterPressed();
		}
		else
		{
			system("cls");
			PrintTotalResults(turn.city);
			std::cout<< "\nPress ENTER to return to the main menu.\n";
			WaitUntilEnterPressed();
		}
	} 
}