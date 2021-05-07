//
//  k_means.hpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 26.03.2021.
//

#ifndef k_means_hpp
#define k_means_hpp

#include <stdio.h>

#include "cloud.hpp"
#include "distant_matrix.hpp"
#include "find_clasters.hpp"
#include "buffer.hpp"

class k_means_cl{
    
    void k_means(int k);
    double mod(double a);
    double D(point a, point b);
    void razmetka(int k, vector<point> c);
    vector<point *> find_group(int metka, vector<point *> g);
    point center_mass(vector<point*> g);
};


#endif /* k_means_hpp */
