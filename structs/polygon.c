#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} point;

typedef struct {
    size_t len;
    point points[];
} polygon;

polygon *read_points() {
    size_t len;
    scanf("%zu", &len);
    polygon *p = malloc(len * sizeof(point) + sizeof(polygon));
    p->len = len;
    for(size_t i = 0; i < p->len; i++) {
        scanf("%lf %lf", &p->points[i].x, &p->points[i].y);
    }
    return p;
}

double dist(const point *p1, const point *p2) {
    return sqrt((p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y));
}

double perimeter(const polygon *p) {
    double sum = 0;
    for(size_t i = 0; i < p->len; i++) {
        sum += dist(&p->points[i], &p->points[(i+1) % p->len]);
    }
    return sum;
}

//ok i had misread the formula so i thought it was a simpler one because wow this one actually accounts for empty space so some of what i said in class was wrong
double area(const polygon *p) {
    double sum = 0;
    for(size_t i = 0; i < p->len; i++) {
        //more elegant way of writing the formal provided by Laker:
        point curr = p->points[i];
        point next = p->points[(i+1) % p->len];
        sum += (curr.x + next.x) * (curr.y - next.y);
    }
    return fabs(sum) / 2;
}

int main(int argc, char *argv[] ) {
    polygon *p = read_points();
    printf("perimeter: %f\n", perimeter(p));
    printf("area: %f\n", area(p));
    free(p);
    return 0;
}
