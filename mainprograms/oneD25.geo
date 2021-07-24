// Gmsh project created on Sat Jul 24 16:00:57 2021
SetFactory("OpenCASCADE");
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {25, 0, 0, 1.0};
//+
Line(1) = {1, 2};
//+
//+
Physical Curve("line", 1) = {1};
//+
Physical Point("left", 2) = {1};
//+
Physical Point("right", 3) = {2};
