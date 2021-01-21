#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} point;

//slightly different than what you put, this is an outparameter
point *read_points(size_t *count) {
    scanf("%zu", count);
    point *p = malloc(*count * sizeof(point));
    for(size_t i = 0; i < *count; i++) {
        scanf("%lf %lf", &p[i].x, &p[i].y);
    }
    return p;
}

double dist(const point *p1, const point *p2) {
    return sqrt((p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y));
}

double perimeter(const point *points, size_t count) {
    double sum = 0;
    for(size_t i = 0; i < count; i++) {
        sum += dist(points+i, points+i+1);
    }
    return sum;
}

//ok i had misread the formula so i thought it was a simpler one because wow this one actually accounts for empty space so some of what i said in class was wrong
double area(const point *points, size_t count) {
    double sum = 0;
    for(size_t i = 0; i < count; i++) {
        sum += (points[i].x + points[i+1].x) * (points[i].y - points[i+1].y) / 2;
    }
    sum += (points[count].x + points[0].x) * (points[count].y - points[0].y) / 2;
    return fabs(sum);
}

int main(int argc, char *argv[] ) {
    size_t count;
    point *p = read_points(&count);
    printf("perimeter: %f\n", perimeter(p, count));
    printf("area: %f\n", area(p, count));
    free(p);
    return 0;
}
