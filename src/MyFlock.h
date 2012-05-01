//
//  MyFlock.h
//  moshMural
//
//  Created by Ali Sajjadi on 4/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef moshMural_MyFlock_cpp
#define moshMural_MyFlock_cpp
#include "Boid.h"

#define BOIDCOUNT 200

class MyBlobs;

class MyFlock {
    vector <Boid>       boids;
    
public:
    MyFlock();
    ~MyFlock();
    
    void setup(ofPoint center, ofColor c);
    void draw();
    void update(float area, ofPoint center, vector<ofPoint>& points);
    bool inside(float x, float y, vector<ofPoint>& points);
    
    ofPoint calculateBoidMotion(Boid & b);
    ofColor color;
    
};

#endif
