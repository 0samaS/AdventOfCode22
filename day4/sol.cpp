#include <iostream>
#include <fstream>

int part1(std::ifstream& file)
{
    int p1_start;
    int p1_end;
    int p2_start;
    int p2_end;
    char dummy; 

    int count_pairs = 0;

    while(file >> p1_start && file >> dummy && file >> p1_end && file >> dummy &&
          file >> p2_start && file >> dummy && file >> p2_end)
    {
        if (p1_start == p2_start && p1_end == p2_end)
        {
            count_pairs++;
        }
        else if (p1_start >= p2_start && p1_end <= p2_end)
        {
            count_pairs++;
        }
        else if (p2_start >= p1_start && p2_end <= p1_end)
        {
            count_pairs++;
        }

    }

    return count_pairs;
}

int part2(std::ifstream& file)
{
    int p1_start;
    int p1_end;
    int p2_start;
    int p2_end;
    char dummy; 

    int count_pairs = 0;

    while(file >> p1_start && file >> dummy && file >> p1_end && file >> dummy &&
          file >> p2_start && file >> dummy && file >> p2_end)
    {
        if (p1_start >= p2_start && p1_start <= p2_end)
        {
            count_pairs++;
        }
        else if (p2_start >= p1_start && p2_start <= p1_end)
        {
            count_pairs++;
        }
        else if (p1_end <= p2_end && p1_end >= p2_start)
        {
            count_pairs++;
        }
        else if (p2_end <= p1_end && p2_end >= p1_start)
        {
            count_pairs++;
        }

    }

    return count_pairs;
}

int main()
{
    std::ifstream file ("data.txt");

    // std::cout << part1(file) << std::endl;
    std::cout << part2(file) << std::endl;

    return 0;
}