//
//  crack.h
//  MoshMural
//
//  Created by Mark Kleback on 4/25/12.
//  Copyright (c) 2012 Kleebtronics, Inc. All rights reserved.
//

#ifndef MoshMural_crack_h
#define MoshMural_crack_h


#include "ofMain.h"
#include "myBlob.h"
#include "crackLine.h"


class crack{
  
public:
    
    crack(ofColor crackColor);
    
    void update(myBlob* blob);
    void draw(myBlob* blob);
    void addCrack(ofPoint cen);
    
    vector<crackLine*> crackLines;
    
    ofColor color;
    ofPoint location;
    
};

#endif
