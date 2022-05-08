#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"


#define N_SOUNDS 5

class SoundData {
public:
    int     soundID;
    bool bHit;
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
    vector <shared_ptr<ofxBox2dPolygon>>  polyShapes;
    
    ofxBox2dCircle circle;
    
    ofxBox2dCircle protagonist;
    
    float gravityX= -1.0;
    float gravityY= 0.0;
    
    bool circle1;
    void applyForce(ofVec2f force,ofVec2f point);
    
    ofPoint bottomLeft;
    ofPoint bottomRight;
    ofPoint topLeft;
    ofPoint topRight;
    
    
    // when the ball hits we play this sound
    ofSoundPlayer  sound[N_SOUNDS];
    
    // this is the function for contacts
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
    bool hitOnce;

    
		
};
