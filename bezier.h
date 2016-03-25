#ifndef BEZIER_H
#define BEZIER_H

//#include "bezier_global.h"
#include <vector>
#include <string>
#include "Point.h"

using namespace std;

class Bezier//BEZIERSHARED_EXPORT Bezier
{

public:	
    Bezier();
    void addpoint(Point p);
    void addpointsXY(vector<int> x, vector<int> y);
	void addpointsXY2(int x[], int y[]);
    //vector<Point> points;
    vector<Point> findCurve();
    vector<Point> findCurveCubic();
    void setDensity(int density);
	vector<Point> getpoints();
	void writeToFile(string name, vector<Point> source);
private:
	int density;
	vector<Point> points;
};

#endif // BEZIER_H
