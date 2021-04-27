#include <iostream>
#include <vector>
#include "classes.h"
#include "utilities.h"
#include "sel.h"
#include "math_tools.h"

using namespace std;

int main() {
    vector<Matrix> localKs;
    vector<Vector> localBs;
    Matrix k;
    Vector b;
    Vector t;

    cout << "IMPLEMENTACION DEL METODO DE LOS ELEMENTOS FINITOS\n"
         << "\t TRANSFERENCIA DE CALOR\n" << "\t 1 DIMENSION\n"
         << "\t FUNCIONES DE FORMA LINEALES\n" << "\t PESOS DE GALERKIN\n"
         << "*************************************************************************\n\n";

    Mesh mesh;

    readMeshConditions(mesh);
    createLocalSystems(mesh, localKs, localBs);
    zeroes(k, mesh.getSize(NODES)); zeroes(b, mesh.getSize(NODES));
    assemble(mesh, localKs, localBs, k, b);
    showMatrix(k); showVector(b);
    applyNeumann(mesh, b); applyDirichlet(mesh, k, b);
    zeroes(t, b.size());
    calculate(k, b, t);

    cout << "La respuesta es: \n";
    showVector(t);

    return 0;
}