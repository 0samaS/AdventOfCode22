/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>

using namespace std;


int part1()
{
    char in1;
    char in2;
    
    int score = 0;
    while (cin >> in1 >> in2)
    {
        //rock
        if (in2 == 'X')
        {
            score += 1;
            if (in1 == 'A'){
                score += 3;
            }
            if (in1 == 'B'){
                score += 0;
            }
            if (in1 == 'C'){
                score += 6;
            }
        }
        //paper
        else if (in2 == 'Y') 
        {
            score += 2;
            if (in1 == 'A'){
                score += 6;
            }
            if (in1 == 'B'){
                score += 3;
            }
            if (in1 == 'C'){
                score += 0;
            }
        }
        //scissors
        else if (in2 == 'Z')
        {
            score += 3;
            if (in1 == 'A'){
                score += 0;
            }
            if (in1 == 'B'){
                score += 6;
            }
            if (in1 == 'C'){
                score += 3;
            }
        }
        
    }
    return score;
    
}

int part2()
{
    char in1;
    char in2;
    
    int score = 0;
    char rock = 'A';
    int rock_val = 1;
    
    char paper = 'B';
    int paper_val = 2;
    
    char scissors = 'C';
    int scissors_val = 3;
    
    while (cin >> in1 >> in2)
    {
        //lose 
        if (in2 == 'X')
        {
            score += 0;
            if (in1 == rock){
                score += scissors_val;
            }
            if (in1 == paper){
                score += rock_val;
            }
            if (in1 == scissors){
                score += paper_val;
            }
        }
        //draw
        else if (in2 == 'Y') 
        {
            score += 3;
            if (in1 == rock){
                score += rock_val;
            }
            if (in1 == paper){
                score += paper_val;
            }
            if (in1 == scissors){
                score += scissors_val;
            }
        }
        //win
        else if (in2 == 'Z')
        {
            score += 6;
            if (in1 == rock){
                score += paper_val;
            }
            if (in1 == paper){
                score += scissors_val;
            }
            if (in1 == scissors){
                score += rock_val;
            }
        }
        
    }
    return score;
    
}

int main()
{
    cout << part1() << endl;
    cout << part2() << endl;
    return 0;
}
