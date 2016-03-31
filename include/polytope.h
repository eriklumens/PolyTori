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
    Polytope(Polytope polytopeBase, Polytope polytopeFiber, unsigned int choiceFiber, unsigned int choiceFiberDual, bool isDual);
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
    Fan getCorrespondingFan();
    double scalingFactor();
    int drawPolytope();
    Polytope cleanUpExtraVertices();
    Polytope getCorrespondingDualPolytope();
    Polytope getModularTransform(int a, int b, int c, int d);
    double getPolytopeArea();
    std::vector<std::vector<double> > getIntegerPointsLine(std::vector<double> beginPoint, std::vector<double> endPoint);
    std::vector<std::vector<double> > getIntegerPointsLineInterior(std::vector<double> beginPoint, std::vector<double> endPoint);
    std::vector<std::vector<double> > getIntegerPointsTriangle(std::vector<double> pointA, std::vector<double> pointB, std::vector<double> pointC);
    std::vector<std::vector<double> > getIntegerPointsQuadrangle(std::vector<double> pointA, std::vector<double> pointB, std::vector<double> pointC, std::vector<double> pointD);
    std::vector<std::vector<double> > getIntegerPointsQuadrangleInterior(std::vector<double> pointA, std::vector<double> pointB, std::vector<double> pointC, std::vector<double> pointD);
    std::vector<std::vector<double> > getIntegerPointsTriangleInterior(std::vector<double> pointA, std::vector<double> pointB, std::vector<double> pointC);
    std::vector<std::vector<double> > getIntegerpoints4DPolytope();
    std::vector<int> getDualVerticesOrdering(Polytope polytopeBase, Polytope polytopeFiber, int choiceFiber, int choiceFiberDual);
    int hodgeOneOne(Polytope polytopeBase, Polytope polytopeFiber, int choiceFiber, int choiceFiberDual);
    int hodgeTwoOne(Polytope polytopeBase, Polytope polytopeFiber, int choiceFiber, int choiceFiberDual);
    std::vector<int> getDualVerticesOrdering(Polytope dualPolytope);
    int hodgeOneOne(Polytope dualPolytope);
    int hodgeTwoOne(Polytope dualPolytope);
    bool isPointInsidePolytope(std::vector<double> Point);
};
