#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
using namespace std;

static const double EPS = 1e-8;

double add(double a, double b) {
        if (abs(a + b) < EPS * (abs(a) + abs(b))) return 0;
        return a + b;
}

struct Point {
        double x, y;
        Point() {}
        Point(double x, double y) : x(x), y(y) {}
        Point operator + (Point p) { return Point(add(x, p.x), add(y, p.y)); }
        Point operator - (Point p) { return Point(add(x, -p.x), add(y, p.y)); }
        Point operator * (double d) { return Point(x * d, y * d); }
        double dot(Point p) { return add(x * p.x, y * p.y); }
        double det(Point p) { return add(x * p.y, -y * p.x); }
};

struct Line { Point s, t; };

Point Intersection(Line p, Line q) {
        return p.s + (p.t - p.s) * ((q.t - q.s).det(q.s - p.s) / (q.t - q.s).det(p.t - p.s));
}

bool Intersect(Line p, Line q) {
        if (abs((q.t - q.s).det(p.t - p.s)) < EPS) return false;
        return true;
}

int main() {
        return 0;
}

