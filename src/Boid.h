/*
 *  Boid.h
 *  boid
 *
 *  Created by Jeffrey Crouse on 3/29/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 */

#ifndef BOID_H
#define BOID_H

#include "ofMain.h"
#include <list>
#include "ofPolyline.h"

class MyBlobs;



class Boid {

public:
	Boid();
	Boid(ofPoint center);

	
	void update();
	void draw(ofColor color);
    void seek(ofPoint target);
    void arrive(ofPoint target);
    void accel(ofPoint vec);
    void setup(ofPoint cen);
	    
	ofPoint loc;
	ofPoint vel;
	ofPoint acc;
    
    ofPoint force;
    ofPoint normal;
    ofPoint target;
    ofPoint predictLoc;
    ofPoint dir;//dep
//	float r;
	float maxforce;
	float maxspeed;

    ofPoint vecSteer(ofPoint vec);
    ofPoint steer(ofPoint target, bool slowdown);
    
    
};

#endif