//
//  cloud.hpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 12.10.2020.
//

#ifndef cloud_hpp
#define cloud_hpp

#include <iostream>
#include <stdio.h>
#include <vector>

#include "point.hpp"

using namespace std;
//CREATED BY ARSENIY KLEVAKIN 211 GROUP
class cloud{ //klas oblako
public:
    long countP;
    int Numcl=0;
    vector<point> points;
    void gen(double x, double y, double Dx, double Dy, int N);
    double sampleNormal();
};

#endif /* cloud_hpp */
