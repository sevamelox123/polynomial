#include "polynomial.hpp"

using namespace std;


int main(){
    TetoPolynomial poly({6.0,5.0,4.0,3.0,2.0});
    // poly.printData();
    cout << string(poly) << endl;
    poly =  3.9 + poly + 3;

    cout << string(poly) << endl;

    const TetoPolynomial p1({-1,0,1});
    //cout << p1[0] ;
    const TetoPolynomial p2({-1,1});
    // cout << -p1+p2 << "\n";
    cout << p1-p2 << "\n";
    cout << p1*p2 << "\n";
    cout << p1/p2 << "\n";
    cout << p1%p2 << "\n";
    cout << p2/p1 << "\n";
    cout << p2%p1 << "\n";

    return 0;
}