//
//  myBlob.cpp
//  MoshMural
//
//  Created by Mark Kleback on 4/13/12.
//  Copyright (c) 2012 Kleebtronics, Inc. All rights reserved.
//

#include <iostream>
#include "myBlob.h"


myBlob::myBlob(ofPoint c, vector<ofPoint> pts, int blobNo)
{
    cen = c;
    points = pts;
    
    flockcolor = ofColor(ofRandom(100, 255), ofRandom(100,255), ofRandom(100, 255));
    
    available = true;
    blobDelete = false;
    blobId = blobNo;
    
    timer = 200;
    
    

    myFlock = new Flock(flockcolor);
    
    
}

void myBlob::update(ofxCvBlob _cv)
{

    cen = _cv.centroid;
    points = _cv.pts;    
    
 
    myFlock->update(cen, points);
    

}

void myBlob::draw()
{
    ofEnableSmoothing();
    ofSetLineWidth(10);
    ofSetColor(flockcolor);
    ofNoFill();
    ofBeginShape();
    
    for(int i = 0; i < points.size(); i++)
    {
        ofVertex(points[i].x, points[i].y);
    }
    
    ofEndShape();

    myFlock->draw(cen);

}



void myBlob::countDown()
{
    timer--;
    
}

bool myBlob::dead()
{
    if(timer < 0) return true;
    return false;
    
}