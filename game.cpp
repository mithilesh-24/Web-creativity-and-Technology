#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cctype>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <cmath>


#ifdef _WIN32
#include <windows.h> 
#endif

//struct to store the question
struct Question {
    std::string questionText;
    std::string options[4];
    char correctOption;
};


//to set color
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}


void printCentered(const std::string& text) {

    const int consoleWidth = 80; 
    int textLength = text.length();
    int padding = (consoleWidth - textLength) / 2;
    for (int i = 0; i < padding; i++) {
        std::cout << " ";
    }
    std::cout << text << std::endl;
}
