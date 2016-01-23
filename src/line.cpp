#include <iostream>
#include <vector>
#include "line.h"

using namespace std;

Line::Line(std::vector<double> dir, std::vector<double> beg, std::vector<double> end)
{
    direction = dir;
    beginPoint = beg;
    endPoint = end;
}

Line::~Line(){}

std::vector<double> Line::getDirection()
{
    return direction;
}
std::vector<double> Line::getBeginPoint()
{
    return beginPoint;
}
std::vector<double> Line::getEndPoint()
{
    return endPoint;
}

