//
//  MyFlock.cpp
//  moshMural
//
//  Created by Ali Sajjadi on 4/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyFlock.h"

MyFlock::MyFlock(int blobID, ofColor clr, ofPoint center, const vector<ofPoint>& pts) {
    points  = pts;
    bID     = blobID;
    color   = clr;
    active  = true;
    cen     = center;
    
}

MyFlock::~MyFlock() {
    
}

void MyFlock::setup(ofPoint center, ofColor c) {
    color = c;
    
    for (int i = 0; i < boids.size(); i++) boids[i].setup(center);
    //    cout<<"fsetup: "<<center.x<<" , "<<center.y<<endl;
    
}

void MyFlock::draw(int magnitude, int frequency) {
    ofEnableSmoothing();
    ofSetLineWidth(10);
    ofSetColor(color);
    ofNoFill();
    ofBeginShape();
    
    for(int i = 0; i < points.size(); i++)
    {
        ofVertex(points[i].x, points[i].y);
    }
    
    ofEndShape();
    
    //    cout<<" B: "<<boids.size();
    float mag = ofMap(magnitude, 0, 100, 0, 10.0f);
    for (int i = 0; i < boids.size() ; i++) {
        if (magnitude != 0) boids[i].draw(color, mag);
        else boids[i].draw(color);
        
    }
}

void MyFlock::update() {
    if ( boids.size() < BOIDCOUNT ) {
        for (int i = 0; i < ofRandom(10); i++) {
            boids.push_back(Boid(cen));
        }
    }
    //    cout << "FID:" << bID << " pts:"<< points.size() << endl;
    for (int i = 0; i < boids.size(); i++) {
        boids[i].update();
        ofPoint predictLoc = boids[i].loc + boids[i].vel*10;  
        if (inside(predictLoc.x, predictLoc.y, points)) {
            boids[i].maxspeed   = 5;
            boids[i].acc += calculateBoidMotion(boids[i]);
        } else {
            boids[i].maxspeed = 10;
            boids[i].force = cen - predictLoc;
            boids[i].acc += boids[i].force.normalize()* 2.5f;
        }
        
    }
    
}


void MyFlock::update(ofPoint center, const vector<ofPoint>& pts) {
    
    
    points.clear();
    points  = pts;
    cen     = center;
    update();
    
}

bool MyFlock::inside(float x, float y, const vector<ofPoint> & points){
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