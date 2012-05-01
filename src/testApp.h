#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "kinectMesh.h"
#include "MyBlobs.h"
#include "ofxCvGrayscaleImage.h"
#include "ofxCvContourFinder.h"
#include "ofxCvColorImage.h"
#include "MyFlock.h"

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void blobHandler(bool thresh);

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxKinect               kinect;
    kinectMesh              mesh;
    vector<MyBlobs>         blobs;
    
    
    int             nearThreshold, farThreshold, blobCount;
    
    ofxCvGrayscaleImage grayImage,grayThreshNear,grayThreshFar;
    ofxCvContourFinder contourFinder;
    
    bool                    debug;
		
};
