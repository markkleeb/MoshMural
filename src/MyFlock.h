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

#define BOIDCOUNT 600

class MyBlobs;

class MyFlock {
    vector <Boid>       boids;
    vector <ofPoint>    points;
    ofPoint             cen;
    
public:
    MyFlock(int blobID, ofColor clr, ofPoint center, const vector<ofPoint>& pts);
    ~MyFlock();
    
    void setup(ofPoint center, ofColor c);
    void draw();
    void update();
    void update(ofPoint center, const vector<ofPoint>& points);
    bool inside(float x, float y, const vector<ofPoint>& points);
    
    ofPoint calculateBoidMotion(Boid & b);
    ofColor color;
    
    int bID;
    bool    active;
    
};

#endif
