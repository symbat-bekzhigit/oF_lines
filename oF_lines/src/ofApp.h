#pragma once

#include "ofMain.h"
#include "ofxGui.h"


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
    

    ofxPanel gui;
    ofParameterGroup intSliderGroup;
    ofParameter<int> intSlider1;
    ofParameter<int> intSlider2;
  
    ofParameterGroup floatSliderGroup;
    ofParameter<float> floatSlider1;
    ofParameter<float> floatSlider2;

    
    ofParameterGroup params;
    ofParameter<ofVec3f> color1;
    ofParameter<ofVec3f> color2;
    ofParameter<ofVec3f> color3;
    
    ofParameterGroup mainGroup;
    
    
    
		
};
