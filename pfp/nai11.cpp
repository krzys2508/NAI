#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <fstream>

std::string result = "file.txt";
std::ofstream output(result);

using namespace std;

using point2d = array<double, 2>;

inline point2d operator+(const point2d a, const point2d b) {
    return {a[0] + b[0], a[1] + b[1]};
}

inline point2d operator*(const point2d a, const double b) {
    return {a[0] * b, a[1] * b};
}

inline point2d operator-(const point2d a, const point2d b) {
    return a + (b * -1.0);
}

inline point2d operator%(const point2d a, const point2d b) {
    return {a[0] * b[0], a[1] * b[1]};
}

inline double operator*(const point2d a, const point2d b) {
    auto r = a % b;
    return accumulate(r.begin(), r.end(), 0.0);
}

inline double length(const point2d a) {
    return sqrt(a * a);
}

inline std::ostream& operator<<(std::ostream& o, const point2d a) {
    o << a[0] << " " << a[1];
    return o;
}

point2d derivative(std::function<double(point2d)> f, point2d x, double d = 1.52588e-05) {
    point2d dx = {d, 0.0};
    point2d dy = {0.0, d};
    return {
        (f(x + dx * 0.5) - f(x - dx * 0.5)) / d,
        (f(x + dy * 0.5) - f(x - dy * 0.5)) / d};
}

double shortestDistPossible(point2d p1, point2d p2, point2d p3) {
    double p_x = p2[0] - p1[0];
    double p_y = p2[1] - p1[1];
    double temp = pow(p_x, 2) + pow(p_y, 2);
    double u = ((p3[0] - p1[0]) * p_x + (p3[1] - p1[1]) * p_y) / temp;

    if (u > 1) {u = 1;} 
    else if (u < 0) {u = 0;} 
    
    return sqrt(pow((p1[0] + u * p_x) - p3[0], 2) + pow((p1[1] + u * p_y) - p3[1], 2));
}

int main(int argc, char** argv) {
    point2d destination = {0.0, 0.0};
    point2d currentPosition = {10.0, 1.0};
    double velocity = 0.1;
    double acceleration = 0.1;

    vector<pair<point2d, double>> obstacles = {};

    obstacles.push_back({{7.0, 0.4},(argc>1)?std::stod(argv[1]):0.1});
    obstacles.push_back({{8.0, 2.0},(argc>1)?std::stod(argv[1]):0.1});

        
    auto field = [&](point2d p) -> double {
        double obstaclefield = 0;
        for (int i = 0; i < obstacles.size(); i +=2) {
            double distanceToObstacle = shortestDistPossible(obstacles[i].first, obstacles[i+1].first, p);
            obstaclefield += obstacles[i].second / (distanceToObstacle * distanceToObstacle);
        }
        return length(destination - p) + obstaclefield;
    };

    point2d currentVelocity = {0.0, 0.0};

    for (int i = 0; i < 1000; i++) {
        point2d dp = derivative(field, currentPosition);
        dp = dp * (1.0 / length(dp));
        dp = dp * acceleration;

        currentVelocity = currentVelocity - dp;
        if (length(currentVelocity) > velocity) currentVelocity = (currentVelocity * (1.0 / (length(currentVelocity))))*velocity;
        currentPosition = currentPosition + currentVelocity;
        output<<currentPosition<<endl;
    }

    return 0;
}