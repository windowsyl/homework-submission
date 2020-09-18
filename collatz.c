#include <stdio.h>

int collatz_stopping_time(int num) {
    if (num == 1)
    {
        return 0;
    }
    if (num%2 == 0)
    {
        return collatz_stopping_time(num / 2) + 1;
    } else
    {
        return collatz_stopping_time(num * 3 + 1) + 1;
    }
}

int main(int argc, char *argv[]) {
    int current_recordholder = 0;
    int ratio_recordholder = 0;
    double ratio_time = 0;
    int longest_time = 1;
    for (int i = 1; i < 100000; i++)
    {
        int j = collatz_stopping_time(i);
        if (longest_time < j)
        {
            current_recordholder = i;
            longest_time = j;
        }
        if(ratio_time < (j/1.0)/i)
        {
            ratio_recordholder = i;
            ratio_time = (j/1.0)/i;
        }
    }
    printf("%i had the longest stopping time of %i \n", current_recordholder, longest_time);
    printf("%i had the largest ratio of %f \n", ratio_recordholder, ratio_time);
    return 0;
}
