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

void copyMatrix(Matrix A, Matrix &copy){
    zeroes(copy, A.size());
    
    for(int i = 0; i < A.size(); i++)
        for(int j = 0; j < A.at(0).size(); j++)
            copy.at(i).at(j) = A.at(i).at(j);
}

void getMinor(Matrix &matrix,int i, int j){
    matrix.erase(matrix.begin() + i); 

    for(int i = 0; i < matrix.size(); i++)
        matrix.at(i).erase(matrix.at(i).begin() + j);
}

void cofactors(Matrix matrix, Matrix &cof){
    zeroes(cof, matrix.size());
    
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.at(0).size(); j++) {
            Matrix minor;
            
            copyMatrix(matrix, minor);
            getMinor(minor,i,j);
            
            cof.at(i).at(j) = pow(-1, i + j) * determinant(minor);
        }
    }
}

float determinant(Matrix &matrix) {
        if(matrix.size() == 1) return matrix.at(0).at(0);
    else{
        float det = 0.0;
        
        for(int i = 0; i < matrix.at(0).size(); i++){
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,0,i);

            det += pow(-1, i) * matrix.at(0).at(i) * determinant(minor);
        }
        
        return det;
    }
}

void transpose(Matrix matrix, Matrix &t){
    zeroes(t, matrix.size());
    
    for(int i = 0; i < matrix.size(); i++)
        for(int j = 0; j < matrix.at(0).size(); j++)
            t.at(j).at(i) = matrix.at(i).at(j);
}

void productRealMatrix(float real, Matrix M, Matrix &R){
    zeroes(R, M.size());
    
    for(int i = 0; i < M.size(); i++)
        for(int j = 0; j < M.at(0).size(); j++)
            R.at(i).at(j) = real * M.at(i).at(j);
}

void inverseMatrix(Matrix &m, Matrix &mi) {
    // Using following formula:
    // (M^-1) = (1/determinant(M))*Adjunta(M)
    // Adjunta(M) = transpose(cofactors(M))
    Matrix cof, adj;
    float det = determinant(m);

    if(det == 0)
        exit(EXIT_FAILURE);
    
    cofactors(m, cof);
    transpose(cof, adj);
    productRealMatrix(1 / det, adj, mi);
}

void productMatrixVector(Matrix A, Vector v, Vector &R) {
    for(int f = 0; f < A.size(); f++){
    
    float cell = 0.0;
    
    for(int c = 0; c < v.size(); c++) 
        cell += A.at(f).at(c)*v.at(c);
    
    R.at(f) += cell;
}