#include "cone.h"
#include "lattice.h"
#include <vector>

class Fan
{
    private:
    Lattice lattice{Lattice(0,std::vector<std::vector<double> >(0,std::vector<double>(0)))};
    std::vector<Cone> cones{0,Cone(std::vector<std::vector<double> >(0,std::vector<double>(0)),lattice)};
    public:
    Fan(std::vector<Cone> con, Lattice lat);
    ~Fan();
    void setCones(std::vector<Cone> con);
    std::vector<Cone> getCones();
    Fan getCorrespondingDualFan();
};
