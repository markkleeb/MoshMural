/*
 *  Boid.cpp
 *  boid
 *
 *  Created by Jeffrey Crouse on 3/29/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 */

#include "Boid.h"
#include <iostream>

Boid::Boid() {
    
    loc.x = -1;
	loc.y = -1;   
    
	acc = 0;
    
    maxspeed = 2;
    maxforce = 0.1;
    vel = 0;
//    r   = 2.5f;
    
    
    
}

Boid::Boid(ofPoint center) {
    
    loc.x = ofRandom(center.x-10, center.x+10);
	loc.y = ofRandom(center.y-10, center.y+10);   
    
	acc = 0;
    
    maxspeed = 2;
    maxforce = 0.1;
    vel = 0;
    //    r   = 2.5f;
    
    
    
}


// Method to update location
void Boid::update() {
    
    
    
    vel += acc;   // Update velocity
    vel.x = ofClamp(vel.x, -maxspeed, maxspeed);  // Limit speed
	vel.y = ofClamp(vel.y, -maxspeed, maxspeed);  // Limit speed
    
    loc += vel;
    
    if(loc.x <= 0 || loc.x >= ofGetWindowWidth()) vel.x *= -1;
    if(loc.y <= 0 || loc.y >= ofGetWindowHeight()) vel.y *= -1;
    
    loc.x = ofClamp(loc.x, 0, ofGetWindowWidth());
    loc.y = ofClamp(loc.y, 0, ofGetWindowHeight());
    
    acc = 0;  // Reset accelertion to 0 each cycle
	
    
}

void Boid::setup(ofPoint cen) {
    loc = cen;
//    cout<<"lx: "<<loc.x<<"ly: "<<loc.y<<"cx: "<<cen.x<<"cy: "<<cen.y<<endl;
    
    
}
void Boid::draw(ofColor color, float magnitude) {
    float r = 2.5f + magnitude;

    float angle = (float)atan2(-vel.y, vel.x);
    float theta =  -1.0*angle;
	float heading2D = ofRadToDeg(theta)+90;

	ofEnableAlphaBlending();
    ofSetColor(color);
    ofFill();
    ofPushMatrix();
        ofTranslate(loc.x, loc.y);
        ofRotateZ(heading2D);
        ofBeginShape();
            ofVertex(0, r);
            ofVertex(2*r/3, -r*1.5);
            ofVertex(-2*r/3, -r*1.5);
        ofEndShape(true);
        ofEllipse(0, -r*1.5, r*1.5, r*2);
    ofPopMatrix();
	ofDisableAlphaBlending();
    
    
//    // Draw the predicted location
//    if (debug) {
//		ofFill();
//        
//		ofSetColor(0,191,255); // BLUE
//		ofLine(loc.x,loc.y,predictLoc.x, predictLoc.y);
//        
//        // PREDICTED LOCATION 
//		ofEllipse(predictLoc.x, predictLoc.y,4,4);
//        
//		
//        // Draw normal location
//		ofSetColor(255, 69, 0); //ORANGE
//        ofEllipse(target.x,target.y,4,4);
//		
//        
//		ofSetColor(255, 20, 147);
//		ofEllipse(target.x+dir.x, target.y+dir.y, 8, 8);
//    }
//    
    
}


ofPoint Boid::vecSteer(ofPoint vec) {
    float mag = sqrt(vec.x*vec.x + vec.y*vec.y);
    if (mag > 0) {
		// Implement Reynolds: Steering = Desired - Velocity
		vec /= mag;
		vec *= maxspeed;
		vec -= vel;
		vec.x = ofClamp(vec.x, -maxforce, maxforce);
		vec.y = ofClamp(vec.y, -maxforce, maxforce);
    }
    return vec;
    
}
ofPoint Boid::steer(ofPoint target, bool slowdown) {
    ofPoint steer;                      // The steering vector
    ofPoint desired = target - loc;     // A vector pointing from the location to the target
    float d = ofDist(target.x, target.y, loc.x, loc.y); // Distance from the target is the magnitude of the vector
    
	// If the distance is greater than 0, calc steering (otherwise return zero vector)
    if (d > 0) {
		
		desired /= d; // Normalize desired
		// Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
		if ((slowdown) && (d < 100.0f)) {
			desired *= maxspeed * (d/100.0f); // This damping is somewhat arbitrary
		} else {
			desired *= maxspeed;
		}
		// Steering = Desired minus Velocity
		steer = desired - vel;
		steer.x = ofClamp(steer.x, -maxforce, maxforce); // Limit to maximum steering force
		steer.y = ofClamp(steer.y, -maxforce, maxforce); 
    }
    return steer;
}

void Boid::accel(ofPoint vec) {
    acc += vec;
}
void Boid::seek(ofPoint target) {
    acc += steer(target, false);
}

void Boid::arrive(ofPoint target) {
    acc += steer(target, true);
}
