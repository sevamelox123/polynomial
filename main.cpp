#include "polynomial.hpp"

using namespace std;


int main(){
    const int soa = 5;
    double* teto =  new double[soa];
    TetoPolynomial poly(teto,soa);
    cout << poly.getLength() << endl;
    return 0;
}