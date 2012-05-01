/*
 *  Flock.cpp
 *  flock
 *
 *  Created by Jeffrey Crouse on 3/30/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 */

#include "Flock.h"
#include <iostream>

Flock::Flock(ofColor fcolor) {
    
    color = fcolor;
  
}

void Flock::update(ofPoint cen, vector<ofPoint> pts) {
    
    while(boids.size() < 600){
        
        addBoid(cen);
    }
    
	for(int i=0; i<boids.size(); i++) {
		boids[i]->update(cen, pts, boids);
                
	}
}

void Flock::draw(ofPoint cen) {
    
    
	
    
    for(int i=0; i<boids.size(); i++) {
		boids[i]->draw(color);
        
        if(boids[i]->debug){
           
                
                ofPushMatrix();
                ofTranslate(cen.x, cen.y);
                ofSetColor(0, 255, 0);
                ofEllipse(0, 0, 10, 10);
                ofPopMatrix();
        }
	}
}

void Flock::addBoid(ofPoint centroid) {
	boids.push_back( new Boid(centroid) );
}