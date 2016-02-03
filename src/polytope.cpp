#include <iostream>
#include "polytope.h"
#include <math.h> 
#include <vector>


Polytope::Polytope(std::vector<std::vector<double> > _vertices, Lattice _lattice)
{
    vertices = _vertices;
    lattice = _lattice;
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
    
    //j selects the first vertex
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
//doesn't work yet, need algorithm to do this in general dimensions
/*std::vector<Line> Polytope::getEdges()
{
    int nrOfVertices = vertices.size();
    std::vector<std::vector<Line> > linesBetweenVertices = getLinesBetweenVertices();
    std::vector<double> myHelpVector(lattice.getDimension());
    std::vector<Line> myEdges(0,Line(myHelpVector,myHelpVector,myHelpVector));
    std::cout << "Lattice dimension = " << lattice.getDimension() << std::endl;
    std::cout << "NR of vertices = " << nrOfVertices << std::endl;
    
    //get vertices starting from i
    for(int i = 0; (unsigned) i < nrOfVertices; ++i)
    {
        std::cout << "We start with vertex nr " << i << std::endl;
        //get candidate j
        for(int j = 0; ((unsigned) j < i); ++j)
        {   
            //std::cout << "Let us check CANDIDATE nr " << j << std::endl;       
            std::vector<double> myDifferencesCandidate(lattice.getDimension());
            for(int d = 0; (unsigned) d < lattice.getDimension(); ++d)
            {
                myDifferencesCandidate[d] = vertices[i][d] - vertices[j][d];
                //std::cout << "Value of candidate" << myDifferencesCandidate[d] << std::endl;
            }
            //get check k, flagcheck becomes false if j is not a good candidate
            bool flagCheck = true;
            std::vector<bool> vectorOfFlagCheck(lattice.getDimension(), false);
            for(int k = 0; ((unsigned) k < nrOfVertices); ++k)
            {
                std::vector<double> myDifferencesCheck(lattice.getDimension());
                for(int d = 0; (unsigned) d < lattice.getDimension(); ++d)
                {
                    myDifferencesCheck[d] = vertices[i][d] - vertices[k][d];
                    
                    //std::cout << "We are looking in direction " << d << std::endl;
                    //std::cout << "Value of check" << myDifferencesCheck[d] << std::endl; 
                    
                    if(myDifferencesCheck[d] >= 0 and myDifferencesCandidate[d]>=0 and myDifferencesCheck[d] < myDifferencesCandidate[d])
                    {
                        vectorOfFlagCheck[d] = true;
                    }
                    else if (myDifferencesCheck[d] <= 0 and myDifferencesCandidate[d] <= 0 and myDifferencesCheck[d] > myDifferencesCandidate[d])
                    {
                        vectorOfFlagCheck[d] = true;
                    }
                }
            }
            for(int d = 0; (unsigned) d < lattice.getDimension(); ++d)
            {
                if(vectorOfFlagCheck[d] == true)
                {
                    flagCheck = false;
                }
            }
            if (flagCheck == true)
            {
                myEdges.insert(myEdges.end(),linesBetweenVertices[i][j]);
            }
        }
        std::cout << "We have reached the end of the candidates, edges is this big now: " <<myEdges.size() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
    return myEdges;
}*/

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

std::vector<Cone> Polytope::getConesOverFaces()
{
    int nrOfVertices = vertices.size();
    std::vector<std::vector<double> > myHelpVector(nrOfVertices,std::vector<double>(lattice.getDimension()));
    std::vector<Cone> myCones(nrOfVertices,myHelpVector);
    std::vector<Line> myEdges = getEdges();
    std::vector<int> newOrder = getVerticesOrder();
    if(lattice.getDimension() == 2)
    {
        for(int i = 0; i < nrOfVertices; ++i)
        {
           Line myLine = myEdges[i];
           std::vector<double> myBeginPoint = myLine.getBeginPoint();
           std::vector<double> myEndPoint = myLine.getEndPoint(); 
           
           std::vector<double> myFirstBorderPoint = getSpecificVertex(newOrder[(i-1)%nrOfVertices]);
           std::vector<double> mySecondBorderPoint = getSpecificVertex(newOrder[(i+2)%nrOfVertices]);
           
           std::vector<double> myDiff1(lattice.getDimension());
           std::vector<double> myDiff2(lattice.getDimension());
           
           myDiff1[0] = myEndPoint[0] - myFirstBorderPoint[0];
           myDiff1[1] = myEndPoint[1] - myFirstBorderPoint[1];
           myDiff2[0] = myBeginPoint[0] - mySecondBorderPoint[0];
           myDiff2[1] = myBeginPoint[1] - mySecondBorderPoint[1];
           
           std::vector<std::vector<double> > myRays = {myDiff1,myDiff2};
           Cone myCone(myRays);
           myCones[i]=myCone;
        }
    }
    return myCones;
}



void Polytope::drawPolytope()
{
    return;
}
