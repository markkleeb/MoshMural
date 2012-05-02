//
//  BlobListener.h
//  moshMural
//
//  Created by Ali Sajjadi on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef moshMural_BlobListener_cpp
#define moshMural_BlobListener_cpp
#include "ofxCvConstants_Track.h"
#include "MyFlock.h"

class BlobListener : public ofxCvBlobListener  {
    vector<MyFlock*> f;
    
public:
    BlobListener();//MyFlock& flock);
    ~BlobListener();
    
    void blobOn( int x, int y, int id, const vector<ofPoint>& pts);//int order );
    void blobMoved( int x, int y, int id, const vector<ofPoint>& pts);// int order );
    void blobOff( int x, int y, int id, const vector<ofPoint>& pts);// int order );
        
    void draw();
    void update();
};

#endif
