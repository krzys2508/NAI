#include <iostream>
#include <math.h>
#define M_PI 3.1415926535
#define M_E 2.7182818284590452
#include <vector>
#include <cstdio>
#include <random>
#include <functional>
using namespace std;

random_device rd;
mt19937 gen(rd());

ostream &operator << (ostream &o, vector<double>v){
    for(auto e :v){
        o<<e<<",";

    }
    return o;
}

vector<double> hill_climbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations)
{
    auto p = p0;
    uniform_int_distribution<> distrib(0, p.size() - 1);
    uniform_real_distribution<> distrib_r(-0.1, 0.1);

    if (!f_domain(p)) throw std::invalid_argument("The p0 point must be in domain");
    for (int i = 0; i < iterations; i++) {
        auto p2 = p;

        p[distrib(gen)] += distrib_r(gen);
        double y2 = f(p2);
        if (y2 < f(p)) {
            p = p2;
        }
    }
    return p;
}

auto boothFunction = [](vector <double> v){
double x = v.at(0);
double y = v.at(1);
double results;
results = pow((x + (2 * y) - 7), 2)+pow(((2*x)+y-5),2);
return results;
};

auto ackley = [](vector<double> v) {
double x = v.at(0);
double y = v.at(1);
double results;
results = -20 * exp(-0.2 * sqrt(0.5 * (x * x + y * y))) - exp(0.5 * (cos(2 * M_PI * x) + cos(2 * M_PI * y))) + M_E + 20.0;
return results;
};

auto ackley_domain = [](vector<double> v) {
    return (abs(v[0]) <= 5) && (abs(v[1]) <= 5);
};
auto booth_domain = [](vector<double> v) {
    return (abs(v[0]) <=10) && (abs(v[1]) <=10);
};



int main() {
using namespace std;
vector <double> numbers;
int wybor;
cout << "Wybierz funkcje optymalizacyjna: 1 = Booth 2 = Ackley ";
cin >> wybor;
int iteracje;
if (wybor == 1) {
cout << "Podaj ilosc iteracji"<<endl;
cin>>iteracje;
uniform_real_distribution<> distrib_r(-10,10);
vector<double> booth_p0 = {distrib_r(gen),distrib_r(gen)};
auto result = hill_climbing(boothFunction,booth_domain,booth_p0,iteracje);
cout<<result << "->"<<boothFunction(result)<<endl;
}
else if (wybor == 2) {
cout << "Podaj ilosc iteracji"<<endl;
cin>>iteracje;
uniform_real_distribution<> distrib_r(-5,5);
vector<double> ackley_p0 = {distrib_r(gen),distrib_r(gen)};
auto result = hill_climbing(ackley,ackley_domain,ackley_p0,iteracje);
cout<<result << "->"<<ackley(result)<<endl;
}
}