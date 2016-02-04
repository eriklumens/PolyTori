#include <iostream>
#include <vector>
#include "fan.h"

Fan::Fan(std::vector<Cone> con)
{
    cones = con;
    return;
}

Fan::~Fan(){}

void Fan::setCones(std::vector<Cone> con)
{   
        cones = con;
        return;
}

std::vector<Cone> Fan::getCones()
{
    return cones;
}

Fan Fan::getCorrespondingDualFan()
{
    int dimensionOfLattice = 2;
    std::vector<std::vector<double> > myDualBasis(0,std::vector<double>(dimensionOfLattice));
    std::vector<Cone> myDualCones(0,Cone(myDualBasis));
    
    for(int i = 0; i < cones.size(); ++i)
    {
        Cone myCone = cones[i];
        Cone myDualCone = myCone.getCorrespondingDualCone();
        myDualCones.push_back(myDualCone);
    }
    
    Fan myDualFan(myDualCones);
    return myDualFan;
}
