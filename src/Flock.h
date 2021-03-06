/*
 *  Flock.h
 *  flock
 *
 *  Created by Jeffrey Crouse on 3/30/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 */

#ifndef FLOCK_H
#define FLOCK_H

#include "ofMain.h"
#include "Boid.h"
#include "ofxOpenCV.h"


class Flock {
public:
	Flock(ofColor fcolor);
	void update(ofPoint cen, vector<ofPoint> pts);
	void draw(ofPoint cen);
	void addBoid(ofPoint centroid);
	
    
    ofColor color;
    
	vector<Boid*> boids;
};

#endif