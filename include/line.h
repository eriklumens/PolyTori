#include <iostream>
#include <vector>

class Line
{
    private:
    std::vector<double> direction{1};
    std::vector<double> beginPoint{1};
    std::vector<double> endPoint{1};

    public:
    Line(std::vector<double> dir, std::vector<double> beg, std::vector<double> end);
    ~Line();
    std::vector<double> getDirection();
    std::vector<double> getBeginPoint();
    std::vector<double> getEndPoint();
};
