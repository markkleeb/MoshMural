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
#include "ofxCvBlob.h"
#include "ofxCvContourFinder.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"



class Boid {
    
    int objAvoidScalar;
    int counter;
    bool avoidObject;
    
public:
	Boid(ofPoint centroid);
	
	void update(ofPoint cen, vector<ofPoint> points, vector<Boid*> boids);
	void draw(ofColor color);
    void flock(vector<Boid*> boids);
	
    ofPoint separate(vector<Boid*> boids);
    ofPoint align(vector<Boid*> boids);
	ofPoint cohesion(vector<Boid*> boids);
    
    ofPoint steer(ofPoint target, bool slowdown);
    
	ofPoint loc;
	ofPoint vel;
	ofPoint acc;
    
    ofPoint force;
    ofPoint normal;
    ofPoint target;
    ofPoint predictLoc;
    ofPoint dir;
	float r;
	float maxforce;
	float maxspeed;
    float wandertheta;
    float record;
    
    
    bool projected;
    bool debug;
    
    
    vector<ofPoint> p;
    
 
   
    
    
    
};

#endif