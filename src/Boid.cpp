/*
 *  Boid.cpp
 *  boid
 *
 *  Created by Jeffrey Crouse on 3/29/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 */

#include "Boid.h"


Boid::Boid(ofPoint centroid) {

    loc.x = ofRandom(centroid.x-10, centroid.x+10);
	loc.y = ofRandom(centroid.y-10, centroid.y+10);   
    
	acc = 0;
	
    r = 2.0;
    maxspeed = 2;
    maxforce = 0.1;
    vel = 0;//ofPoint(-maxspeed, 0);
    wandertheta = 0.0;
   // objAvoidScalar = 10;
    debug = false;
    
 //   i.loadImage("airplane.png");
 //   i.resize(25,30);
    
    counter = 0;
    avoidObject = false;
    
}


// Method to update location
void Boid::update(vector<Boid*> boids) {
    
    
  
    vel += acc;   // Update velocity
    vel.x = ofClamp(vel.x, -maxspeed, maxspeed);  // Limit speed
	vel.y = ofClamp(vel.y, -maxspeed, maxspeed);  // Limit speed
   
    loc += vel;
    
    loc.x = ofClamp(loc.x, 0, ofGetWindowWidth());
    loc.y = ofClamp(loc.y, 0, ofGetWindowHeight());
    
    acc = 0;  // Reset accelertion to 0 each cycle
	

}

void Boid::flock(vector<Boid*> boids){
    
    ofPoint sep = separate(boids);
	ofPoint ali = align(boids);
	ofPoint coh = cohesion(boids);
	
	// Arbitrarily weight these forces
	sep *= 10.0;
	ali *= 1.0;
	coh *= 1.0;
	
	acc += sep + ali + coh;
}

void Boid::draw(ofColor color) {
    
    // Draw a triangle rotated in the direction of velocity
        
   if(loc.x == 0 || loc.x == ofGetWindowWidth()) vel.x *= -1;
    if(loc.y == 0 || loc.y == ofGetWindowHeight()) vel.y *= -1;


	
	float angle = (float)atan2(-vel.y, vel.x);
    float theta =  -1.0*angle;
	float heading2D = ofRadToDeg(theta)+90;
	
	ofEnableAlphaBlending();
    ofSetColor(color);
    ofFill();
    ofPushMatrix();
    ofTranslate(loc.x, loc.y);
    ofRotateZ(heading2D);
//	ofBeginShape();
//    ofVertex(0, -r*2);
//    ofVertex(-r, r*2);
//    ofVertex(r, r*2);
//    ofEndShape(true);
//    i.setAnchorPoint(10, 12);
//    i.draw(0,0);
    ofSetColor(color);
    ofEllipse(0, 0, r, r);
    ofPopMatrix();
	ofDisableAlphaBlending();
    
    
    // Draw the predicted location
    if (debug) {
		ofFill();
		ofSetColor(0,191,255); // BLUE
		ofLine(loc.x,loc.y,predictLoc.x, predictLoc.y);
        // PREDICTED LOCATION 
		ofEllipse(predictLoc.x, predictLoc.y,4,4);
        
    }
	
	// Draw the debugging stuff
    if (debug) {
		// Draw normal location
		ofSetColor(255, 69, 0); //ORANGE
		//ofLine(predictLoc.x, predictLoc.y, acc.x, acc.y);
		ofEllipse(target.x,target.y,4,4);
		
		// Draw actual target (red if steering towards it)
		//ofLine(predictLoc.x,predictLoc.y,target.x,target.y);
		
		//if (record > p->radius) 
		//	ofSetColor(255,0,0);
        // VIOLET CIRCLE IS TARGET + DIR
		ofSetColor(255, 20, 147);
		ofEllipse(target.x+dir.x, target.y+dir.y, 8, 8);
    }

    
}

void Boid::intersects(myBlob& blob, vector<Boid*> boids){
    
  
    predictLoc = loc + vel*10;  // A vector pointing from the location to where the boid is heading
    
    
        //myBlob temp = blob;
        ofPolyline l;
        l.addVertexes(blob.points);
        
        if(l.inside(predictLoc))
        {   
           
            
            r = 2.5;
            maxspeed = 5;
            flock(boids);
                       
        } else {
            
            r = 8;
            maxspeed = 10;
         
            force =  blob.cen - predictLoc;
            acc += force.normalize()* 2.5;
            //cout << "bounce!\n";

            
        }
        
        
        
    
  

        
}

           
ofPoint Boid::getNormalPoint(ofPoint p, ofPoint a, ofPoint b) {
	
    // Vector from a to p
    ofPoint ap = p - a;
	
    // Vector from a to b
    ofPoint ab = b - a;
	
//	Path::normalize(&ab); // Normalize the line
	
    // Project vector "diff" onto line by using the dot product
//    ab *= dotproduct(ab, ap);
	
    return a + ab;
}

void Boid::wander() {
    float wanderR = 16.0f;         // Radius for our "wander circle"
    float wanderD = 50.0f;         // Distance for our "wander circle"
    float change = 0.3f;//0.25f;
    wandertheta += ofRandom(-change, change); // Randomly change wander theta
    
    // Now we have to calculate the new location to steer towards on the wander circle
    ofPoint circleloc;
    circleloc.set(vel.x, vel.y);  // Start with velocity
    circleloc.normalize();            // Normalize to get heading
    circleloc *= wanderD;          // Multiply by distance
    circleloc += loc;               // Make it relative to boid's location
    
    ofPoint circleOffSet;
    circleOffSet.set(wanderR*cos(wandertheta),wanderR*sin(wandertheta));
    ofPoint target = circleloc + circleOffSet;
    
    acc += steer(target,false);  // Steer towards it
    
} 


ofPoint Boid::steer(ofPoint target, bool slowdown) {
    ofPoint steer;  // The steering vector
    ofPoint desired = target - loc;  // A vector pointing from the location to the target
    float d = ofDist(target.x, target.y, loc.x, loc.y); // Distance from the target is the magnitude of the vector
    
	// If the distance is greater than 0, calc steering (otherwise return zero vector)
    if (d > 0) {
		
		desired /= d; // Normalize desired
		// Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
		if ((slowdown) && (d < 100.0f)) {
			desired *= maxspeed * (d/100.0f); // This damping is somewhat arbitrary
		} else {
			desired *= maxspeed;
		}
		// Steering = Desired minus Velocity
		steer = desired - vel;
		steer.x = ofClamp(steer.x, -maxforce, maxforce); // Limit to maximum steering force
		steer.y = ofClamp(steer.y, -maxforce, maxforce); 
    }
    return steer;
}


void Boid::seek(ofPoint target) {
    acc += steer(target, false);
//    cout << "SEEK\n";
}

void Boid::arrive(ofPoint target) {
    acc += steer(target, true);
    cout << "ARRIVE\n";
}


// Separation
// Method checks for nearby boids and steers away
ofPoint Boid::separate(vector<Boid*> boids) {
    float desiredseparation = 25.0f;
    ofPoint steer;
    int count = 0;
	
    // For every boid in the system, check if it's too close
    for (int i = 0 ; i < boids.size(); i++) {
		Boid* other = boids[i];
		float d = ofDist(loc.x, loc.y, other->loc.x, other->loc.y);
		// If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
		if ((d > 0) && (d < desiredseparation)) {
			// Calculate vector pointing away from neighbor
			ofPoint diff = loc - other->loc;
			diff /= d;			// normalize
			diff /= d;        // Weight by distance
			steer += diff;
			count++;            // Keep track of how many
		}
    }
    // Average -- divide by how many
    if (count > 0) {
		steer /= (float)count;
    }
	
	
    // As long as the vector is greater than 0
	float mag = sqrt(steer.x*steer.x + steer.y*steer.y);
    if (mag > 0) {
		// Implement Reynolds: Steering = Desired - Velocity
		steer /= mag;
		steer *= maxspeed;
		steer -= vel;
		steer.x = ofClamp(steer.x, -maxforce, maxforce);
		steer.y = ofClamp(steer.y, -maxforce, maxforce);
    }
    return steer;
}

// Alignment
// For every nearby boid in the system, calculate the average velocity
ofPoint Boid::align(vector<Boid*> boids) {
    float neighbordist = 50.0;
    ofPoint steer;
    int count = 0;
    for (int i = 0 ; i < boids.size(); i++) {
		Boid* other = boids[i];
		
		float d = ofDist(loc.x, loc.y, other->loc.x, other->loc.y);
		if ((d > 0) && (d < neighbordist)) {
			steer += (other->vel);
			count++;
		}
    }
    if (count > 0) {
		steer /= (float)count;
    }
	
    // As long as the vector is greater than 0
	float mag = sqrt(steer.x*steer.x + steer.y*steer.y);
    if (mag > 0) {
		// Implement Reynolds: Steering = Desired - Velocity
		steer /= mag;
		steer *= maxspeed;
		steer -= vel;
		steer.x = ofClamp(steer.x, -maxforce, maxforce);
		steer.y = ofClamp(steer.y, -maxforce, maxforce);
    }
    return steer;
}

// Cohesion
// For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
ofPoint Boid::cohesion(vector<Boid*> boids) {
    float neighbordist = 50.0;
    ofPoint sum;   // Start with empty vector to accumulate all locations
    int count = 0;
    for (int i = 0 ; i < boids.size(); i++) {
		Boid* other = boids[i];
		float d = ofDist(loc.x, loc.y, other->loc.x, other->loc.y);
		if ((d > 0) && (d < neighbordist)) {
			sum += other->loc; // Add location
			count++;
		}
    }
    if (count > 0) {
		sum /= (float)count;
		return steer(sum, false);  // Steer towards the location
    }
    return sum;
}


