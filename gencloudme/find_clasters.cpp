//
//  find_clasters.cpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 13.10.2020.
//

#include "find_clasters.hpp"

void find_clasters::new_cluster(){
    claster A;
    A.Num=countClas;
    countClas++;
    clasters.push_back(A);
}


find_clasters::find_clasters(){
    GM = new Graf_Matrix;
    new_cluster();
}


void find_clasters::colorize(){
    for(int i=0; i<countClas; i++){
        for(int j=0; j<clasters[i].points.size(); j++){
            clasters[i].points[j]->color=clasters[i].color;
        }
    }
}

