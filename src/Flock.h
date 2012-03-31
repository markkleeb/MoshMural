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
	Flock();
	void update(ofxCvContourFinder& _cv);
	void draw(ofxCvContourFinder& _cv);
	void addBoid(ofPoint centroid);
	
     
    
	vector<Boid*> boids;
};

#endif