#pragma once

#include "ofMain.h"

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
    
//    ofPoint position;
//    float radius;
//    ofColor circleColor;
//    ofColor drawColor;
    
//    float position;
//    float x;
//    float y;
//    float c1;
//    float c2;
//    float c3;
    
    float angle;
    float angle2;
    
    float rotationSpeed;
    float rotationSpeed2;
    int width;
    int widthLarge;
    
    float x, x1, x2, x3, x4;
    float y, y1, y2, y3, y4;
    
    int i;
    int k;
    glm::vec2 point;
    glm::vec2 point2;
    glm::vec2 point3;
    glm::vec2 point4;
    
    glm::vec2 point_2;
    glm::vec2 point2_2;
    glm::vec2 point3_2;
    glm::vec2 point4_2;
    
 
		
};
