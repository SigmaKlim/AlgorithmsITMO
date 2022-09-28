#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
//bool GetLanguage();
//bool SetLanguage(const std::string lang);
//bool PrintInvalidInput();
void WaitUntilEnterPressed();
bool GetLineFromFile(std::string& output, const std::string fileName);
bool GetTextFromFile(std::string& output, const std::string fileName);
bool PrintTextFromFile(const std::string fileName);
int ConvertInput(const std::string input);

//bool DisplayMainMenu();
