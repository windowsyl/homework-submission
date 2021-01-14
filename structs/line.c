#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} pos;
typedef struct {
    pos p1;
    pos p2;
} line;

double dist(pos p1, pos p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
double length(line l)
{
    return dist(l.p1, l.p2);
}
double slope(line l)
{
    return (l.p1.y-l.p2.y)/(l.p1.x-l.p2.x);
}
double point_on_line(line l, pos p)
{
    if (fabs((p.x-l.p1.x) * slope(l) + l.p1.y - p.y) < 0.001)
    {
        return 1;
    } else {
        return 0;
    }
}
int main( int argc, char *argv[] ) {
    line l = {
        .p1 = {0, 0},
        .p2 = {3, 4}
    };
    pos p = {5,6};
    pos p2 = {1, 1.333333};
    printf("coords: (%.3f, %.3f), (%.3f, %.3f) \n", l.p1.x, l.p1.y, l.p2.x, l.p2.y);
    printf("distance between points: %.3f\n",dist(l.p1, l.p2));
    printf("length of line segment: %.3f\n", length(l));
    printf("slope of the line: %f\n", slope(l));
    printf("the point (5, 6) on the line: %s\n", point_on_line(l, p) == 1 ? "true":"false");
    printf("the point (1, 1.333) on the line: %s\n", point_on_line(l, p2) == 1 ? "true":"false");
    return 0;
}
