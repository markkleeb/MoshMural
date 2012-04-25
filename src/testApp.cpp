#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    /*
     //soundstream stuff
     
     
     srand((unsigned int)time((time_t *)NULL));
     
     // 0 output channels, 
     // 2 input channels
     // 44100 samples per second
     // BUFFER_SIZE samples per buffer
     // 4 num buffers (latency)
     
     ofSoundStreamSetup(0,2,this, 44100,BUFFER_SIZE, 4);	
     left = new float[BUFFER_SIZE];
     right = new float[BUFFER_SIZE];
     
     for (int i = 0; i < NUM_WINDOWS; i++)
     {
     for (int j = 0; j < BUFFER_SIZE/2; j++)
     {
     freq[i][j] = 0;	
     }
     }
     
     //end FFT stuff
     */
    
    
    mesh = new kinectMesh(kinect);    
    blobCount = 0;
    startX = 1100;
    startY = 650;
    ofSetFrameRate(60);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
	// enable depth->video image calibration
	kinect.setRegistration(true);
    
	kinect.init();
	//kinect.init(true); // shows infrared instead of RGB video image
	//kinect.init(false, false); // disable video image (faster fps)
	kinect.open();
    
#ifdef USE_TWO_KINECTS
	kinect2.init();
	kinect2.open();
#endif
    
	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
    
	nearThreshold = 230;
	farThreshold = 90;
	bThreshWithOpenCV = true;
    
    
    
	// zero the tilt on startup
	angle = 0;
	kinect.setCameraTiltAngle(angle);
    
	// start from the front
	bDrawPointCloud = false;
    
    
    
	framenum=0;
	doCapture=false;
    
    //ofSoundStreamSetup(0, 1, this, 44100, 256, 4);
    
    
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    
    
    ofBackground(0, 0, 0);
    
    
    
    mesh->update();
    
    if(!mesh->active){
        
        
        kinect.update();
        
        
        // there is a new frame and we are connected
        if(kinect.isFrameNew()) {
            
            // load grayscale depth image from the kinect source
            grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
            
            // we do two thresholds - one for the far plane and one for the near plane
            // we then do a cvAnd to get the pixels which are a union of the two thresholds
            if(bThreshWithOpenCV) {
                grayThreshNear = grayImage;
                grayThreshFar = grayImage;
                grayThreshNear.threshold(nearThreshold, true);
                grayThreshFar.threshold(farThreshold);
                cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
            } else {
                
                // or we do it ourselves - show people how they can work with the pixels
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
            
            // update the cv images
            grayImage.flagImageChanged();
            
            // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
            // also, find holes is set to true so we will get interior contours as well....
            contourFinder.findContours(grayImage, 100, (kinect.width*kinect.height)/2, 20, false);
            
            
            
        }
        
        
        
        
        //scenario 1 - no blobs: make a blob for each CV blob
        
        if(myBlobs.size() == 0){
            
            for(int i=0; i< contourFinder.blobs.size(); i++){        
                
                myBlobs.push_back(new myBlob(contourFinder.blobs[i].centroid, contourFinder.blobs[i].pts, blobCount));
                blobCount++;
                
            }
        }
        
        //scenario 2 - we have less blobs than CV blobs
        
        else if(myBlobs.size() <= contourFinder.blobs.size())
        {
            vector<bool> used;
            for(int i = 0; i < contourFinder.blobs.size(); i++)
            {
                bool n;
                used.push_back(n);
            }
            
            for(int i = 0; i<myBlobs.size(); i++)
            {
                float record = 50000;
                int index = -1;
                for(int j = 0; j < contourFinder.blobs.size(); j++)
                {
                    float d = ofDist(contourFinder.blobs[j].centroid.x, contourFinder.blobs[j].centroid.y, myBlobs[i]->cen.x, myBlobs[i]->cen.y);
                    if(d < record && !used[j])
                    {
                        record = d;
                        index = j;
                    }
                }
                
                used[index] = true;
                myBlobs[i]->update(contourFinder.blobs[index]);
                
            }
            
            for(int i=0; i < contourFinder.blobs.size(); i++)
            {
                if(!used[i])
                {
                    myBlobs.push_back(new myBlob(contourFinder.blobs[i].centroid, contourFinder.blobs[i].pts, blobCount));
                    
                    blobCount++;
                    
                }
                
            }
            
        }
        
        //Scenario 3: more myBlobs than cv blobs
        else{
            
            
            for(int i=0; i< myBlobs.size(); i++)
            {
                myBlobs[i]->available = true;
            }
            
            for(int i=0; i<contourFinder.blobs.size(); i++)
            {
                float record = 500000;
                int index = -1;
                for(int j = 0; j < myBlobs.size(); j++)
                {
                    float d = ofDist(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y, myBlobs[j]->cen.x, myBlobs[j]->cen.y);
                    if(d < record && myBlobs[j]->available)
                    {
                        record = d;
                        index = j;
                    }
                }
                
                
                myBlobs[index]->available = false;
                myBlobs[index]->update(contourFinder.blobs[i]);
                
            }
            
            for(int i = 0; i < myBlobs.size(); i++)
            {
                if(myBlobs[i]->available)
                {
                    myBlobs[i]->countDown();
                    if(myBlobs[i]->dead()){
                        myBlobs[i]->blobDelete = true;
                    }
                }
            }
        }
        
        //Delete any that should be deleted
        for(int i = myBlobs.size()-1; i >=0; i--)
        {
            if(myBlobs[i]->blobDelete)
            {
                myBlobs.erase(myBlobs.begin() +i);
                flocks.erase(flocks.begin() +i);
            }
            
            
        }
        
        
        
        
        
        
        for(int i=0; i < myBlobs.size(); i++){
            
            flocks.push_back(new Flock(myBlobs[i]->flockcolor));
            
            flocks[i]->update(myBlobs[i]);
            cracks[i]->update(myBlobs[i]);
        }
        
        
        
    }
    
}



//--------------------------------------------------------------
void testApp::draw(){
    
    
    /* 
     
     //FFT stuff
     maxMagnitude = 0;
     
     int max = 0;
     int f = -1;
     static int index=0;
     float avg_power = 0.0f;	
     
     if(index < 80)
     index += 1;
     else
     index = 0;
     
     
     
     do the FFT
     myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, left,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
     
     // start from 1 because mag[0] = DC component 
     // and discard the upper half of the buffer 
     for(int j=1; j < BUFFER_SIZE/2; j++) {
     freq[index][j] = magnitude[j];		
     if (magnitude[j] > max ) {
     max = magnitude[j];
     f = j;
     maxMagnitude = magnitude[f];
     
     
     //   cout << "mm: " << maxMagnitude << endl;
     
     }
     }
     */
    
    if(mesh->active){
    
    
    mesh->draw();    
    }
    
    else if(cracking){
        
        for(int i = 0; i < myBlobs.size(); i++){
            myBlobs[i]->draw();
            cracks[i]->draw(myBlobs[i]);
        }
        
        
    }
    
    else{
        
        kinectImage(); 
        
        
        
        
        ofSetColor(255, 255, 255);
        
        
        
        
        
        
        for(int i = 0; i < myBlobs.size(); i ++){
            
            myBlobs[i]->draw();
            
            flocks[i]->draw(myBlobs[i], maxMagnitude);
            
        }
        
        
    }
    
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
		case ' ':
			bThreshWithOpenCV = !bThreshWithOpenCV;
            
            mesh->active = !mesh->active;
            
            
            break;
            
        case 'b':
            
            
            cracking = !cracking;
            
            break;
            
            
		case'p':
            if (kinectOn) {
                kinectOn = false;
                for(int j=0; j < flocks.size(); j++){
                    for(int i = 0; i < flocks[j]->boids.size(); i++)
                    {
                        flocks[j]->boids[i]->debug = false;
                    }
                }
            } else {
                kinectOn = true;
                for(int j = 0; j < flocks.size(); j++){
                    
                    for(int i = 0; i < flocks[j]->boids.size(); i++)
                    {
                        //  flocks[j].boids[i]->debug = true;
                    }
                }
            }
			break;
            
		case '>':
		case '.':
			farThreshold ++;
            cout<<"Threshold: "<<farThreshold<<"\n";
			if (farThreshold > 255) farThreshold = 255;
			break;
            
		case '<':
		case ',':
			farThreshold --;
            
            cout<<"Threshold: "<<farThreshold<<"\n";
			if (farThreshold < 0) farThreshold = 0;
			break;
            
		case '+':
		case '=':
			nearThreshold ++;
			if (nearThreshold > 255) nearThreshold = 255;
			break;
            
		case '-':
			nearThreshold --;
			if (nearThreshold < 0) nearThreshold = 0;
			break;
            
		case 'w':
			kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
			break;
            
		case 'o':
			kinect.setCameraTiltAngle(angle); // go back to prev tilt
			kinect.open();
			break;
            
		case 'c':
			kinect.setCameraTiltAngle(0); // zero the tilt
			kinect.close();
			break;
            
        case 'n':
            // f.boids.push_back(Boid*);
            break;
            
		case OF_KEY_UP:
			angle++;
			if(angle>30) angle=30;
			kinect.setCameraTiltAngle(angle);
			break;
            
		case OF_KEY_DOWN:
			angle--;
			if(angle<-30) angle=-30;
			kinect.setCameraTiltAngle(angle);
			break;
            
        case 'd':
            for(int j = 0; j < flocks.size(); j++){
                for(int i = 0; i < flocks[j]->boids.size(); i++)
                {
                    flocks[j]->boids[i]->debug = false;
                }
            }
			break;
            
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
    
    ofSetColor(255, 0, 0);
    ofCircle(mouseX, mouseY, 20);
    
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

//--------------------------------------------------------------
void testApp::capture() {
	if(doCapture && ofGetFrameNum() % 4 == 0)
	{
		char filename[255];
		sprintf(filename, "frame%05d.png", framenum++);
		ofSaveScreen(filename);
	}
}


void testApp::drawPointCloud() {
	int w = 640;
	int h = 480;
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_POINTS);
	int step = 2;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			if(kinect.getDistanceAt(x, y) > 0) {
				mesh.addColor(kinect.getColorAt(x,y));
				mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
			}
		}
	}
	glPointSize(3);
	ofPushMatrix();
	// the projected points are 'upside down' and 'backwards' 
	ofScale(1, -1, -1);
	ofTranslate(0, 0, -1000); // center the points a bit
	glEnable(GL_DEPTH_TEST);
	mesh.drawVertices();
	glDisable(GL_DEPTH_TEST);
	ofPopMatrix();
}

void testApp::kinectImage(){
    
    
    if(kinectOn) {
        //grayImage.draw(0, 0, 1280, 768);
        //contourFinder.draw(-700, 0, 2400, 1180);
        contourFinder.draw(0,0);    
        /* 
         // draw instructions
         ofSetColor(255, 255, 255);
         stringstream reportStream;
         reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
         << ofToString(kinect.getMksAccel().y, 2) << " / "
         << ofToString(kinect.getMksAccel().z, 2) << endl
         << "press p to switch between images and point cloud, rotate the point cloud with the mouse" << endl
         << "using opencv threshold = " << bThreshWithOpenCV <<" (press spacebar)" << endl
         << "set near threshold " << nearThreshold << " (press: + -)" << endl
         << "set far threshold " << farThreshold << " (press: < >) num blobs found " << contourFinder.nBlobs
         << ", fps: " << ofGetFrameRate() << endl
         << "press c to close the connection and o to open it again, connection is: " << kinect.isConnected() << endl
         << "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl;
         
         ofDrawBitmapString(reportStream.str(),20,750);
         */
        
    }
    
}

void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){	
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
	bufferCounter++;
}



