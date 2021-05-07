//
//  buffer.cpp
//  gencloudme
//
//  Created by Arsenii Klevakin on 12.12.2020.
//

#include "buffer.hpp"

void buffer::shift(point a){
    for(int i=0; i<B.size(); i++){
        B[i].x=B[i].x+a.x;
        B[i].y=B[i].y+a.y;
    }
}

void buffer::homothety(double k){
    for(int i=0; i<B.size(); i++){
        B[i].x=B[i].x*k;
        B[i].y=B[i].y*k;
    }
}
