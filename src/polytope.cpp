#include <iostream>
#include "polytope.h"


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
std::vector<Line> Polytope::getEdges()
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
}

Cone Polytope::getConeOverFace()
{
    Cone myCone(vertices);
    return myCone;
}



void Polytope::drawPolytope()
{
    return;
}
