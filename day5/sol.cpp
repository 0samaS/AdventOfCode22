#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

void parseAndBuild(std::ifstream& file, std::vector<std::deque<char>>& towers)
{
    std::string input;
    std::getline(file, input);
    towers.resize(input.size() / 4);

    file.clear();
    file.seekg( 0, std::ios_base::beg );

    while (std::getline(file, input))
    {
        if (input[1] == '1') break;
        for (int i = 0; i < input.size() / 4; ++i)
        {
            if (input[i*4 + 1] != ' ')towers[i].push_front(input[i*4 + 1]);
        }
    }
}

std::string part1(std::ifstream& file)
{
    std::vector<std::deque<char>> towers;

    parseAndBuild(file, towers);
    int num_to_move;
    int src; 
    int dest;
    std::string dummy;

    while (file >> dummy >> num_to_move >> dummy >> src >> dummy >> dest)
    {
        for (int i = 0; i < num_to_move; ++i)
        {
            towers[dest-1].push_back(towers[src-1].back());
            towers[src-1].pop_back();
        }
        

    }

    std::string res = "";
    for (int i = 0; i < towers.size(); ++i)
    {
        res += towers[i].back();
    }
    return res;
}

std::string part2(std::ifstream& file)
{
    std::vector<std::deque<char>> towers;

    parseAndBuild(file, towers);
    int num_to_move;
    int src; 
    int dest;
    std::string dummy;

    while (file >> dummy >> num_to_move >> dummy >> src >> dummy >> dest)
    {
        std::deque<char> temp;
        for (int i = 0; i < num_to_move; ++i)
        {
            temp.push_front(towers[src-1].back());
            towers[src-1].pop_back();
        }
        while(!temp.empty())
        {
            towers[dest-1].push_back(temp.front());
            temp.pop_front();
        }

    }

    std::string res = "";
    for (int i = 0; i < towers.size(); ++i)
    {
        res += towers[i].back();
    }
    return res;
}

int main()
{
    std::ifstream file ("data.txt");

    // std::cout << part1(file) << std::endl;
    std::cout << part2(file) << std::endl;

    return 0;
}