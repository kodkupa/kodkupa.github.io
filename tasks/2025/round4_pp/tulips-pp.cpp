/*
 We determine how many tulips fall inside a fertilized zone 
 by checking triangle properties. We calculate the distances 
 between each tulip and the rectangle's corners, then classify 
 triangles using the Triangle Inequality Rule. 
 A tulip is in the fertilized zone if it forms exactly two 
 obtuse and two acute triangles with the rectangle's corners.
*/

#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    int x = 0, y = 0;
};

int distance(Point A, Point B) {
    return pow(A.x - B.x, 2) + pow(A.y - B.y, 2);
}

int checkTriangles(int side1, int side2, int sideOfSquare) {
    if (side1 + side2 > sideOfSquare) {
        return 1;  // acute triangle
    }
    if (side1 + side2 < sideOfSquare) {
        return -1; // obtuse triangle
    }
    return 0; // right-angled triangle
}

int main() {
    Point topLeft, topRight, bottomLeft, bottomRight;

    cin >> topLeft.x >> topLeft.y;
    cin >> topRight.x >> topRight.y;
    cin >> bottomRight.x >> bottomRight.y;
    cin >> bottomLeft.x >> bottomLeft.y;

    int numberOfPoints;
    cin >> numberOfPoints;

    int numberOfPointsInRedArea = 0;

    for (int i = 0; i < numberOfPoints; i++) {
        Point p;
        cin >> p.x >> p.y;

        int countObtuse = 0;
        int countAcute = 0;

        if (checkTriangles(distance(p, topLeft), distance(p, bottomLeft), distance(topLeft, bottomLeft)) == -1) {
            countObtuse++;
        }
        if (checkTriangles(distance(p, topLeft), distance(p, topRight), distance(topLeft, topRight)) == -1) {
            countObtuse++;
        }
        if (checkTriangles(distance(p, bottomRight), distance(p, topRight), distance(bottomRight, topRight)) == -1) {
            countObtuse++;
        }
        if (checkTriangles(distance(p, bottomRight), distance(p, bottomLeft), distance(bottomRight, bottomLeft)) == -1) {
            countObtuse++;
        }
        if (checkTriangles(distance(p, topLeft), distance(p, bottomLeft), distance(topLeft, bottomLeft)) == 1) {
            countAcute++;
        }
        if (checkTriangles(distance(p, topLeft), distance(p, topRight), distance(topLeft, topRight)) == 1) {
            countAcute++;
        }
        if (checkTriangles(distance(p, bottomRight), distance(p, topRight), distance(bottomRight, topRight)) == 1) {
            countAcute++;
        }
        if (checkTriangles(distance(p, bottomRight), distance(p, bottomLeft), distance(bottomRight, bottomLeft)) == 1) {
            countAcute++;
        }

        if (countObtuse == 2 && countAcute==2) {
            numberOfPointsInRedArea++;
        }
    }

    cout << numberOfPointsInRedArea << endl;

    return 0;
}
