enum line {NO_LINE, SINGLE_LINE, DOUBLE_LINE};
enum mode {NO_MODE, INT_FLOAT, INT_INT_INT};
enum constant {ELEMENT_LENGTH, THERMAL_CONDUCTIVITY, HEAT_SOURCE};
enum size {NODES, ELEMENTS, DIRICHLET, NEUMANN};

// Class representing the mesh
class Mesh {
    // To contain the value of K, L and Q
    float constants[3];

    // To contain the number of nodes, elements, dirichlet and neumann conditions
    int sizes[4]; 

    Node* nodeList;
    Element* elementList;
    Condition* dirichletList;
    Condition* neumannList;

    public:
        void setConstants(float l, float k, float q) {
            constants[ELEMENT_LENGTH] = l;
            constants[THERMAL_CONDUCTIVITY] = k;
            constants[HEAT_SOURCE] = q;
        }

        void setSizes(int nodes, int elements, int dirichlets, int neumann) {
            sizes[NODES] = nodes;
            sizes[ELEMENTS] = elements;
            sizes[DIRICHLET] = dirichlets;
            sizes[NEUMANN] = neumann;
        }

        void createData() {
            nodeList = new Node[sizes[NODES]];
            elementList = new Element[sizes[ELEMENTS]];
            dirichletList = new Condition[sizes[DIRICHLET]];
            neumannList = new Condition[sizes[NEUMANN]];
        }

        Node* getNodes() {
            return nodeList;
        }

        Element* getElements() {
            return elementList;
        }

        Condition* getDirichlet() {
            return dirichletList;
        }

        Condition* getNeumann() {
            return neumannList;
        }

        int getSize(int s) {
            return sizes[s];
        }

        float getConstant(int c) {
            return constants[c];
        }

        Node getNode(int i) {
            return nodeList[i];
        }

        Element getElement(int i) {
            return elementList[i];
        }
};

// Class representing an item in the mesh
class MeshItem {
    protected:
        int id; // Id of the MeshItem
        float x; // X coordinates
        int node1; // First node id
        int node2; // Second node id
        float value; // Value of the MeshItem

    public:
        int getId() {
            return id;
        }

        float getX() {
            return x;
        }

        int getNode1() {
            return node1;
        }

        int getNode2() {
            return node2;
        }

        float getValue() {
            return value;
        }

        virtual void setIntFloat(int id, float x) = 0;

        virtual void setIntIntInt(int id, int n1, int n2) = 0;
};

// Class representing a node in the mesh
class Node: public MeshItem {
    public:
        void setIntFloat(int identifier, float xCoordinate) {
            id = identifier;
            x = xCoordinate;
        }

        void setIntIntInt(int id, int n1, int n2) {}
};

// Class representing an element in the mesh
class Element: public MeshItem {
    public:
        void setIntFloat(int id, float x) {}

        void setIntIntInt(int identifier, int n1, int n2) {
            id = identifier;
            node1 = n1;
            node2 = n2;
        }
};

// Class representing the conditions in the mesh
class Condition: public MeshItem {
    public:
        void setIntFloat(int nodeToApply, float prescribedValue) {
            node1 = nodeToApply;
            value = prescribedValue;
        }

        void setIntIntInt(int id, int n1, int n2) {}
};
