#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "kinectMesh.h"
#include "ofxCvGrayscaleImage.h"
#include "ofxCvContourFinder.h"
#include "ofxCvColorImage.h"
#include "MyFlock.h"
#include "ofxCvBlobTracker.h"
#include "BlobListener.h"

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();
    

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void scalePoints(ofxCvContourFinder& cf);
    void flockHandler(bool bflock);
    void blobHandler(bool thresh);
    
    ofxKinect               kinect;
    kinectMesh              mesh;
    ofxCvBlobTracker        tracker;
    
    ofTexture *             img;
    
    vector<MyFlock*>        flocks;

    
    
    int                     nearThreshold, 
                            farThreshold, 
                            blobCount;
    
    ofxCvGrayscaleImage     grayImage,
                            grayThreshNear,
                            grayThreshFar;
    
    ofxCvContourFinder      contourFinder;
    
    BlobListener*           listener;
    
    bool                    debug,
                            flocking,
                            cracking,
                            meshing;
		
};
