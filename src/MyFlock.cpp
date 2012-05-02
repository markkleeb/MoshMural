//
//  MyFlock.cpp
//  moshMural
//
//  Created by Ali Sajjadi on 4/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyFlock.h"

MyFlock::MyFlock() {
    
//    int boidCount = 200;
//    for (int i = 0; i < boidCount; i++) boids.push_back(Boid()); 
//    color = ofColor(255,255,255);
}

MyFlock::~MyFlock() {
    
}

void MyFlock::setup(ofPoint center, ofColor c) {
    color = c;
    
    for (int i = 0; i < boids.size(); i++) boids[i].setup(center);
//    cout<<"fsetup: "<<center.x<<" , "<<center.y<<endl;

}

void MyFlock::draw() {
//    cout<<" B: "<<boids.size();
    for (int i = 0; i < boids.size() ; i++) {
        boids[i].draw(color);

    }
    
}

void MyFlock::update(float area, ofPoint center, vector<ofPoint>& points) {
    
    if ( boids.size() < BOIDCOUNT ) {
        for (int i = 0; i < ofRandom(10); i++) {
            boids.push_back(Boid(center));
        }
    }

    for (int i = 0; i < boids.size(); i++) {
        boids[i].update();
        ofPoint predictLoc = boids[i].loc + boids[i].vel*10;  
        if (inside(predictLoc.x, predictLoc.y, points)) {
            boids[i].maxspeed   = 5;
            boids[i].acc += calculateBoidMotion(boids[i]);
        } else {
            boids[i].maxspeed = 10;
            boids[i].force = center - predictLoc;
            boids[i].acc += boids[i].force.normalize()* 2.5f;
        }
        
    }
}

bool MyFlock::inside(float x, float y, vector<ofPoint> & points){
	int counter = 0;
	int i;
	double xinters;
	ofPoint p1,p2;
    
	int N = points.size();
    
	p1 = points[0];
	for (i=1;i<=N;i++) {
		p2 = points[i % N];
		if (y > MIN(p1.y,p2.y)) {
            if (y <= MAX(p1.y,p2.y)) {
                if (x <= MAX(p1.x,p2.x)) {
                    if (p1.y != p2.y) {
                        xinters = (y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
                        if (p1.x == p2.x || x <= xinters)
                            counter++;
                    }
                }
            }
		}
		p1 = p2;
	}
    
	if (counter % 2 == 0) return false;
	else return true;
}


ofPoint MyFlock::calculateBoidMotion(Boid & b) {
    float desiredseparation = 25.0f;
    float neighbordist = 50.0f;
    ofPoint cohSteer, aliSteer, sepSteer;
    int cCount = 0, aCount = 0, sCount = 0;
	
    // For every boid in the system, check if it's too close
    for (int i = 0 ; i < boids.size(); i++) {
		
		float d = ofDist(b.loc.x, b.loc.y, boids[i].loc.x, boids[i].loc.y);
        
        // Separation
		if ((d > 0) && (d < desiredseparation)) {
			// Calculate vector pointing away from neighbor
			ofPoint diff = b.loc - boids[i].loc;
			diff /= d;			// normalize
			diff /= d;          // Weight by distance
			sepSteer += diff;
			sCount++;           // Keep track of how many
		}
        
        // Alignment
        if ((d > 0) && (d < neighbordist)) {
			aliSteer += boids[i].vel;
			aCount++;
		}
        
        // Cohesion
        if ((d > 0) && (d < neighbordist)) {
			cohSteer += boids[i].loc; // Add location
			cCount++;
		}
    }
    
    // Average -- divide by how many
    if (sCount > 0) {
		sepSteer /= (float)sCount;
    }
    if (aCount > 0) {
		aliSteer /= (float)aCount;
    }
    if (cCount > 0) {
		cohSteer /= (float)cCount;
    }
	
    sepSteer = b.vecSteer(sepSteer);
    aliSteer = b.vecSteer(aliSteer);
    cohSteer = b.steer(cohSteer, false);
    
    sepSteer *= 10.0;
	aliSteer *= 1.0;
	cohSteer *= 1.0;
	
	return sepSteer + aliSteer + cohSteer;

}
