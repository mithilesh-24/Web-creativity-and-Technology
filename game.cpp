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
void countdown(int seconds) {
    for (int i = seconds; i >= 0; --i) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        std::cout << "⏳ Get Ready! Starting in: " << i << " seconds...\n";
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }
    std::cout << "🚦 Go!\n";
}

//question
void askQuestion(const Question& q, const std::string& playerName, int& score, int& position,int& wrong) {
    std::cout << "\n🚦 " << playerName << "'s Turn\n";
    std::cout << "Q: " << q.questionText << "\n";
    for (const auto& opt : q.options) std::cout << opt << "\n";

    auto start = std::chrono::high_resolution_clock::now();
    char answer;
    std::cout << "Your answer (A/B/C/D): ";
    std::cin >> answer;
    
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    double speed = 0,distance=0;int move=0;
    double timeTaken = std::min(elapsed.count(), 60.0);
    double clampedTime = std::min(timeTaken, 60.0);
    if (elapsed.count() > 60) {

        setColor(12, 0);
        std::cout << "⏰ Time's up!\n";
        Beep(300, 300);
        setColor(15, 0);
        move=-1;
        position += move;
        if(position < 0)position=0;

    } else if (toupper(answer) == q.correctOption) {


        speed = 5.0 - (2.0 * clampedTime / 60.0);

        
        distance = speed * (clampedTime / 60.0);
        move = std::max(3, std::min(5, (int)std::round(distance)));
        
        setColor(10, 0);
        std::cout << "✅ Correct!\n";
        setColor(15, 0);
        Beep(1000, 300);
        position += move;
        score++;

    } else {

        move = 1;

        speed = 1.0 - (clampedTime / 60.0);
        speed = std::max(0.1, speed);

        setColor(12, 0);
        wrong++;
        std::cout << "❌ Wrong! Correct answer was " << q.correctOption << "\n";
        Beep(400, 300);
        setColor(15, 0);

        position+=move;

        std::random_device rd;
        std::mt19937 gen(rd());
        
        
        if(position>1){
            int frictionChance = std::min(57 + (wrong - 1) * 3, 90); 
            std::uniform_int_distribution<> frictionRoll(1, 100);
            if (frictionRoll(gen) <= frictionChance) {
                std::uniform_int_distribution<> frictionLoss(1, 2);
                int friction = frictionLoss(gen);
                position = std::max(0, position - friction);
                std::cout << "🛑 Friction occurred! -" << friction << " units (Chance: " << frictionChance << "%)\n\n";
            }
        }     
    }

    setColor(10, 0);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n\n⏱️ Time Taken: " << clampedTime << "s\n";
    std::cout << "Your car Speed: " << speed << " units/sec\n";
    std::cout << "📏 Distance moved: " << move << " units\n\n";
    setColor(15, 0);
}



