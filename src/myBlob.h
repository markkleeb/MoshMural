//
//  myBlob.h
//  MoshMural
//
//  Created by Mark Kleback on 4/13/12.
//  Copyright (c) 2012 Kleebtronics, Inc. All rights reserved.
//

#ifndef MoshMural_myBlob_h
#define MoshMural_myBlob_h
#include "ofMain.h"
#include "ofxOpenCv.h"

class myBlob
{
public:
    myBlob(ofPoint c, vector<ofPoint> pts);
    
    void update(ofxCvBlob _cv);
    void draw();
    void countDown();
    
    bool processPoint(ofPoint centroid);
    
    bool available;
    bool blobDelete;
    bool dead();
    
    ofPoint cen;
    
    vector<ofPoint> points;
   
    
    int timer;
    int blobCount;
    int blobId;
    
};


#endif
