//
//  kinectMesh.cpp
//  moshMural
//
//  Created by Ali Sajjadi on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "kinectMesh.h"

kinectMesh::kinectMesh(ofxKinect &kinect2) {
    
    kinect = &kinect2;
    init();
    

}
kinectMesh::kinectMesh() {
    
    kinect = new ofxKinect();
    init();
    
}

kinectMesh::~kinectMesh() {
    kinect->close();
    delete kinect;

}

void kinectMesh::init() {
    active = false;
    
    int numOfLines = 200;
    
    scale = ofGetWindowWidth()/numOfLines;
    
    for (int i = 0; i < ofGetWindowWidth(); i += scale) {
        vector<ofPoint> points;
        for (int j = 0; j < ofGetWindowHeight(); j += scale) {
            points.push_back(ofPoint(i, j, 0));
        }
        
        lines.push_back(ofPolyline(points));
        
    }
    rows = lines[0].getVertices().size();
    cols = lines.size();
    
    kW = kinect->getWidth();
    kH = kinect->getHeight();
    kX = kW/cols;
    kY = kH/rows;
    
    lwl = 0;
    active = true;
    tick = 0;
    upl = 9757;
    
}

void kinectMesh::setup() {
    kinect->setRegistration(true);
	kinect->init();
	kinect->open();
    
}

void kinectMesh::draw() {
    if (active) {
        ofSetColor(255, 0, 0);
        for (int i = 0; i < lines.size(); i++ ) {
            lines[i].draw();
        }
        tick++;
    }
}

void kinectMesh::update() {
    if (active) {
        kinect->update();
    
        img = kinect->getRawDepthPixels();
    
        for (int x = 0; x < kW; x += kX) {
            for (int y = 0; y < kH; y += kY) {
                int l = ofClamp(x/kX, 0, cols - 1);
                int p = ofClamp(y/kY, 0, rows - 1);
                int depth = img[x+y*kW];
                if (depth < upl && depth > lwl) {
                    lines[l][p].z = ofMap(depth, 0, 9757, -50, 500);
                } else {
                    lines[l][p].z = -50;
                }
            }
        }
    }
}

void kinectMesh::raiseLower() {
    lwl += 10;
}

void kinectMesh::lowerLower() {
    lwl -= 10;
}

void kinectMesh::raiseUpper() {
    upl += 10;
}

void kinectMesh::lowerUpper() {
    upl -= 10;
}