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
    std::vector<std::vector<std::vector<double> > > subdivideVerticesInPlanes();
    std::vector<std::vector<double> > get2DFaceGivenThreePoints(std::vector<std::vector<double> > points);
    std::vector<std::vector<double> > getIntegerPoints2DFace(std::vector<std::vector<double> > vertices);
    std::vector<std::vector<double> > getIntegerPoints2DFaceInterior(std::vector<std::vector<double> > vertices);
    std::vector<std::vector<double> > get3DFaceGivenFourPoints(std::vector<std::vector<double> > points);
    std::vector<std::vector<std::vector<double> > > get2DFacesOf3DPolytopeOfFacePlusPoint();
    std::vector<std::vector<double> > getIntegerPoints3DFaceInterior(std::vector<std::vector<double> > vertices);
    std::vector<std::vector<std::vector<double> > > get2DFacesOf4DPolytope();
    std::vector<std::vector<std::vector<double> > > get3DFacesOf4DPolytope();
    std::vector<std::vector<double> > getDualTo2DFace(std::vector<std::vector<double> > face, Polytope dualPolytope);
    int hodgeOneOneHKK(Polytope dualPolytope);
    int hodgeTwoOneHKK(Polytope dualPolytope);
    std::vector<Polytope> getAllPolytopesFromConstruction(Polytope polytopeBase, Polytope polytopeFiber);
    std::vector<Polytope> getAllDualPolytopesFromConstruction(Polytope polytopeBase, Polytope polytopeFiber);
    std::vector<std::vector<std::vector<std::vector<Polytope> > > > getAll4DPolytopesGivenListOf2DPolytopes(std::vector<Polytope> myList);
    void printListFrom2DTo4DPolytopesToFile(std::string fileName, std::vector<Polytope> myList);
};
