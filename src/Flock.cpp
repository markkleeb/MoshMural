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
    
    color = ofColor(ofRandom(20, 255), ofRandom(20,255), ofRandom(20, 255));
  
    
    
}

void Flock::update(myBlob& blob) {
    
    while(boids.size() < 100){
        
        addBoid(blob.cen);
    }
    
	for(int i=0; i<boids.size(); i++) {
		boids[i]->update(boids);
        boids[i]->intersects(blob, boids);
        
	}
}

void Flock::draw(myBlob& blob) {
	
    
    for(int i=0; i<boids.size(); i++) {
		boids[i]->draw(color);
        
        if(boids[i]->debug){
           
                
                ofPushMatrix();
                ofTranslate(blob.cen.x, blob.cen.y);
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