#include "polynomial.hpp"

using namespace std;


int main(){
    TetoPolynomial poly({5.0,4.0,-3.0,2.0,55.0});
    poly.printData();
    cout << string(poly) << endl;
    // cout << poly[1].c<<endl;
    // cout << poly.at(1).c<<endl;

    return 0;
}