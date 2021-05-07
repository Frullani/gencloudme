//
//  find_clasters.hpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//

#ifndef find_clasters_hpp
#define find_clasters_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

#include "claster.hpp"
#include "Graf_Matrix.hpp"
#include "marker_exp.hpp"

using namespace std;

class find_clasters{
public:
    Graf_Matrix *GM;
    marker_exp ME;
    vector<claster> clasters;
    long countClas=0;
    int FC_num;
    
    find_clasters();
    void new_cluster();
    void colorize();
};
#endif /* find_clasters_hpp */
