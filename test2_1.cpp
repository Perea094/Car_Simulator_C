// crt_rand.c
// This program seeds the random-number generator
// with a fixed seed, then exercises the rand function
// to demonstrate generating random numbers, and
// random numbers in a specified range.
#include <iostream>
#include <stdlib.h> // rand(), srand()
#include <chrono> // time()

float RangedRand(float range_min, float range_max)
{
    float r = (static_cast<double>(rand()));
    // Generate random numbers in the interval [range_min, range_max], inclusive.
    float r1 = (static_cast<double>(rand())/RAND_MAX) * (range_max - range_min) + range_min;
    return r1;
}

int RangedRandInt(int range_min, int range_max)
{
    float r = (static_cast<double>(rand()));
    // Generate random numbers in the interval [range_min, range_max], inclusive.
    float r1 = (static_cast<double>(rand())/RAND_MAX) * (range_max - range_min) + range_min;
    return r1;
}

int main(void)
{
    // Seed the random-number generator with a fixed seed so that
    // the numbers will be the same every time we run.
    std::srand(static_cast<unsigned>(time(0))); 
    std::cout << "\nRandom number in a range demo ====\n"; 
    std::cout << (RangedRand(0,100)) << std::endl;
    std::cout << "New random ranged \n" << (RangedRandInt(0,5)) << std::endl;
    
}