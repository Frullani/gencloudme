//
//  claster.hpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//

#ifndef claster_hpp
#define claster_hpp

#include <stdio.h>
#include <vector>

#include "point.hpp"

using namespace std;

class claster{
public:
    double color;
    point centr_mass;
    claster();
    vector<point*> points;
    long Num;
    int NumP;
};

#endif /* claster_hpp */
