//
//  kinectMesh.h
//  moshMural
//
//  Created by Ali Sajjadi on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ofxKinect.h"
#include "ofMain.h"

#ifndef moshMural_kinectMesh_cpp
#define moshMural_kinectMesh_cpp

class kinectMesh {
    
public:
    kinectMesh();
    kinectMesh(ofxKinect& k);
    ~kinectMesh();
    void                setup( ofxKinect& k );
    void                update(int lineType = 0);
    void                draw(int magnitute = 0, int frequency = 0);
    
    void                raiseLower();
    void                lowerLower();
    void                raiseUpper();
    void                lowerUpper();
    
    ofxKinect*           kinect;
    
    vector<ofPolyline>  lines;
    
    unsigned short *    img;
    int                 scale, 
                        rows, 
                        cols, 
                        kW, 
                        kH, 
                        kY, 
                        kX, 
                        upl, 
                        lwl,
                        tick;
    
    bool                active;
};


#endif
