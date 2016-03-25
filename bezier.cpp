#include <vector>
#include <Math.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Bezier.h"
#include "Point.h"

using namespace std;

Bezier::Bezier()
{
    //this->points;// = new vector<Point>();
    this->density = 10;
}


void Bezier::addpoint(Point p)
{

    this->points.push_back(p);

}

vector<Point> Bezier::getpoints()
{
    return this->points;
}

void Bezier::setDensity(int density)
{

	this->density = density;
}

void Bezier::writeToFile(string file, vector<Point> source)
{
	ofstream oufile;
	oufile.open(file.c_str());//, ofstream::out);
	for(int i = 0; i < this->points.size(); i++)
	{
		oufile << source.at(i).x << " " << source.at(i).y << endl;
	}
	oufile.close();
	
	
	
}

void Bezier::addpointsXY(vector<int> x, vector<int> y)
{
	for(int i = 0; i < x.size(); i++)
	{
		Point p;
		p.x = x.at(i);
		p.y = y.at(i);
		this->points.push_back(p);
	}

}

void Bezier::addpointsXY2(int x[], int y[])
{
//	
//	if(x.size() != y.size())
//	{
//		printf("error: size of arrays unequal");
//	}
//	for(int i = 0; i < x.size(); i++)
//	{
//		Point p;
//		p.x = x.at(i);
//		p.y = y.at(i);
//		this->points[i] = p;
//		//this->points.push_back(p);
//	}

}

vector<Point> Bezier::findCurve()
{

	vector<Point> points = this->points;
	int d = this->density;
	vector<Point> result;// = new vector<Point>();
	Point p0, p1, curmid, prevmid;

	prevmid.x = (points.at(0).x + points.at(1).x) / 2;
	prevmid.y = (points.at(0).y + points.at(1).y) / 2;


	for(int i = 0; i < d; i++)
	{
		double t = i/d;
		Point p;
		p.x = (1 - t) * (1 - t) * points.at(0).x + 2 * (1 - t) * t * points.at(1).x + t * t * prevmid.x;
		p.y = (1 - t) * (1 - t) * points.at(0).y + 2 * (1 - t) * t * points.at(1).y + t * t * prevmid.y;
		result.push_back(p);
	}

	for (int i = 2; i < points.size()-2; i++)
	{
		p0 = points.at(i);
		p1 = points.at(i+1);

		curmid.x = (p0.x + p1.x) /2;
		curmid.y = (p0.y + p1.y) /2;

		for(int j = 0; j < d; j++)
		{
			double t = j/d;
			Point p;
			p.x = (1 - t) * (1 - t) * prevmid.x + 2 * (1 - t) * t * p0.x + t * t * curmid.x;
			p.y = (1 - t) * (1 - t) * prevmid.y + 2 * (1 - t) * t * p0.y + t * t * curmid.y;
			result.push_back(p);
			printf(p.x + " " +  p.y);
		}

		prevmid = curmid;

	}

	//to end
	for(int i = 0; i < d; i++)
	{
		double t = i/d;
		Point p;
		p.x = (1 - t) * (1 - t) * prevmid.x + 2 * (1 - t) * t * points.at(points.size()-2).x + t * t * points.at(points.size()-1).x;
		p.y = (1 - t) * (1 - t) * prevmid.y + 2 * (1 - t) * t * points.at(points.size()-2).y + t * t * points.at(points.size()-1).y;
		result.push_back(p);
	}
	
	return result;

}

//find cubic


//P(t) = (1 - t)^3 * P0 + 3t(1-t)^2 * P1 + 3t^2 (1-t) * P2 + t^3 * P3

vector<Point> Bezier::findCurveCubic()
{
	int d = this->density;
	vector<Point> points = this->points;
	vector<Point> result;
	Point p0, p1, p2, curmid, prevmid;

	prevmid.x = (points.at(2).x + points.at(3).x) / 2;
	prevmid.y = (points.at(2).y + points.at(3).y) / 2;

	for(int i = 0; i <points.size()-3; i+=2)
	{

		p0 = points.at(i);
		p1 = points.at(i+1);
		p2 = points.at(i+2);

		curmid.x = (p1.x + p2.x) / 2;
		curmid.y = (p1.y + p2.y) / 2;

		for(int j = 0; j < d; j++)
		{
			double t = j/d;
			Point p;
			p.x = pow((1 - t), 3) * prevmid.x + (3*t)*pow((1-t),2) * p0.x + pow((3*t), 2) * (1-t) * p1.x + pow(t, 3) * curmid.x;
			p.x = pow((1 - t), 3) * prevmid.y + (3*t)*pow((1-t),2) * p0.y + pow((3*t), 2) * (1-t) * p1.y + pow(t, 3) * curmid.y;
			result.push_back(p);

		}

		prevmid = curmid;
	}


	for(int i = 0; i < d; i++)
	{
		double t = i/d;
		Point p;
		p.x = pow((1 - t), 3) * prevmid.x + (3*t)*pow((1-t),2) * points.at(points.size()-3).x + pow((3*t),2) *(1-t) * points.at(points.size()-2).x + pow(t, 3) * points.at(points.size()-1).x;
		p.y = pow((1 - t), 3) * prevmid.y + (3*t)*pow((1-t),2) * points.at(points.size()-3).y + pow((3*t),2) *(1-t) * points.at(points.size()-2).y + pow(t, 3) * points.at(points.size()-1).y;
		result.push_back(p);

	}

	return result;


}
