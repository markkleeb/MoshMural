//
//  crackLine.cpp
//  MoshMural
//
//  Created by Mark Kleback on 4/25/12.
//  Copyright (c) 2012 Kleebtronics, Inc. All rights reserved.
//

#include "crackLine.h"
#include <iostream>



crackLine::crackLine(ofPoint cen){
    
    loc = cen;
    vel.x = ofRandom(-1,1);
    vel.y = ofRandom(-1,1);
    
    
}

void crackLine::update(vector<ofPoint> pts){
    loc.x += vel.x;
    loc.y += vel.y;
    
    for(int i = 0; i < path.size(); i++){
        
        float d = 0.2;
        ofPoint temppath = path[i];
        
        for(int j=0; j < pts.size(); j++){
        
        if((abs(loc.x-temppath.x) < d && abs(loc.y-temppath.y) <d) || (abs(loc.x-pts[j].x < d && abs(loc.y-pts[j].y) < d))){
         
            walking = false;
        }
            
        }
        
        
    }
    
    path.push_back(loc);
    
    
}

void crackLine::draw(ofColor color){
    
    ofSetLineWidth(1);
    ofSetColor(255);
    ofBeginShape();
    ofNoFill();
    for(int i = 0; i < path.size(); i++){
        ofVertex(path[i].x, path[i].y);
    }
    ofEndShape();
    
    
}