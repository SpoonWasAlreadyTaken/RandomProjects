#include <iostream>
#include <string>
#include <chrono>
#include <array>



std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
std::chrono::duration<float> elapsed_seconds = start - end;
float dt = elapsed_seconds.count(); 

std::string text = "";
std::string output = "";
constexpr uint32_t maxRGB = 6;
int ticker = 0;
std::array<std::string, maxRGB> rgb = {"\e[1;91m","\e[1;95m","\e[1;94m","\e[1;96m","\e[1;92m","\e[1;93m"};
//std::array<std::string, maxRGB> rgb = {"\e[1;91m","\e[1;95m","\e[1;94m","\e[1;96m","\e[1;92m","\e[1;93m"};

float timer = 0;


inline int Tick();
inline int WordTick(int i, int size);



int main()
{
    while (true)
    {
        std::cout << "Input text to rainbow\n";
        std::getline (std::cin, text);
        std::cout << "\033[2J\033[H";
        
        if (text == "q" || text == "quit") break;


        while (true)
        {   

            start = std::chrono::system_clock::now();
            elapsed_seconds = start - end;
            dt = elapsed_seconds.count();
            timer += dt;

            if (timer > 0.05)
            {
                timer = 0;
                output = "";
                std::cout << "\033[2J\033[H";

                for (int i = 0; i < text.size(); i++)
                {
                    output += rgb[WordTick(i, 5)] + text[i];
                }
                Tick();
                
                std::cout << output << "\n\n\n"; 
                std::cout << "\e[0m" << "DEBUG | " << "Ticker: " << ticker << "\n";
            }


            end = start;
        }

    }
}




inline int Tick()
{
    ticker++;
    ticker = ticker * (ticker < maxRGB);
    return ticker;
}

inline int WordTick(int i, int size)
{
    return (ticker + i) % maxRGB; 
}
