#include "polynomial.hpp"

using namespace std;


int main(){
    // const int soa = 5;
    // double* teto =  new double[soa];
    TetoPolynomial poly({1.0,2.0,3.0});
    poly.getData();
    cout << poly.Calculate(5)<<endl;
    // cout << poly.at(2).k<<endl;

    return 0;
}