#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <memory>
#include <cstdint>

using namespace std;

struct TreeData
{
    TreeData(int8_t in_height)
    {
        height = in_height;
        left_max = in_height;
        up_max = in_height;
        right_max = in_height;
        down_max = in_height;
    }
    int8_t height;
    int8_t left_max;
    int8_t up_max;
    int8_t right_max;
    int8_t down_max;
};

int print_and_count_vis(const std::vector<std::vector<bool>>& vis)
{
    int count = 0;
    for (int row = 0; row < vis[0].size(); ++row)
    {
        for (int col = 0; col < vis.size(); ++col)
        {
            // std::cout << vis[row][col] << " ";
            if (vis[row][col])
                ++count;
        }
        // std::cout << std::endl;
    }
    // std::cout << std::endl;
    return count;
}


void print_forest(const std::vector<std::vector<TreeData>>& forest)
{
    for (int row = 0; row < forest[0].size(); ++row)
    {
        for (int col = 0; col < forest.size(); ++col)
        {
            std::cout << (int)(forest[row][col].height) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void create_forest(std::ifstream& file, std::vector<std::vector<TreeData>>& trees)
{
    std::string input;
    while (file >> input)
    {
        std::vector<TreeData> row;
        for (auto c : input)
        {
            TreeData tree((int8_t)c - 48);
            row.push_back(tree);
        }
        trees.push_back(row);
    }
}

int part1(std::vector<std::vector<TreeData>>& trees)
{
    int row_length = trees[0].size();
    int num_rows = trees.size();

    // vector contains max height seen.
    vector<vector<bool>> vis(num_rows, vector<bool> (row_length, false)); 

    for (int row = 0; row < num_rows; ++row)
    {
        vis[row][0] = true;
        vis[row][row_length-1] = true;
    }
    for (int col = 0; col < row_length; ++col)
    {
        vis[0][col] = true;
        vis[num_rows-1][col] = true;
    }

    for (int row = 1; row < num_rows-1; ++row)
    {
        for (int col = 1; col < row_length-1; ++col)
        {
            // check if height is sufficient to clear maxes
            if (trees[row][col].height > trees[row-1][col].up_max
                || trees[row][col].height > trees[row][col-1].left_max)
            {
                vis[row][col] = 1;
            }
            // update maxes
            trees[row][col].up_max = std::max(trees[row][col].up_max, trees[row-1][col].up_max);
            trees[row][col].left_max = std::max(trees[row][col].left_max, trees[row][col-1].left_max);
        }
    }

    for (int row = num_rows-2; row > 0; --row)
    {
        for (int col = row_length-2; col > 0; --col)
        {
            // check if height is sufficient to clear maxes
            if (trees[row][col].height > trees[row+1][col].down_max
                || trees[row][col].height > trees[row][col+1].right_max)
            {
                vis[row][col] = 1;
            }
            // update maxes
            trees[row][col].down_max = std::max(trees[row][col].down_max, trees[row+1][col].down_max);
            trees[row][col].right_max = std::max(trees[row][col].right_max, trees[row][col+1].right_max);
        }
    }

    return print_and_count_vis(vis);
}

int part2(std::vector<std::vector<TreeData>>& trees)
{
    int row_length = trees[0].size();
    int num_rows = trees.size();

    int max_scenic = 0;

    for (int row = 0; row < num_rows; ++row)
    {
        for (int col = 0; col < row_length; ++col)
        {
            int left_scenic = 0;
            int up_scenic = 0;
            int right_scenic = 0;
            int down_scenic = 0;

            int i = row-1;
            int j = col-1;

            while(i >= 0)
            {
                ++up_scenic;
                if (trees[row][col].height <= trees[i][col].height)
                    break;
                --i;
            }
            while(j >= 0)
            {
                ++left_scenic;
                if (trees[row][col].height <= trees[row][j].height)
                    break;
                --j;
            }

            i = row+1;
            j = col+1;
            while(i < num_rows)
            {
                ++down_scenic;
                if (trees[row][col].height <= trees[i][col].height)
                    break;
                ++i;
            }
            while(j < row_length)
            {
                ++right_scenic;
                if (trees[row][col].height <= trees[row][j].height)
                    break;
                ++j;
            }

            max_scenic = std::max(max_scenic, up_scenic * left_scenic * down_scenic * right_scenic);
        }
    }
    return max_scenic;
}

int main()
{
    std::ifstream file ("data.txt");

    std::vector<std::vector<TreeData>> trees;
    create_forest(file, trees);

    std::cout << "Part 1: " << part1(trees) << std::endl;
    std::cout << "Part 2: " << part2(trees) << std::endl;

    return 0;
}