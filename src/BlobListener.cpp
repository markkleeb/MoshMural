//
//  BlobListener.cpp
//  moshMural
//
//  Created by Ali Sajjadi on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "BlobListener.h"

BlobListener::BlobListener(){//MyFlock& flock){
    
}

BlobListener::~BlobListener() {

}

void BlobListener::blobOn(int x, int y, int id, const vector<ofPoint>& pts) {// int order) {
    cout<<"blob on "<<endl;
    f.push_back(new MyFlock(id, ofColor(ofRandom(255),ofRandom(255),ofRandom(255)), ofPoint (x, y), pts));
    
}

void BlobListener::blobMoved(int x, int y, int id, const vector<ofPoint>& pts) {// int order) {
    for (int i = 0; i < f.size(); i++) {
        if (f[i]->bID == id) {
            f[i]->update(ofPoint (x, y), pts);
        }
    }
}

void BlobListener::blobOff(int x, int y, int id, const vector<ofPoint>& pts) {// int order) {
    for (int i = 0; i < f.size(); i++) {
        if (f[i]->bID == id) {
            f[i]->~MyFlock();
            f.erase(f.begin()+i);
        }
    }
    cout<<"blob off"<<endl;
}

void BlobListener::draw() {
    for (int i = 0; i < f.size(); i++) {
        if (f[i] != NULL) {
            f[i]->draw();
        }
    }
}

void BlobListener::update() {
    for (int i = 0; i < f.size(); i++) {
        if (f[i] != NULL) {
            f[i]->update();
        }
    }
}
