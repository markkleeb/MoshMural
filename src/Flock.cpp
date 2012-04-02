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

Flock::Flock() {
    
  
    
    
}

void Flock::update(ofxCvBlob& _cv) {
    
    while(boids.size() < 500){
        
        addBoid(_cv.centroid);
    }
    
	for(int i=0; i<boids.size(); i++) {
		boids[i]->update(boids);
        boids[i]->intersects(_cv, boids);
        
	}
}

void Flock::draw(ofxCvBlob& _cv) {
	
    
    for(int i=0; i<boids.size(); i++) {
		boids[i]->draw();
        
        if(boids[i]->debug){
           
                
                ofPushMatrix();
                ofTranslate(_cv.centroid.x, _cv.centroid.y);
                ofSetColor(0, 255, 0);
                ofEllipse(0, 0, 10, 10);
                ofPopMatrix();
                
                
            
            
        }
        

	}
    
   /* 
    if(ofGetFrameNum()%30 == 1){
        Boid* b;
		boids.push_back(b);
        
    }
    */

    
    
}

void Flock::addBoid(ofPoint centroid) {
	boids.push_back( new Boid(centroid) );
}