#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    listener    = new BlobListener();
    img         = NULL;
    kinect.setRegistration(true);
    
	kinect.init();
	kinect.open();

    mesh = kinectMesh(kinect);

    nearThreshold           = 230;
    farThreshold            = 90;
    blobCount               = 0;
    
    grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
    ofSetFrameRate(60);
    
    meshing     = false;
    cracking    = false;
    flocking    = false;
    
    tracker.setListener(listener);

}

//--------------------------------------------------------------
void testApp::update(){
    kinect.update();
    
    if (kinect.isFrameNew()) {
        mesh.update();
        blobHandler(true);
        img = &kinect.getTextureReference();
    }
//    flockHandler(flocking);
    listener->update();

}

//--------------------------------------------------------------
void testApp::draw(){
    
    if (img != NULL) img->draw(0, 0);
    ofBackground(0,0,0);
    mesh.draw();
    tracker.draw(0,0);
    listener->draw();
    
    
}

void testApp::exit() {
    
    kinect.close();
}

void testApp::flockHandler(bool bflock) {
    if (!bflock) {
        for (int i=0; i<flocks.size(); i++) {
            flocks[i]->~MyFlock();
            flocks.erase(flocks.begin()+i);
        }
        return;
    } else {
        int blobSize = tracker.blobs.size();
        int flockSize = flocks.size();
        for (int i = 0; i< tracker.blobs.size(); i++) {
            
        }
    }return;
    
    
}

void testApp::blobHandler(bool bThreshWithOpenCV = false) {
    grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
    
    
    if(bThreshWithOpenCV) {
        grayThreshNear = grayImage;
        grayThreshFar = grayImage;
        grayThreshNear.threshold(nearThreshold, true);
        grayThreshFar.threshold(farThreshold);
        cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
    } else {
        unsigned char * pix = grayImage.getPixels();
        
        int numPixels = grayImage.getWidth() * grayImage.getHeight();
        for(int i = 0; i < numPixels; i++) {
            if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                pix[i] = 255;
            } else {
                pix[i] = 0;
            }
        }
    }
    
    grayImage.flagImageChanged();
    

    contourFinder.findContours(grayImage, 100, (kinect.width*kinect.height)/2, 20, false);
    scalePoints(contourFinder);
    tracker.trackBlobs( contourFinder.blobs );
    
    
}

void testApp::scalePoints(ofxCvContourFinder& cf) {
    float wScale = 1.6f;
    float hScale = 1.6f;
    for (int i = 0; i < cf.blobs.size(); i++) {
        for (int j = 0; j < cf.blobs[i].pts.size(); j++) {
            cf.blobs[i].pts[j].x *= wScale;
            cf.blobs[i].pts[j].y *= hScale;
        }
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'f') {
        flocking = !flocking;
        flockHandler(flocking);
    } else if (key == 'c') {
        cracking = !cracking;
    } else if (key == 'm') {
        meshing = !meshing;
    } else if (key == '-') {
        nearThreshold --;
    } else if (key == '=') {
        nearThreshold ++;
    } else if (key == '[') {
        farThreshold --;
    } else if (key == ']') {
        farThreshold ++;
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
//    for (int i = 0; i < blobs.size(); i++) {
//        blobs[i].resizeWindow(w, h);
//    }
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}