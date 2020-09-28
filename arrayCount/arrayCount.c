#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int countOccurances (int nums[], size_t length)
{
    int ongoingCount[100] = {0};
    for (size_t i = 0; i < length; i++)
    {;
        ongoingCount[nums[i]]++;
        //printf("%zu %d %d \n", i, nums[i], ongoingCount[nums[i]]);
    }
    
    int currentBest = 0;
    for (size_t i = 1; i < 100; i++)
    {
        if (ongoingCount[currentBest] < ongoingCount[i])
        {
            currentBest = i;
        }
    }
    printf("%d was the smallest number with the most occurances. (%d) \n", currentBest, ongoingCount[currentBest]);
    return 0;
}
int main(int argc, char *argv[] ) {
    int array[100] = {2, 1, 2, 9, 3, 9, 9, 4};
    countOccurances(array, 8);
    return 0;
}
