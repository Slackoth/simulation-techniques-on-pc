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
    int index1 = e.getNode1() - 1;
    int index2 = e.getNode2() - 1;

    k.at(index1).at(index1) += localK.at(0).at(0);
    k.at(index1).at(index2) += localK.at(0).at(1);
    k.at(index2).at(index1) += localK.at(1).at(0);
    k.at(index2).at(index2) += localK.at(1).at(1);
}

void assemblyB(Element e, Vector localB, Vector &b) {
    int index1 = e.getNode1() - 1;
    int index2 = e.getNode2() - 1;

    b.at(index1) += localB.at(0);
    b.at(index2) += localB.at(1);
}

void showMatrix(Matrix k) {
    for(int i = 0; i < k.at(0).size(); i++) {
        cout << "[\t";
        for(int j = 0; j < k.size(); j++) {
            cout << k.at(i).at(j) << "\t";
        }
        cout << "]\n";
    }
}

void showVector(Vector b){
    cout << "[\t";
    for(int i = 0; i < b.size(); i++) {
        cout << b.at(i) << "\t";
    }
    cout << "]\n";
}

void assemble(Mesh &mesh, vector<Matrix> &localKs, vector<Vector> &localBs, Matrix &k, Vector &b) {
    for (int i = 0; i < mesh.getSize(ELEMENTS); i++) {
        Element e = mesh.getElement(i);

        assemblyK(e, localKs.at(i), k);
        assemblyB(e, localBs.at(i), b);
    }
}

void applyNeumann(Mesh &mesh, Vector &b) {
    for(int i = 0; i < mesh.getSize(NEUMANN); i++) {
        Condition c = mesh.getCondition(i, NEUMANN);

        b.at(c.getNode1() - 1) += c.getValue();
    }
}

void applyDirichlet(Mesh &mesh, Matrix &k, Vector &b) {
    for(int i = 0; i < mesh.getSize(DIRICHLET); i++) {
        Condition c = mesh.getCondition(i, DIRICHLET);
        int index = c.getNode1() - 1;

        k.erase(k.begin() + index);
        b.erase(b.begin() + index);

        for(int row = 0; row < k.size(); row++) {
            float cell = k.at(row).at(index);

            k.at(row).erase(k.at(row).begin() + index);
            b.at(row) += -1 * c.getValue() * cell;
        }
    }
}

void calculate(Matrix &k, Vector &b, Vector &t) {
    Matrix kInverse;

    
}