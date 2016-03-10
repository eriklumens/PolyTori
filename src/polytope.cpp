#include <iostream>
#include <numeric>
#include "polytope.h"
#include <math.h> 
#include <vector>
#include <string>
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
    std::cout << "choice fiber vector: (" << choiceFiberVector[0] << "," << choiceFiberVector[1] << ")" << std::endl;
    std::cout << "choice fiber dual vector: (" << choiceFiberDualVector[0] << "," << choiceFiberDualVector[1] << ")" << std::endl;
    
    if( isDual == false)
    {
        //Determine scaling factor 
        scalingFactor = choiceFiberVector[0]*choiceFiberDualVector[0] + choiceFiberVector[1]*choiceFiberDualVector[1] + 1;
         
        //scalingFactor = std::inner_product(choiceFiberVector.begin(), choiceFiberVector.end(), choiceFiberDualVector.begin(), 0) + 1;
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
            myAngles[i]= atan2((vertices[i][1]),(vertices[i][0]));
            if (myAngles[i] < 0)
            {
                myAngles[i] = 2*pi + myAngles[i];
            }
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

Fan Polytope::getCorrespondingDualFan()
{
    int nrOfVertices = vertices.size();

    std::vector<std::vector<double> > myHelpVector(nrOfVertices,std::vector<double>(lattice.getDimension()));
    std::vector<Cone> myCones(nrOfVertices,Cone(myHelpVector,lattice));
    std::vector<int> newOrder = getVerticesOrder();
    if(lattice.getDimension() == 2)
    {
        for(int i = 0; i < nrOfVertices; ++i)
        {
           std::vector<double> myVertex = getSpecificVertex(newOrder[i]);
           std::vector<double> myNextVertex = getSpecificVertex(newOrder[(i+1)%nrOfVertices]);
           std::vector<double> myPreviousVertex = getSpecificVertex(newOrder[(i-1+nrOfVertices)%nrOfVertices]);
           
           
           std::vector<double> myDiff1(lattice.getDimension());
           std::vector<double> myDiff2(lattice.getDimension());
           
           myDiff1[0] = myNextVertex[0] - myVertex[0];
           myDiff1[1] = myNextVertex[1] - myVertex[1];
           myDiff2[0] = myPreviousVertex[0] - myVertex[0];
           myDiff2[1] = myPreviousVertex[1] - myVertex[1];
           
           std::vector<std::vector<double> > myRays = {myDiff1,myDiff2};
           Cone myCone(myRays,lattice);
           myCones[i]=myCone;
        }
    }
    Fan myFan(myCones, lattice);
    return myFan;
}

//Works only in 2 dimensions.
Fan Polytope::getCorrespondingFan()
{
    Polytope myDualPolytope = getCorrespondingDualPolytope();
    std::vector<Cone> myCones = myDualPolytope.getConesOverFaces();
    Fan myFan(myCones,lattice);
    return myFan;
}

double Polytope::scalingFactor()
{
    std::vector<std::vector<double> > myVertices = getVertices();
    int nrOfVertices = myVertices.size();
    double myScaling = 1;
    for(int i = 0; i < nrOfVertices; ++i)
    {
        for(int j = 0; j < lattice.getDimension(); ++j)
        {
            if(abs(myVertices[i][j]) > myScaling)
            {
                myScaling = abs(myVertices[i][j]);
            }
        }
    }
    return myScaling;
}
//Works only in 2 dimensions.
int Polytope::drawPolytope()
{
    double myScaling = scalingFactor();
    std::string s = std::to_string(myScaling);
    std::string str = "Polytope with scaling ";
    str.append(s);
    const char * c = str.c_str();
    
    int nrOfVertices = vertices.size();
    if(nrOfVertices == 0)
    {
        return -1;
    }
    std::vector<int> newOrder = getVerticesOrder();
    newOrder.push_back(newOrder[0]);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, c, NULL, NULL);
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
            glVertex3f(vertices[newOrder[i]][0]/myScaling, vertices[newOrder[i]][1]/myScaling, vertices[newOrder[i]][2]/myScaling);
            glVertex3f(vertices[newOrder[i+1]][0]/myScaling, vertices[newOrder[i+1]][1]/myScaling, vertices[newOrder[i]][2]/myScaling);
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

Polytope Polytope::cleanUpExtraVertices()
{
    int nrOfVertices = vertices.size();
    std::vector<std::vector<double> > myVertices = vertices;
    for(int i = 0; i < nrOfVertices; ++i)
    {
        
        for(int j = 0; j < i; ++j)
        {
            
            if(myVertices[i]== myVertices[j])
            {                
                myVertices.erase(myVertices.begin()+i);
                nrOfVertices = myVertices.size();
                i = i - 1;
            }
        }
    }
    Polytope myPolytope(myVertices, lattice);
    return myPolytope;
}

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
            bool coordinate0Integer = false;
            bool coordinate1Integer = false;
            if ((myBVs[j][0] == floor(myBVs[j][0])) && isfinite(myBVs[j][0])) 
            {
                coordinate0Integer = true;
            }
            
            if ((myBVs[j][1] == floor(myBVs[j][1])) && isfinite(myBVs[j][1])) 
            {
                coordinate1Integer = true;
            }
            
            if(coordinate0Integer && coordinate1Integer)
            {
                myHelpVector.push_back(myBVs[j]);
            }
            else if(!coordinate0Integer && coordinate1Integer)
            {
                double testValue = myBVs[j][0];
                int scaleFactor = 1;
                while(!coordinate0Integer)
                {
                    testValue = testValue * scaleFactor;
                    scaleFactor = scaleFactor + 1; 
                    if ((testValue == floor(testValue)) && isfinite(testValue)) 
                    {
                        coordinate0Integer = true;
                        scaleFactor = scaleFactor - 1;
                    }   
                }
                if(scaleFactor > 1000)
                {
                    std::cout << "scaleFactor is getting really big, please abort program!" << std::endl;
                }
                myBVs[j][0] = myBVs[j][0] * scaleFactor;
                myBVs[j][1] = myBVs[j][1] * scaleFactor;
                myHelpVector.push_back(myBVs[j]);
            }
            else if(coordinate0Integer && !coordinate1Integer)
            {
                double testValue = myBVs[j][1];
                int scaleFactor = 1;
                while(!coordinate1Integer)
                {
                    testValue = testValue * scaleFactor;
                    scaleFactor = scaleFactor + 1; 
                    if ((testValue == floor(testValue)) && isfinite(testValue)) 
                    {
                        coordinate1Integer = true;
                        scaleFactor = scaleFactor - 1;
                    }   
                    if(scaleFactor > 1000)
                    {
                        std::cout << "scaleFactor is getting really big, please abort program!" << std::endl;
                    }
                }
                
                myBVs[j][0] = myBVs[j][0] * scaleFactor;
                myBVs[j][1] = myBVs[j][1] * scaleFactor;
                myHelpVector.push_back(myBVs[j]);
            }
            else if(!coordinate0Integer && !coordinate1Integer)
            {
                double testValue0 = myBVs[j][0];
                int scaleFactor0 = 1;
                while(!coordinate0Integer)
                {
                    testValue0 = testValue0 * scaleFactor0;
                    scaleFactor0 = scaleFactor0 + 1; 
                    if ((testValue0 == floor(testValue0)) && isfinite(testValue0)) 
                    {
                        coordinate0Integer = true;
                        scaleFactor0 = scaleFactor0 - 1;
                    }  
                    if(scaleFactor0 > 1000)
                    {
                        std::cout << "scaleFactor is getting really big, please abort program!" << std::endl;
                    } 
                }
                double testValue1 = myBVs[j][1];
                int scaleFactor1 = 1;
                while(!coordinate1Integer)
                {
                    testValue1 = testValue1 * scaleFactor1;
                    scaleFactor1 = scaleFactor1 + 1; 
                    if ((testValue1 == floor(testValue1)) && isfinite(testValue1)) 
                    {
                        coordinate1Integer = true;
                        scaleFactor1 = scaleFactor1 - 1;
                    }  
                    if(scaleFactor1 > 1000)
                    {
                        std::cout << "scaleFactor is getting really big, please abort program!" << std::endl;
                    } 
                }
                int scaleFactor = 1;
                if(scaleFactor1 % scaleFactor0 == 0)
                {
                    scaleFactor = scaleFactor1;
                }
                else if(scaleFactor0 % scaleFactor1 == 0)
                {
                    scaleFactor = scaleFactor0;
                }
                else
                {
                    scaleFactor = scaleFactor1 * scaleFactor0;
                }
                myBVs[j][0] = myBVs[j][0] * scaleFactor;
                myBVs[j][1] = myBVs[j][1] * scaleFactor;
                myHelpVector.push_back(myBVs[j]);
            }
        }
    }
    
    Polytope myPolytope(myHelpVector,lattice);
    
    myPolytope = myPolytope.cleanUpExtraVertices();
    return myPolytope;
}

Polytope Polytope::getModularTransform(int a, int b, int c, int d)
{
    if(abs(a*d-b*c) != 1)
    {
        std::cout << "Not an element of GL(2,Z) with Det = +-1! Aborting modular transform!" << std::endl;
        std::vector<std::vector<double> > myHelpVector(0,std::vector<double>(lattice.getDimension()));
        Polytope myPolytope(myHelpVector,lattice);
        return myPolytope;
    }
    std::vector<std::vector<double> > myVertices = getVertices();
    int nrOfVertices = myVertices.size();
    for(int i = 0; i < nrOfVertices; ++i)
    {
        double xValue = myVertices[i][0];
        double yValue = myVertices[i][1];
        myVertices[i][0] = a*xValue + b*yValue;
        myVertices[i][1] = c*xValue + d*yValue;
    }
    Polytope myPolytope(myVertices, lattice);
    return myPolytope;
}

double Polytope::getPolytopeArea()
{
    double myArea = 0;
    std::vector<std::vector<double> > myVertices = getVertices();
    int nrOfVertices = myVertices.size();
    int j = 0;
    
    if(nrOfVertices == 0)
    {
        return -1;
    }
    std::vector<int> newOrder = getVerticesOrder();
    newOrder.push_back(newOrder[0]);
    
    for(int i=0; i < nrOfVertices; ++i) 
    {
      j = (i + 1) % nrOfVertices;
      myArea += myVertices[newOrder[i]][0] * myVertices[newOrder[j]][1];
      myArea -= myVertices[newOrder[i]][1] * myVertices[newOrder[j]][0];
    }

    myArea /= 2;
    return(myArea < 0 ? -myArea : myArea);
}

std::vector<std::vector<double> > Polytope::getNrOfIntegerPointsLine(std::vector<double> beginPoint, std::vector<double> endPoint)
{
    std::vector<std::vector<double> > myHelpVector(0,std::vector<double>(lattice.getDimension()));
    if(beginPoint == endPoint)
    {
        myHelpVector.push_back(beginPoint);
        return myHelpVector;
    }
    int dim = lattice.getDimension();
    if(beginPoint[0] == endPoint[0])
    {
        std::vector<double> dimRedBegin = beginPoint;
        std::vector<double> dimRedEnd = endPoint;
        std::vector<std::vector<double> > dimRedBasisVectors = lattice.getBasisVectors();
        dimRedBegin.erase(dimRedBegin.begin());
        dimRedEnd.erase(dimRedEnd.begin());
        dimRedBasisVectors.erase(dimRedBasisVectors.begin());
        Lattice dimRedLattice(dim - 1, dimRedBasisVectors);
        Polytope myPol({dimRedBegin,dimRedEnd},dimRedLattice);
        std::vector<std::vector<double> > myIntegerPoints = myPol.getNrOfIntegerPointsLine(dimRedBegin,dimRedEnd);
        int myNrOfIntegerPoints = myIntegerPoints.size();
        for( int i = 0; i < myNrOfIntegerPoints; ++i)
        {
            std::vector<double> myPoint = myIntegerPoints[i];
            myPoint.insert(myPoint.begin(),beginPoint[0]);
            myIntegerPoints[i] = myPoint;
        }
        return myIntegerPoints;
    }
    

    double m[dim-1];
    double b[dim-1];
    int run = 0;
    int climb = 0;
    
    for(int i = 1; i < dim; ++i)
    {
        climb = endPoint[i]-beginPoint[i];
        run = endPoint[0]-beginPoint[0];
        m[i-1] = climb/run;
        b[i-1] = beginPoint[i]-m[i-1]*beginPoint[0];
    }
    
    double y[dim-1];
    int rounded[dim-1];
    
    for (int x = beginPoint[0]; x <= endPoint[0]; ++x)
    {
        bool isAnInteger = true;
        // solve for y
        for(int i = 1; i < dim; ++i)
        {
            y[i-1] = m[i-1]*x + b[i-1];
        // round to nearest int
            rounded[i-1] = (y[i-1] > 0.0) ? floor(y[i-1] + 0.5) : ceil(y[i-1] - 0.5);
        
            // convert int result back to float, compare
            if ((float) rounded[i-1] != y[i-1])
            {
                isAnInteger = false;
            }
        }
        if(isAnInteger == true)
        {
            std::vector<double> integerPoint;
            integerPoint.push_back(x);
            for(int i = 1; i < dim; ++i)
            {
                integerPoint.push_back(y[i-1]);
            } 
            myHelpVector.push_back(integerPoint);
        }
    }
    return myHelpVector;
}

bool Polytope::isPointInsidePolytope(std::vector<double> Point)
{
    bool myBool = false;
    
    //http://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
    return myBool;
}
