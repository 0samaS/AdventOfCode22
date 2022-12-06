#include <iostream>
#include <fstream>
#include <set>
#include <deque>


int sol(std::ifstream& file, int length)
{
    std::string input;

    file >> input;
    std::deque<char> unique;
    char char_to_del = input[0];
    for (int i = 0; i < input.size(); ++i)
    {
        if(unique.size() == length)
        {
            std::set<char> u_set;
            for (int j = 0; j < unique.size(); ++j)
            {
                u_set.insert(unique[j]);
            }
            if (u_set.size() == length) return i;
            unique.pop_front();
        }
        unique.push_back(input[i]);
    }
    return 0;
}

int main()
{
    std::ifstream file ("data.txt");

    // part 1
    // std::cout << sol(file, 4) << std::endl;
    // part 2
    std::cout << sol(file, 14) << std::endl;

    return 0;
}