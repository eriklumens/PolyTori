#include "lattice.h"

class Polytope
{
    private:
    int vertices = 0;  
    Lattice lattice{Lattice(0,std::vector<std::vector<double> >(1,std::vector<double>(1)))}; 

    public:
    Polytope(int vert, Lattice lat);
    ~Polytope();
    void setVertices(int vert);
    void setLattice(Lattice lat);
    int getVertices();
    int getNrOfVertices();
    Lattice getLattice();
    void drawPolytope();
};

