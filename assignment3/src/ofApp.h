#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"


#define N_SOUNDS 5

class ColorData {
public:
    ofColor  color;
    bool bHit;
    int colorID;
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    bool                                  breakupIntoTriangles;
    bool                                  bFill;
    ofPolyline                            shape;
    ofxBox2d                              box2d;
    vector <shared_ptr<ofxBox2dCircle>>   circles;
    vector <shared_ptr<ofxBox2dRect>>  rectangles;
    
    
    ofxBox2dCircle protagonist;
    
    float gravityX= -1.0;
    float gravityY= 0.0;
    
    void applyForce(ofVec2f force,ofVec2f point);
    ofImage background1;
    ofColor colors[5];
    
    // these are the functions for checking the collision
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
    bool hitOnce;
    
    float radius;
    ofColor changeTo;
    int index = 0;
    
  
    //these are the vectors for randonly generated circles, rectangles, and joints
    vector <shared_ptr<ofxBox2dJoint>> joints;
    vector <shared_ptr<ofxBox2dCircle>> circlesForJoints;
    vector <shared_ptr<ofxBox2dRect>> rectanglesForJoints;
    
    //
    bool changeTheme;
    bool finalStage;
    bool gatherToCenter;
    
    //sound
    ofSoundPlayer mySound;
    ofSoundPlayer explosion;
    
    //font and intro/exit sreens
    ofTrueTypeFont introText;
    ofTrueTypeFont introTextSmall;
    bool isIntroScreen;
    ofTrueTypeFont endText;
    bool isEndScreen;
    
    int counter;
    
		
};
