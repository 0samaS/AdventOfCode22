#include <iostream>
#include <fstream>
#include <unordered_map>

int calculate_priority(char c)
{
    return islower(c) ? (int)c - 96 : (int)c - 38;
}

int part1(std::ifstream& file)
{
    int total_priority = 0;
    std::string input;
    while (std::getline(file, input))
    {
        std::unordered_map<char, int> freq;
        int half_size = input.size() / 2;
        std::string first_half = input.substr(0, half_size);
        std::string second_half = input.substr(half_size, half_size);

        for (char c : first_half)
        {
            freq[c]++;
        }
        for (char c : second_half)
        {
            if (freq.count(c))
            {
                total_priority += calculate_priority(c);
                break;
            }
        }
    }
    return total_priority;
}

int part2(std::ifstream& file)
{
    std::string elf1, elf2, elf3;
    int total_priority = 0;

    while (file >> elf1 >> elf2 >> elf3)
    {
        std::unordered_map<char, int> freq;

        for (char c : elf1)
        {
            if (!freq.count(c)) freq[c]++;
        }
        for (char c : elf2)
        {
            if (freq.count(c) && freq[c] == 1)
            {
                freq[c]++;
            }
        }
        for (char c : elf3)
        {
            if (freq.count(c) && freq[c] == 2) 
            {
                total_priority += calculate_priority(c);
                break;
            }
        }
    }
    return total_priority;
}

int main()
{
    std::ifstream file ("data.txt");

    // std::cout << part1(file) << std::endl;
    std::cout << part2(file) << std::endl;

    return 0;
}