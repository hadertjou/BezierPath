Add Bezier and point classes. 

Create points and use Bezier::addPoint() method to add to Bezier object. Or create two equal length vectors with X values and Y values and use addPointsXY().

adddPointsXY2() will take two int arrays.

Once all points have been added, call findCurve() to return interpolated series of points in a vector. 

Optionally, change density with setDensity() to control how many interpolated points per provided point returned. Default is 10.

