#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
/*
  MATH PORTION OF THE CODE
*/
using point2d = std::array<double, 2>;
inline point2d operator+(const point2d a, const point2d b)
{
    return {a[0] + b[0], a[1] + b[1]};
}
inline point2d operator*(const point2d a, const double b)
{
    return {a[0] * b, a[1] * b};
}
inline point2d operator-(const point2d a, const point2d b)
{
    return a + (b * -1.0);
}
inline point2d operator%(const point2d a, const point2d b)
{
    return {a[0] * b[0], a[1] * b[1]};
}
inline double operator*(const point2d a, const point2d b)
{
    auto r = a % b;
    return std::accumulate(r.begin(), r.end(), 0.0);
}
inline double length(const point2d a)
{
    return std::sqrt(a * a);
}
inline std::ostream& operator<<(std::ostream& o, const point2d a)
{
    o << a[0] << " " << a[1];
    return o;
}

////

point2d derivative(std::function<double(point2d)> f, point2d x, double d = 1.52588e-05)
{
    point2d dx = {d, 0.0};
    point2d dy = {0.0, d};
    return {
        (f(x + dx * 0.5) - f(x - dx * 0.5)) / d,
        (f(x + dy * 0.5) - f(x - dy * 0.5)) / d};
}

double minDistance(point2d pt1, point2d pt2, point2d pt3){

    pair<double, double> pt1_pt2;
    pt1_pt2.first = pt2[0] - pt1[0];
    pt1_pt2.second = pt2[1] - pt1[1];

  
    pair<double, double> pt1_pt3;
    pt1_pt3.first = pt3[0] - pt1[0];
    pt1_pt3.second = pt3[1] - pt1[1];

    
    pair<double, double> pt3_pt2;
    pt3_pt2.first = pt3[0] - pt2[0],
    pt3_pt2.second = pt3[1] - pt2[1];


   
    double vw_wp = (pt1_pt2.first * pt3_pt2.first + pt1_pt2.second * pt1_pt3.second);
    double vw_vp = (pt1_pt2.first * pt1_pt3.first + pt1_pt2.second * pt1_pt3.second);

   
    double ans = 0.0;

    if (vw_wp > 0) {
       
        double y = pt3[1] - pt2[1];
        double x = pt3[0] - pt2[0];
        ans = sqrt(x * x + y * y);
    } else if (vw_vp < 0) {
        double y = pt3[1] - pt1[1];
        double x = pt3[0] - pt1[0];
        ans = sqrt(x * x + y * y);
    } else {
        
        double x1 = pt1_pt2.first;
        double y1 = pt1_pt2.second;
        double x2 = pt1_pt3.first;
        double y2 = pt1_pt3.second;
        double mod = sqrt(x1 * x1 + y1 * y1);
        ans = abs(x1 * y2 - y1 * x2) / mod;
    }
    return ans;
}


int main(int argc, char** argv)
{
    string outfilename = "Results.txt";
    ofstream out (outfilename);
    point2d destination = {0.0, 0.0};
    point2d currentPosition = {10.0, 1.0};
    double velocity = 0.1;
    double acceleration = 0.1;

    std::vector<std::pair<point2d, double>> obstacles = {};
    // for (double x = 4.6; x < 5.0; x += 0.01) {
    //     for (double y = -3.6; y < 3.7; y += 0.01) {
    //         obstacles.push_back({{x,y},(argc>1)?std::stod(argv[1]):1.0});
    //     }
    // }
    obstacles.push_back({{5.0,1.0},(argc>1)?std::stod(argv[1]):1.0});
    obstacles.push_back({{8.0,1.0},(argc>1)?std::stod(argv[1]):1.0});

    auto field = [&](point2d p) -> double {
        double obstaclefield = 0;
        for (const auto& obstacle : obstacles) {
           // double distanceToObstacle = length(p - obstacle.first);
            double distanceToObstacle = minDistance(obstacles[0].first, obstacles[1].first, p);
            obstaclefield += obstacle.second/ (distanceToObstacle*distanceToObstacle);
        }
        return length(destination - p) + obstaclefield;
    };
    for (int i = 0; i < 1000; i++) {
        point2d dp = derivative(field, currentPosition);
        dp = dp * (1.0 / length(dp));
        dp = dp * acceleration;
        currentPosition = currentPosition -dp;
        out<<currentPosition<<endl;
        }
    

    return 0;
}
