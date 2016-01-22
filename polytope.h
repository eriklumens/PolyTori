#include "lattice.h"

class Polytope
{
    private:
    int vertices;  
    Lattice* lattice; 

    public:
    Polytope(int, Lattice*);
    ~Polytope();
    void setVertices(int mVertices);
    void setLattice(Lattice* lattice);
    int getVertices();
    int getNrOfVertices();
    Lattice* getLattice();
    void drawPolytope();
};

