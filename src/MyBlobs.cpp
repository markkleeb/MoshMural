//
//  MyBlobs.cpp
//  moshMural
//
//  Created by Ali Sajjadi on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MyBlobs.h"

MyBlobs::MyBlobs(int blobCount, ofxCvBlob & b, int w, int h) {
    scalar = 1.6f;
    
    cen     = b.centroid*ofPoint(scalar, scalar);
    area    = b.area;
    blobID  = blobCount;
    available  = false;
    count   = 50;
    flocking   = true;
    debug      = true;
    cracking   = false;
    
    clr        = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
    
    points     = b.pts;
    for (int i = 0; i < points.size(); i++) {
        points[i].x *= scalar;
        points[i].y *= scalar;
    }
    setup(clr);
    
    

    
}
MyBlobs::~MyBlobs(){}

void MyBlobs::draw() {
    if (debug) {
        stringstream s;
        s << blobID;
        
        ofSetColor(clr);
        ofDrawBitmapString(s.str(), cen);
        
        
        ofSetColor(clr);
        ofNoFill();
        ofBeginShape();
        for (int i = 0 ; i < points.size(); i++) ofVertex(points[i]);
        ofEndShape(true);
        
    }
    if (flocking) {
        cout<<"FID: "<<blobID;
        flock.draw();
        cout<<endl;
    }
}

void MyBlobs::setup(ofColor clr) {
    flock.setup(cen, clr);    
}

void MyBlobs::resizeWindow(int w, int h){

    
}

bool MyBlobs::blobDelete() {
    if (available) count--; 
    else count = 50;
    
    if (count <= 0 ) return true;
    
    return false;
}

void MyBlobs::update(ofPoint centroid, ofxCvBlob & b) {

    cen     = centroid*ofPoint(scalar, scalar);
    points  = b.pts;
    area    = b.area;
    
    for (int i = 0; i < points.size(); i++) {
        points[i].x *= scalar;
        points[i].y *= scalar;
    }

}

void MyBlobs::updateMotion() {
    if (flocking) {
        flock.update(area, cen, points);
    }
}