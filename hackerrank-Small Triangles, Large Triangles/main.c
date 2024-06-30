#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to store the sides and area of a triangle
typedef struct {
    int a, b, c;
    double area;
} Triangle;

// Function to calculate the area of a triangle using Heron's formula
double calculateArea(int a, int b, int c) {
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

// Comparison function for sorting triangles by their area
int compareTriangles(const void *t1, const void *t2) {
    Triangle *triangle1 = (Triangle *)t1;
    Triangle *triangle2 = (Triangle *)t2;
    if (triangle1->area < triangle2->area) {
        return -1;
    } else if (triangle1->area > triangle2->area) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int n;

    // Reading the number of triangles
    scanf("%d", &n);

    // Array to store the triangles
    Triangle triangles[n];

    // Reading the sides of each triangle and calculating their areas
    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        triangles[i].a = a;
        triangles[i].b = b;
        triangles[i].c = c;
        triangles[i].area = calculateArea(a, b, c);
    }

    // Sorting the triangles by their area
    qsort(triangles, n, sizeof(Triangle), compareTriangles);

    // Printing the sorted triangles
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", triangles[i].a, triangles[i].b, triangles[i].c);
    }

    return 0;
}
