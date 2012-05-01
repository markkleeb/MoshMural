#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
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
    ofSetFrameRate(5);

}

//--------------------------------------------------------------
void testApp::update(){
    kinect.update();
    
    if (kinect.isFrameNew()) {
        mesh.update();
        blobHandler(true); 
        for (int i = 0; i < blobs.size(); i++) {
            blobs[i].updateMotion();
        }
    }
    
    

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0,0,0);
    mesh.draw();
    for (int i = 0; i < blobs.size(); i++) blobs[i].draw();
    
}

void testApp::exit() {
    
    kinect.close();
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
    
    //scenario 1 - no blobs: make a blob for each CV blob
    
    if(blobs.size() == 0){
        cout<<"Scenario1"<<blobs.size()<<" CV Blobs: "<<contourFinder.blobs.size()<<endl;
        
        for(int i=0; i< contourFinder.blobs.size(); i++){        
            
            blobs.push_back(MyBlobs(blobCount, contourFinder.blobs[i], kinect.width, kinect.height));
            blobCount++;
            
        }
    }
    
    //scenario 2 - we have less blobs than CV blobs
    
    else if(blobs.size() <= contourFinder.blobs.size())
    {
        cout<<"Scenario2"<<blobs.size()<<" CV Blobs: "<<contourFinder.blobs.size()<<endl;
        bool tracked[contourFinder.blobs.size()];
        for (int i = 0; i< contourFinder.blobs.size(); i++) tracked[i] = false;
        for(int i = 0; i<blobs.size(); i++)
        {
            float record = 50000;
            int index = -1;
            for(int j = 0; j < contourFinder.blobs.size(); j++)
            {
                float d = ofDist(contourFinder.blobs[j].centroid.x, contourFinder.blobs[j].centroid.y, blobs[i].cen.x, blobs[i].cen.y);
                if(d < record && !tracked[j])
                {
                    record = d;
                    index = j;
                }
            }
            
            tracked[index] = true;
            blobs[i].update(contourFinder.blobs[index].centroid, contourFinder.blobs[index]);
            
        }
        
        for(int i=0; i < contourFinder.blobs.size(); i++)
        {
            if(!tracked[i])
            {
                blobs.push_back(MyBlobs(blobCount, contourFinder.blobs[i], kinect.width, kinect.height));
                
                blobCount++;
                
            }
            
        }
        
    }
    
    //Scenario 3: more myBlobs than cv blobs
    else{
        cout<<"Scenario3 Blobs: "<<blobs.size()<<" CV Blobs: "<<contourFinder.blobs.size()<<endl;
        for(int i=0; i< blobs.size(); i++)
        {
            blobs[i].available = true;
        }
        
        for(int i=0; i<contourFinder.blobs.size(); i++)
        {
            float record = 500000;
            int index = -1;
            for(int j = 0; j < blobs.size(); j++)
            {
                float d = ofDist(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y, blobs[j].cen.x, blobs[j].cen.y);
                if(d < record && blobs[j].available)
                {
                    record = d;
                    index = j;
                }
            }
            
            blobs[index].available = false;
            blobs[index].update(contourFinder.blobs[i].centroid, contourFinder.blobs[i]);
            
        }
        
    }
    
    for(int i = 0; i < blobs.size(); i++) {
        if(blobs[i].blobDelete()) blobs.erase(blobs.begin() +i);
    }
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
    for (int i = 0; i < blobs.size(); i++) {
        blobs[i].resizeWindow(w, h);
    }
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}