#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    k = new kinectMesh();
    k->setup();
    /*
    kinect.setRegistration(true);
    
	kinect.init();
	kinect.open();
    
    vW = 480;
    vH = 360;
    int numOfLines = 200;
    scale = ofGetWindowWidth()/numOfLines;
    video.initGrabber(vW, vH);
    for (int i = 0; i < ofGetWindowWidth(); i += scale) {
        vector<ofPoint> points;
        for (int j = 0; j < ofGetWindowHeight(); j += scale) {
            points.push_back(ofPoint(i, j, 0));
        }
        
        lines.push_back(ofPolyline(points));
        
    }
    rows = lines[0].getVertices().size();
    cols = lines.size();*/
}

//--------------------------------------------------------------
void testApp::update(){
    k->update();
    /*
    video.update();
    kinect.update();
    unsigned short * img = kinect.getRawDepthPixels();
    int kW = kinect.getWidth();
    int kH = kinect.getHeight();
    int kX = kW/cols;
    int kY = kH/rows;
//    int[][] = {{5, 5}, {4, 3};
    short upperLimit = 7000;
    for (int x = 0; x< kW; x += kX) {
        for (int y = 0; y < kH; y += kY) {
            int l = ofClamp(x/kX, 0, cols - 1);
            int p = ofClamp(y/kY, 0, rows - 1);
            int depth = img[x+y*kW];
            if (depth < upperLimit) {
                lines[l][p].z = ofMap(depth, 0, 9757, -50, 500);
            }
        }
    }
   // unsigned char * img = video.getPixels();
   /* if (video.isFrameNew()) {
        for (int y = 0 ; y < vH; y++) {
            for (int x = 0 ; x < vW; x++) {
                int mapX = ofMap(x, 0, vW, 0, ofGetWindowWidth());
                int mapY = ofMap(y, 0, vH, 0, ofGetWindowHeight());
                if (mapX % scale == 0 && mapY % scale == 0) {
                    unsigned char r = img[x*3+y*vW*3];
                    unsigned char g = img[x*3+y*vW*3+1];
                    unsigned char b = img[x*3+y*vW*3+2];
                    unsigned char brightness = (r+b+g)/3;
                    lines[mapX/scale][mapY/scale].z = brightness;//.getVertices();
                    //points[y/scale].x = brightness;
                }
            }
        }
    }
    */
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0,0,0);
    k->draw();
    //video.draw(0,0);
    
/*    ofSetColor(255, 0, 0);
    for (int i = 0; i < lines.size(); i++ ) {
        lines[i].draw();
    }*/
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}