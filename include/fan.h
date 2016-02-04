#include "cone.h"
#include <vector>

class Fan
{
    private:
    std::vector<Cone> cones{0,Cone(std::vector<std::vector<double> >(0,std::vector<double>(0)))};
    public:
    Fan(std::vector<Cone> con);
    ~Fan();
    void setCones(std::vector<Cone> con);
    std::vector<Cone> getCones();
    Fan getCorrespondingDualFan();
};
