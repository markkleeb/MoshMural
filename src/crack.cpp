//
//  crack.cpp
//  MoshMural
//
//  Created by Mark Kleback on 4/25/12.
//  Copyright (c) 2012 Kleebtronics, Inc. All rights reserved.
//

#include "crack.h"
#include <iostream>


crack::crack(ofColor crackColor) {
    
    color = crackColor;
    
  
    
}

void crack::update(myBlob* blob) {
    
    while(crackLines.size() < 5){
        
        addCrack(blob->cen);
    }
    
	for(int i=crackLines.size()-1; i>=0; i--) {
        
        if(crackLines[i]->walking){
        
            if(ofRandom(1) < 0.05){
                
                crackLines[i]->vel.x += ofRandom(-1,1);
                crackLines[i]->vel.y += ofRandom(-1,1);
                
                if(ofRandom(1) < 0.5){
                    
                    addCrack(crackLines[i]->loc);
                    
                }
            }
		
            crackLines[i]->update(blob->points);
        }
	}
}

void crack::draw(myBlob* blob) {
    
    ofPushMatrix();
    ofTranslate(blob->cen);
    
    
    for(int i=crackLines.size()-1; i>=0; i--) {
		crackLines[i]->draw(color);
        
        
        
	}
    
    
    ofPopMatrix();
    
    
}
                                       
                                       
                                       
                                       
void crack::addCrack(ofPoint cen) {
    crackLines.push_back( new crackLine(cen) );
}
