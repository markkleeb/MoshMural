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
    ofImage i;
    int counter;
    bool avoidObject;
    
public:
	Boid(ofPoint centroid);
	
	void update(vector<Boid*> boids);
	void draw();
    void seek(ofPoint target);
    void arrive(ofPoint target);
    void flock(vector<Boid*> boids);
    void wander();
	
    ofPoint separate(vector<Boid*> boids);
    ofPoint align(vector<Boid*> boids);
	ofPoint cohesion(vector<Boid*> boids);
    
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
    
    ofPoint getNormalPoint(ofPoint a, ofPoint b, ofPoint c);
    
    bool projected;
    bool debug;
    
   // ofxCvContourFinder contourFinder;
    
    
    vector<ofPoint> p;
    
 
  //  ofPoint overlap(ofxCvBlob b1, ofxCvBlob b2);
    
    ofPoint steer(ofPoint target, bool slowdown);
    
    
    void intersects(ofxCvContourFinder& _cf, vector<Boid*> boids);
};

#endif