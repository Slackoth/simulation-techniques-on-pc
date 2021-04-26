#include <vector>
#include "math.h"
#include "stdlib.h"

using namespace std;

typedef vector<float> Vector;
typedef vector<Vector> Matrix;

void zeroes(Matrix &m, int n) {
    for(int i = 0; i < n; i++) {
        vector<float> row(n, 0.0);

        m.push_back(row);
    }
}

void zeroes(Vector &v, int n) {
    for(int i = 0; i < n; i++) 
        v.push_back(0.0);
}