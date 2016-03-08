#include <iostream>
#include <numeric>
#include "polytope.h"
#include <math.h> 
#include <vector>
#include <GLFW/glfw3.h>


Polytope::Polytope(std::vector<std::vector<double> > _vertices, Lattice _lattice)
{
    vertices = _vertices;
    lattice = _lattice;
}
Polytope::Polytope(Polytope polytopeBase, Polytope polytopeFiber, int choiceFiber, int choiceFiberDual, bool isDual)
{
    Polytope myDualPolytopeFiber = polytopeFiber.getCorrespondingDualPolytope();
    if(polytopeBase.getLattice().getDimension() != 2 or polytopeFiber.getLattice().getDimension() != 2 or choiceFiber >= polytopeFiber.getVertices().size() or choiceFiberDual >= myDualPolytopeFiber.getVertices().size())
    {
        std::cout << "Cannot form 4D polytope! Dimensions of constituents are not correct!" << std::endl;
        std::vector<std::vector<double> > myHelpVector(4,std::vector<double>(4));
        Lattice myHelpLattice(4, myHelpVector);
        vertices = myHelpVector;
        lattice = myHelpLattice;
    }
    std::vector<std::vector<double> > verticesBase = polytopeBase.getVertices();
    std::vector<std::vector<double> > verticesFiber = polytopeFiber.getVertices();
    std::vector<std::vector<double> > verticesFiberDual = myDualPolytopeFiber.getVertices();
    std::vector<std::vector<double> > verticesBaseScaled = polytopeBase.getVertices();
    int scalingFactor = 1;
    
    std::vector<double> choiceFiberVector = verticesFiber[choiceFiber];
    std::vector<double> choiceFiberDualVector = verticesFiberDual[choiceFiberDual];
    if( isDual == false)
    {
    //Determine scaling factor
    
    
    int scalingFactor = std::inner_product(choiceFiberVector.begin(), choiceFiberVector.end(), choiceFiberDualVector.begin(), 0) + 1;
    }
    //Scale base polytope
    for(int i = 0; i < verticesBase.size(); ++i)
    {
        for(int j = 0; j < polytopeBase.getLattice().getDimension(); ++j)
        {
            verticesBaseScaled[i][j]=verticesBase[i][j]*scalingFactor;
        }
    }
    
    //Create vertices
    std::vector<std::vector<double> > myPolytopeVertices(verticesBase.size() + verticesFiber.size(),std::vector<double>(4));
    for(int i = 0; i < verticesBase.size() + verticesFiber.size(); ++i)
    {
        for(int j = 0; j < polytopeBase.getLattice().getDimension(); ++j)
        {
            if(i < verticesBase.size())
            {
                myPolytopeVertices[i][j] = verticesBaseScaled[i][j];
                myPolytopeVertices[i][j+2] = choiceFiberVector[j];
            }
            else 
            {
                myPolytopeVertices[i][j] = 0;
                myPolytopeVertices[i][j+2] = verticesFiber[i-verticesBase.size()][j];
            }
        }
    }
    
    //Create 4D lattice from 2D lattice data DOES NOT WORK YET!!!!!!!
    /*Lattice baseLattice = polytopeBase.getLattice();
    Lattice fiberLattice = polytopeFiber.getLattice();
    int dimBaseLattice = baseLattice.getDimension();
    int dimFiberLattice = fiberLattice.getDimension();
    std::vector<std::vector<double> > myNewLatticeBasis(dimBaseLattice+dimFiberLattice,std::vector<double>(4));
    std::vector<std::vector<double> > baseLatticeBasis = baseLattice.getBasisVectors();
    std::vector<std::vector<double> > fiberLatticeBasis = fiberLattice.getBasisVectors();
    for(int i = 0; i < dimBaseLattice+dimFiberLattice; ++i)
    {
        for(int j = 0; j < dimBaseLattice+dimFiberLattice; ++j)
        {
            if(i < dimBaseLattice)
            {
                myNewLatticeBasis[i][j] = baseLatticeBasis[i][j];
                myNewLatticeBasis[i][j+2] = 0;
            }
            else 
            {
                myNewLatticeBasis[i][j] = 0;
                myNewLatticeBasis[i][j+2] = fiberLatticeBasis[i-dimBaseLattice][j];
            }
        }
    }
    //Output
    Lattice myLattice(4, myNewLatticeBasis);*/
    std::vector<std::vector<double> > basis(4,std::vector<double>(4));
    basis[0][0] = 1;
    basis[0][1] = 0;
    basis[0][2] = 0;
    basis[0][3] = 0;
    
    basis[1][0] = 0;
    basis[1][1] = 1;
    basis[1][2] = 0;
    basis[1][3] = 0;
    
    basis[2][0] = 0;
    basis[2][1] = 0;
    basis[2][2] = 1;
    basis[2][3] = 0;
    
    basis[3][0] = 0;
    basis[3][1] = 0;
    basis[3][2] = 0;
    basis[3][3] = 1;
    Lattice myLattice(4,basis);
    lattice = myLattice;
    vertices = myPolytopeVertices;  
}

Polytope::~Polytope(){}

void Polytope::setVertices(std::vector<std::vector<double> > _vertices)
{
    vertices = _vertices;
}

void Polytope::setLattice(Lattice _lattice)
{
    lattice = _lattice;
}

std::vector<std::vector<double> > Polytope::getVertices()
{
    return vertices;
}

std::vector<std::vector<double> > Polytope::getVerticesInLattice()
{
    std::vector<std::vector<double> > verticesInLattice(vertices.size(),std::vector<double>(lattice.getDimension()));
    for(int i = 0; (unsigned) i < vertices.size(); i++)
    {
        std::vector<double> myVertex = vertices[i];
        for(int j = 0; (unsigned) j < vertices[i].size(); j++)
        {
            for(int k = 0; (unsigned) k < lattice.getDimension(); k++)
            {
                verticesInLattice[i][j] += myVertex[j]*lattice.getBasisVectors()[k][j];
            }
        }
    }

    return verticesInLattice;
}

int Polytope::getNrOfVertices()
{
    return vertices.size();
}

Lattice Polytope::getLattice()
{
    return lattice;
}

std::vector<double> Polytope::getSpecificVertex(int vertexNr)
{
    if ((unsigned) vertexNr >= 0 and (unsigned) vertexNr <= vertices.size() - 1)
    {
        return vertices.at(vertexNr);
    }
    else
    {
        std::cout << "Vertex number specified is higher than number of vertices, counting starts from zero!" << std::endl;
        return std::vector<double>(1);
    }   
}

int Polytope::getNrOfIntPointsPolytope()
{
    int nrOfIntPointsPolytope = 0;
    for(int i = 0;(unsigned) (i < lattice.getDimension()); i++)
    {
        nrOfIntPointsPolytope = i;
    }
    return nrOfIntPointsPolytope;
}

std::vector< std::vector<std::vector<double> > > Polytope::getVectorsPointingBetweenVertices()
{
    std::vector<std::vector<double> > myHelpVector(vertices.size(),std::vector<double>(lattice.getDimension()));
    std::vector<std::vector<std::vector<double> > > myDifference(vertices.size(),myHelpVector);
    
    for(int j = 0; (unsigned) (j < vertices.size()); ++j)
    {
        std::vector<double> vectorOne = vertices[j];
        for(int k = 0; (unsigned) (k < vertices.size()); ++k)
        { 
            if((unsigned) k != j)
            {
                std::vector<double> vectorTwo = vertices[k];
                if((unsigned) (vectorOne.size() == vectorTwo.size()))
                {
                    for(int i = 0; (unsigned) i < vectorOne.size(); ++i)
                    {
                        myDifference[j][k][i] = vectorTwo[i] - vectorOne[i];
                    }
                }
                else
                {
                    std::cout << "Vector dimensions do not match!";
                }
            }
        }
    }

    return myDifference;
}

std::vector<std::vector<Line> > Polytope::getLinesBetweenVertices()
{
    std::vector<double> myHelpVector(lattice.getDimension());
    std::vector<Line> myHelpLines(vertices.size(),Line(myHelpVector,myHelpVector,myHelpVector));
    std::vector<std::vector<Line >> myLines(vertices.size(),myHelpLines);
    
    for(int i = 0; (unsigned) i < vertices.size(); ++i)
    {
        for(int j = 0; (unsigned) j < vertices.size(); ++j)
        {
            if ((unsigned) j != i)
            {
                myLines[i][j] = Line(getVectorsPointingBetweenVertices()[i][j],vertices[i],vertices[j]);
            }
        } 
    }
    return myLines;
}

//Works only in 2 dimensions.
std::vector<int> Polytope::getVerticesOrder()
{
    int nrOfVertices = vertices.size();
    std::vector<int> newOrder(nrOfVertices,0);
    float pi = atan(1)*4;
    
    if(lattice.getDimension() == 2)
    {
        std::vector<double> myAngles(nrOfVertices,0);
        for(int i = 0; i<nrOfVertices; ++i)
        {
            myAngles[i]= atan((vertices[i][1])/(vertices[i][0]));
            if(myAngles[i]>0 and vertices[i][1]<0)
            {
                myAngles[i] = myAngles[i] + pi;
            }
            else if(myAngles[i]<0 and vertices[i][1]<0)
            {
                myAngles[i] = myAngles[i] + 2*pi;
            }
            else if(myAngles[i]<0 and vertices[i][1]>0)
            {
                myAngles[i] = myAngles[i] + pi;
            }
            //std::cout << "Angle belonging to vertex " << i << " is " << myAngles[i] <<std::endl;
        }
        bool isVerticesOrdered = false;

        for(int i =0; i<nrOfVertices;++i)
        {
            newOrder[i]=i;
        }
        while(isVerticesOrdered == false)
        {
            bool troubles = false;
            for(int i = 0; i< nrOfVertices; ++i)
            {
                for(int j = 0; j<i; ++j)
                {
                    if( myAngles[i] < myAngles[j] )
                    {
                        myAngles.push_back(myAngles[j]);
                        myAngles.erase(myAngles.begin() + j);
                        newOrder.push_back(newOrder[j]);
                        newOrder.erase(newOrder.begin() + j);
                        troubles = true;
                    }
                }
            }
            if (troubles == false)
            {
                isVerticesOrdered = true;
            }
        }
    }
    return newOrder;
}

//Works only in 2 dimensions.
std::vector<Line> Polytope::getEdges()
{
    int nrOfVertices = vertices.size();
    std::vector<std::vector<Line> > linesBetweenVertices = getLinesBetweenVertices();
    std::vector<double> myHelpVector(lattice.getDimension());
    std::vector<Line> myEdges(0,Line(myHelpVector,myHelpVector,myHelpVector));
    
    std::vector<std::vector<Line> > myLines = getLinesBetweenVertices();
    if(lattice.getDimension() == 2)
    {
        std::vector<int> newOrder = getVerticesOrder();
        newOrder.push_back(newOrder[0]);
        
        for(int i = 0; i< nrOfVertices; ++i)
        {
            myEdges.push_back(myLines[newOrder[i]][newOrder[i+1]]);
        }  
    }      
    
    return myEdges;
}

//Works only in 2 dimensions.
std::vector<Cone> Polytope::getConesOverFaces()
{
    int nrOfVertices = vertices.size();
    std::vector<std::vector<double> > myHelpVector(nrOfVertices,std::vector<double>(lattice.getDimension()));
    std::vector<Cone> myCones(nrOfVertices,Cone(myHelpVector,lattice));
    std::vector<Line> myEdges = getEdges();
    std::vector<int> newOrder = getVerticesOrder();
    if(lattice.getDimension() == 2)
    {
        for(int i = 0; i < nrOfVertices; ++i)
        {
           Line myLine = myEdges[i];
           std::vector<double> myBeginPoint = myLine.getBeginPoint();
           std::vector<double> myEndPoint = myLine.getEndPoint();            
           
           std::vector<double> myFirstBorderPoint = getSpecificVertex(newOrder[(i-1+nrOfVertices)%nrOfVertices]);
           std::vector<double> mySecondBorderPoint = getSpecificVertex(newOrder[(i+2)%nrOfVertices]);
           
           std::vector<double> myDiff1(lattice.getDimension());
           std::vector<double> myDiff2(lattice.getDimension());
           
           myDiff1[0] = myEndPoint[0] - myFirstBorderPoint[0];
           myDiff1[1] = myEndPoint[1] - myFirstBorderPoint[1];
           myDiff2[0] = myBeginPoint[0] - mySecondBorderPoint[0];
           myDiff2[1] = myBeginPoint[1] - mySecondBorderPoint[1];
           
           std::vector<std::vector<double> > myRays = {myDiff1,myDiff2};
           Cone myCone(myRays,lattice);
           myCones[i]=myCone;
        }
    }
    return myCones;
}

//Works only in 2 dimensions.
Fan Polytope::getCorrespondingDualFan()
{
    std::vector<Cone> myCones = getConesOverFaces();
    Fan myFan(myCones,lattice);
    return myFan;
}
//Works only in 2 dimensions.
int Polytope::drawPolytope()
{
    std::vector<int> newOrder = getVerticesOrder();
    newOrder.push_back(newOrder[0]);
    int nrOfVertices = vertices.size();
    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Polytope", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glLineWidth(2.5);
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        for(int i = 0; i < nrOfVertices; ++i)
        {
            glVertex3f(vertices[newOrder[i]][0], vertices[newOrder[i]][1], vertices[newOrder[i]][2]);
            glVertex3f(vertices[newOrder[i+1]][0], vertices[newOrder[i+1]][1], vertices[newOrder[i]][2]);
        }
        glEnd();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    
    return 0;
}

//method itself depends on 2d methods
Polytope Polytope::getCorrespondingDualPolytope()
{
    Fan myDualFan = getCorrespondingDualFan();
    Fan myFan = myDualFan.getCorrespondingDualFan();
    
    std::vector<std::vector<double> > myHelpVector(0,std::vector<double>(lattice.getDimension()));
    
    std::vector<Cone> myCones = myFan.getCones();
    int nrOfCones = myCones.size();
    for(int i = 0; i < nrOfCones; ++i)
    {
        Cone myCone = myCones[i];
        std::vector<std::vector<double> > myBVs = myCone.getBasisVectors();
        int nrOfBVs = myBVs.size();
        for(int j = 0; j < nrOfBVs; ++j)
        {
            myHelpVector.push_back(myBVs[j]);
        }
    }
    
    Polytope myPolytope(myHelpVector,lattice);
    return myPolytope;
}

bool Polytope::isPointInsidePolytope(std::vector<double> Point)
{
    bool myBool = false;
    
    //http://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
    return myBool;
}
