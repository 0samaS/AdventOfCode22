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


struct Inode
{
    Inode(std::string name, std::shared_ptr<Inode> parent, int size, bool is_file) 
            : name_ (name), parent_ (parent), size_ (size), is_file_ (is_file)
    {
    }

    std::string name_;
    std::vector<std::shared_ptr<Inode>> children_;
    std::shared_ptr<Inode> parent_;

    // dir size and file size var
    int size_ = 0;

    bool is_file_ = false;
};

std::shared_ptr<Inode> build_file_structure(std::ifstream& file)
{
    std::string input;
    std::string dummy;
    std::string name;

    std::shared_ptr<Inode> root;
    std::shared_ptr<Inode> current;

    while (std::getline(file, input))
    {
        int file_size = 0;

        std::stringstream ss(input);
        if (input[0] == '$')
        {
            std::string cmd;
            ss >> dummy >> cmd;
            if (cmd == "cd")
            {
                ss >> name;
                if (!root)
                {
                    root = std::make_shared<Inode>(name, nullptr, 0, false);
                    current = root;
                }

                else if (name == ".." && current->parent_)
                {
                    current = current->parent_;
                }
                else {
                    for (auto node_ptr : current->children_)
                    {
                        if (node_ptr->name_ == name)
                        {
                            current = node_ptr;
                            break;
                        }
                    }
                }
            }
            else if (cmd == "ls")
            {
                continue;
            }
        }
        else if (input[0] == 'd')
        {
            ss >> dummy >> name;
            auto new_inode = std::make_shared<Inode>(name, current, 0, false);
            current->children_.push_back(new_inode);
        }
        else
        {
            ss >> file_size >> name;
            auto new_inode = std::make_shared<Inode>(name, current, file_size, true);
            current->children_.push_back(new_inode);
        }
        

    }
    return root;
}

int compute_dir_size(std::shared_ptr<Inode> node)
{
    // leaves are files so no nullptr nodes exist
    if (node->is_file_)
        return node->size_;
    if (node->children_.empty())
        return 0;
    for (auto node_ptr : node->children_)
    {
        node->size_ += compute_dir_size(node_ptr);
    }
    return node->size_;
}

void find_total_sum_below_threshold(std::shared_ptr<Inode> node, int threshold, int& total_sum)
{
    if (node->is_file_ || node->children_.empty())
        return;

    if (node->size_ < threshold) 
        total_sum += node->size_;

    for (auto node_ptr : node->children_)
    {
        find_total_sum_below_threshold(node_ptr, threshold, total_sum);
    }
}

void find_min_sufficient_dir(std::shared_ptr<Inode> node, int goal, int& size_of_candidate)
{
    if (node->is_file_ || node->children_.empty())
        return;

    if (node->size_ >= goal && node->size_ < size_of_candidate)
    {
        size_of_candidate = node->size_;
    }

    for (auto node_ptr : node->children_)
    {
        find_min_sufficient_dir(node_ptr, goal, size_of_candidate);
    }
}

void print_tree(std::shared_ptr<Inode> node, int level)
{
    if (!node)
        return;
    std::cout << std::setw(level) << " " << "- "<< node->name_ << " " << node->size_ << std::endl;

    if (node->children_.empty())
        return;

    for (auto node_ptr : node->children_)
    {
        print_tree(node_ptr, level + 1);
    }
}

int part1(std::shared_ptr<Inode> root, int root_size)
{
    int total_sum = 0;
    find_total_sum_below_threshold(root, 100000, total_sum);

    return total_sum;
}

int part2(std::shared_ptr<Inode> root, int root_size)
{
    int total_space = 70000000;
    int needed_space = 30000000;
    int current_unused = total_space - root_size;

    int size_of_candidate = 80000000;
    find_min_sufficient_dir(root, needed_space - current_unused, size_of_candidate);

    return size_of_candidate;
}

int main()
{
    std::ifstream file ("data.txt");
    auto root = build_file_structure(file);
    int root_size = compute_dir_size(root);
    // print_tree(root, 0);

    std::cout << part1(root, root_size) << std::endl;
    std::cout << part2(root, root_size) << std::endl;

    return 0;
}