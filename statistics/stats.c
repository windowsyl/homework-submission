#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double *read_array(size_t length)
{
    printf("%zu\n", length);

    double *nums = malloc(length * sizeof(double));
    printf("Enter %zu numbers, one per line:\n", length);
    for(size_t i = 0; i < length; i++)
    {
        scanf("%lf", &nums[i]);
        printf("what you literally just inputed: %lf\n", nums[i]);
    }
    return nums;
    
}
double sum(const double *nums, size_t length)
{
    double sum = 0;
    for(size_t i = 0; i < length; i++)
    {
        sum += nums[i];
    }
    return sum;
}
double average(const double *nums, size_t length)
{
    double sum = 0;
    for(size_t i = 0; i < length; i++)
    {
        sum += nums[i];
    }
    return sum/length;
}
double stdev(const double *nums, size_t length)
{
    double average = 0;
    for(size_t i = 0; i < length; i++)
    {
        average += nums[i];
    }

    average = average/length;
    double newsum = 0;

    for(size_t i = 0; i < length; i++)
    {
        newsum += (nums[i] - average)*(nums[i] - average);
    }
    return sqrt(newsum/(length-1));
}
int main( int argc, char *argv[] ) {
    printf("How many numbers will you enter? ");
    size_t length;
    scanf("%zu", &length);
    double *nums = read_array(length);
    printf("sum: %f, average: %f, stdev: %f\n", sum(nums, length), average(nums, length), stdev(nums, length));
    free(nums);
    
    return 0;
}
