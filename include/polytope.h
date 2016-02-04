#include "lattice.h"
#include "line.h"
#include "fan.h"
#include <vector>

class Polytope
{
    private:
    std::vector<std::vector<double> > vertices{std::vector<std::vector<double> >(0,std::vector<double>(0))};  
    Lattice lattice{Lattice(0,std::vector<std::vector<double> >(0,std::vector<double>(0)))}; 

    public:
    Polytope(std::vector<std::vector<double> > vert, Lattice lat);
    ~Polytope();
    void setVertices(std::vector<std::vector<double> > vert);
    void setLattice(Lattice lat);
    std::vector<std::vector<double> > getVertices();
    std::vector<std::vector<double> > getVerticesInLattice();
    int getNrOfVertices();
    Lattice getLattice();
    std::vector<double> getSpecificVertex(int vertexNr);
    int getNrOfIntPointsPolytope();
    std::vector< std::vector<std::vector<double> > > getVectorsPointingBetweenVertices();
    std::vector<std::vector<Line> > getLinesBetweenVertices();
    std::vector<int> getVerticesOrder();
    std::vector<Line> getEdges();
    std::vector<Cone> getConesOverFaces();
    Fan getCorrespondingDualFan();
    void drawPolytope();
    bool isPointInsidePolytope(std::vector<double> Point);
};

