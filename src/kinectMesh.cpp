//
//  kinectMesh.cpp
//  moshMural
//
//  Created by Ali Sajjadi on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "kinectMesh.h"
#include "Math.h"

kinectMesh::kinectMesh() {
}

kinectMesh::kinectMesh(ofxKinect& k) {
    kinect = &k;
    int numOfLines = 100;

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
    active = false;
    tick = 0;
    upl = 9757;
}

kinectMesh::~kinectMesh() {
}

void kinectMesh::setup( ofxKinect& k ) {    

}

void kinectMesh::draw(int magnitude, int frequency) {
    ofEnableSmoothing();
    if (magnitude == 0) {
        ofSetColor(255, 0, 0);
        ofSetLineWidth(1);
    } else {
        float frqMod = frequency * 20 / 255;
        int b = 0, g = 0;
        if (frqMod > 1) {
            b = (int) ((frqMod-1) * 255) % 255;
            g = 255;
        } else {
            b = 0;
            g = (int) frqMod * 255;
        }
        ofSetColor(255, g, b);
        ofSetLineWidth(ofMap(magnitude, 0, 150, 0, 5));
    }
    for (int i = 0; i < lines.size(); i++ ) {
//        lines[i].draw();
        ofBeginShape();
        vector<ofPoint> verts = lines[i].getVertices();
        
        for (int j=0; j<verts.size(); j++) {
            ofVertex(verts[j].x-ofMap(verts[j].z,0,500,0,30), verts[j].y);
        }
        for (int j=verts.size()-1; j>=0; j--) {
            ofVertex(verts[j].x+ofMap(verts[j].z,0,500,0,30), verts[j].y);
        } 
        
        ofEndShape();
    }
    ofDisableSmoothing();
    tick++;
}

void kinectMesh::update(int lineType) {
    img = kinect->getRawDepthPixels();

    for (int x = 0; x < kW; x += kX) {
        for (int y = 0; y < kH; y += kY) {
            int l = ofClamp(x/kX, 0, cols - 1);
            int p = ofClamp(y/kY, 0, rows - 1);
            int depth = img[x+y*kW];
            if (depth <= upl && depth >= lwl) {
                lines[l][p].z = ofMap(depth, 0, 9757, 0, 500);
            } else {
                lines[l][p].z = 0;
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