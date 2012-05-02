//
//  MyBlobs.h
//  moshMural
//
//  Created by Ali Sajjadi on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef moshMural_MyBlobs_cpp
#define moshMural_MyBlobs_cpp
#include "ofPoint.h"
#include "ofPolyline.h"
#include "ofMain.h"
#include "ofxCvBlob.h"
#include "ofTrueTypeFont.h"
#include "MyFlock.h"

class MyBlobs {
    
    MyFlock  *          m_pFlock;
//    MyFlock             m_custflock;
    vector<ofPoint>     points;

    
    
public:
    MyBlobs(int blobCount, ofxCvBlob & b, int w, int h);
    ~MyBlobs();
    void draw();
    void update(ofPoint centroid, ofxCvBlob & b);
    void updateMotion();
    void setup(ofColor c);
    void clear();
    void resizeWindow(int w, int h);    
    void toggleFlocking(bool bFlocking);
    
    bool blobDelete();
    
    ofPoint             cen; 
    
    ofColor             clr;
    int                 blobID,
                        count,
                        originW,
                        originH;
    
    float               area,
                        scalar;
    
    bool                available,
                        cracking,
                        flocking,
                        debug;    
    
};


#endif
