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
#include "fft.h"

#define BUFFER_SIZE 256
#define NUM_WINDOWS 80

class testApp : public ofBaseApp{
    float * left;
    float * right;
    int 	bufferCounter;
    fft		myfft;
    
    int     max, frq;
    int     absMax;
    ofSoundStream stream;
    
    float magnitude[BUFFER_SIZE];
    float phase[BUFFER_SIZE];
    float power[BUFFER_SIZE];
    
    float freq[NUM_WINDOWS][BUFFER_SIZE/2];
    float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];

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
    void audioReceived(float * input, int bufferSize, int nChannels);
    
    void fftUpdate();
    void scalePoints(ofxCvContourFinder& cf, float wScale = 1.6f, float hScale = 1.6f, int vAdjust = 0, int hAdjust = 0);
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
                            meshing,
                            drawImage,
                            volume,
                            frequency,
                            streaming;
		
};
