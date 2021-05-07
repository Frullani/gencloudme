//
//  buffer.hpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 12.12.2020.
//

#ifndef buffer_hpp
#define buffer_hpp

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "cloud.hpp"

#include <stdio.h>
class buffer{
public:
    vector<point> B;
    void shift(point a);
    void homothety(double k);
};
#endif /* buffer_hpp */
