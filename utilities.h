#include <fstream>
#include <iostream>
#include "classes.h"

using namespace std;

void getData(ifstream &file, int nLines, int nData, int mode, MeshItem* meshItemList) {
    string line;
    
    file >> line; // Ignore line

    if(nLines == DOUBLE_LINE) file >> line; // Ignore another line

    for(int i = 0; i < nData; i++) {
        switch (mode) {
        case INT_FLOAT:
            int in; float real;
            
            file >> in >> real;
            meshItemList[i].setIntFloat(in, real);

            break;
        
        case INT_INT_INT:
            int in1, in2, in3;
            
            file >> in1 >> in2 >> in3;
            meshItemList[i].setIntIntInt(in1, in2, in3);
        
        default:
            break;
        }
    }
}

void readMeshConditions(Mesh &mesh) {
    char filename[15];
    ifstream file;
    float k, l, q;
    int nNodes, nElements, nDirichlet, nNeumann;

    do {
        cout << "INGRESE EL NOMBRE DEL ARCHIVO QUE CONTIENE LOS DATOS DE LA MALLA:";
        cin >> filename;

        file.open(filename);
    }
    while(!file);

    file >> l >> k >> q;
    file >> nNodes >> nElements >> nDirichlet >> nNeumann;

    mesh.setConstants(l, k, q);
    mesh.setSizes(nNodes, nElements, nDirichlet, nNeumann);
    mesh.createData();
    getData(file,SINGLE_LINE, nNodes, INT_FLOAT, mesh.getNodes());
    getData(file,DOUBLE_LINE, nElements, INT_INT_INT, mesh.getElements());
    getData(file,DOUBLE_LINE, nDirichlet, INT_FLOAT, mesh.getDirichlet());
    getData(file,DOUBLE_LINE, nNeumann, INT_FLOAT, mesh.getNeumann());
    file.close();
}