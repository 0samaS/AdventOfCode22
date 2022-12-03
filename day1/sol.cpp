#include <iostream>
#include <queue>

using namespace std;

int main()
{
    
    string calories_in;
    priority_queue <int, vector<int>, greater<int> > max_calories_for_elf;
    
    while(!cin.eof())
    {
        int current_count = 0;
        while (getline(cin, calories_in)) {
            if (calories_in.size() == 0)
            {
                if (max_calories_for_elf.size() < 3 || current_count > max_calories_for_elf.top())
                {
                    if (max_calories_for_elf.size() == 3) max_calories_for_elf.pop();
                    max_calories_for_elf.push(current_count);
                }
                break;
            }
            current_count += stoi(calories_in);
        }
    }
    int total_count = 0;
    while (!max_calories_for_elf.empty())
    {
        cout<<max_calories_for_elf.top() << endl;
        total_count += max_calories_for_elf.top();
        max_calories_for_elf.pop();

    }
    cout << total_count;
    return 0;
}
