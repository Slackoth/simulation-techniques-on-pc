#include "classes.h"
#include "math_tools.h"

Matrix createLocalK(Mesh &mesh) {
    Matrix localK;
    Vector row1, row2;
    float k = mesh.getConstant(THERMAL_CONDUCTIVITY);
    float l = mesh.getConstant(ELEMENT_LENGTH);
    
    //(k / l) * [1 -1 ; -1 1]
    row1.push_back(k / l); row1.push_back(-k / l);
    row2.push_back(-k / l); row2.push_back(k / l);
    localK.push_back(row1); localK.push_back(row2);

    return localK;
}

Vector createLocalB(Mesh &mesh) {
    Vector localB;
    float q = mesh.getConstant(HEAT_SOURCE);
    float l = mesh.getConstant(ELEMENT_LENGTH);

    // (Q * l / 2) * [1 ; 1]
    localB.push_back(q * l / 2); localB.push_back(q * l / 2);

    return localB;

}

void createLocalSystems(Mesh &mesh, vector<Matrix> localKs, vector<Vector> localBs) {
    for(int i = 0; i < mesh.getSize(ELEMENTS); i++) {
        localKs.push_back(createLocalK(mesh));
        localBs.push_back(createLocalB(mesh));
    }
}

void assemblyK(Element e, Matrix localK, Matrix &k) {

}

void assemblyB(Element e, Vector localB, Vector &b) {
    
}

void assemble(Mesh &mesh, vector<Matrix> &localKs, vector<Vector> &localBs, Matrix &k, Vector &b) {
    for (int i = 0; i < mesh.getSize(ELEMENTS); i++) {
        Element e = mesh.getElement(i);

        assemblyK(e, localKs.at(i), k);
        assemblyB(e, localBs.at(i), b);
    }
    
}