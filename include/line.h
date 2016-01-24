#include <iostream>
#include <vector>

class Line
{
    private:
    std::vector<double> direction{0};
    std::vector<double> beginPoint{0};
    std::vector<double> endPoint{0};

    public:
    Line(std::vector<double> dir, std::vector<double> beg, std::vector<double> end);
    ~Line();
    std::vector<double> getDirection();
    std::vector<double> getBeginPoint();
    std::vector<double> getEndPoint();
};
