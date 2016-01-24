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
