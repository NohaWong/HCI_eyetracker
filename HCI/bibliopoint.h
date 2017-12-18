#ifndef BIBLIOPOINT_H
#define BIBLIOPOINT_H
#include <vector>
#include "point.h"

using namespace std;

class biblioPoint
{
public:
    biblioPoint();
    biblioPoint(vector<Point*> ips,vector<int> nums);
    vector<Point*> ips;
    vector<int> nums;
};

#endif // BIBLIOPOINT_H
