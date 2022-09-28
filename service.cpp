#include "service.h"

extern std::string textPath;

int ConvertInput(const std::string input)
{
	if (isdigit(input[0]))
		return std::stoi(input);
	else
		return -1;
}
void PrintToLog(const std::string message)
{
	std::ofstream fout("log.txt");
	fout << time(0) << " - " << message << "\n";
}
//bool GetLineFromFile(std::string& output, const std::string fileName)
//{
//	std::ifstream fin(fileName);
//	if (fin)
//	{
//		fin >> output;
//		return true;
//	}
//	else
//	{
//		output = "ERROR";
//		PrintToLog("can't open " + fileName);
//		return false;
//	}
//}

bool GetTextFromFile(std::string& output, const std::string fileName)
{
	std::ifstream fin(fileName);
	if (fin)
	{
		std::string line;
		while (std::getline(fin, line))
			output += (line + '\n');
		output += '\0';
		return true;
	}
	else
	{
		output = "ERROR";
		PrintToLog("can't open " + fileName);
		return false;
	}
}

//bool PrintTextFromFile(const std::string fileName)
//{
//	std::string text;
//	if (GetTextFromFile(text, fileName))
//	{
//		std::cout << text + '\n';
//		return true;
//	}
//	else
//		return false;
//}

void WaitUntilEnterPressed()
{
	std::string e;
	std::cin.ignore();
	std::getline(std::cin, e);
}
