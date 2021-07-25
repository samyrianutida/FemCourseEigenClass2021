// Gmsh project created on Sat Jul 24 12:14:57 2021
SetFactory("OpenCASCADE");
a = 30;
Rectangle(1) = {0, 0, 0, 1, 1, 0};
//+
Physical Point("fix", 3) = {1};
//+
Physical Curve("contorno", 2) = {4, 1, 2, 3};
//+
Physical Surface("plano", 1) = {1};
//+
//Transfinite Surface {1};
//+
Transfinite Curve {4, 2} = a Using Progression 1;
//+
Transfinite Curve {1, 3} = a Using Progression 1;