#include "polynomial.hpp"

using namespace std;


int main(){
    TetoPolynomial poly({1.0,2.0,3.0});
    poly.printData();
    cout << poly.calculate(5)<<endl;
    // cout << poly[1].c<<endl;
    // cout << poly.at(1).c<<endl;

    return 0;
}