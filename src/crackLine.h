//
//  crackLine.h
//  MoshMural
//
//  Created by Mark Kleback on 4/25/12.
//  Copyright (c) 2012 Kleebtronics, Inc. All rights reserved.
//

#ifndef MoshMural_crackLine_h
#define MoshMural_crackLine_h

#include "ofMain.h"
#include "myBlob.h"


class crackLine{
public:
    
    crackLine(ofPoint cen);
  
    void update(vector<ofPoint> pts);
    void draw(ofColor color);
    
    vector<ofPoint> path;
    
    bool walking;
    
    ofPoint loc;
    ofPoint vel;
    
    
};


#endif
