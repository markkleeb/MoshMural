#pragma once

#include "ofMain.h"
#include "Boid.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Flock.h"
#include "myBlob.h"
#include "fft.h"
#include "kinectMesh.h"

#define BUFFER_SIZE 256
#define NUM_WINDOWS 80




class testApp : public ofSimpleApp{
    
    int startX, startY;
    
public:
    void setup();
    void update();
    void draw();
    // void exit();
    
    void kinectImage();
    
    void drawPointCloud();
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void audioReceived 	(float * input, int bufferSize, int nChannels); 
    
    ofxKinect kinect;
    
    
    
    vector<ofxCvBlob> cvBlobs;
    
    vector<Flock*> flocks;
    vector<myBlob*> myBlobs;
    
    
    ofxCvColorImage colorImg;
    
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    
    ofxCvContourFinder contourFinder;
    ofxCvBlob           CvBlob;
    
    kinectMesh* mesh;
    
    bool bThreshWithOpenCV;
    bool bDrawPointCloud;
    bool kinectOn;
    
    ofPoint overlap(ofxCvBlob b1, ofxCvBlob b2);
    
    int nearThreshold;
    int farThreshold;
    
    int blobCount;
    
    float maxMagnitude;
    int angle;
    
    // used for viewing the point cloud
    ofEasyCam easyCam;
    
private:
    void capture();
    bool doCapture;
    int framenum;
    
    float * left;
    float * right;
    int 	bufferCounter;
    fft		myfft;
    
    float magnitude[BUFFER_SIZE];
    float phase[BUFFER_SIZE];
    float power[BUFFER_SIZE];
    
    float freq[NUM_WINDOWS][BUFFER_SIZE/2];
    float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];
};