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
    
    float angle;
    float angle1;
    float angle2;
    float angle3;
    float angle4;
    float angle5;
    float angle6;
    float angle7;
    float angle8;
    
    float angleSun1;
    float angleSun2;
    float anglePlanet;
    
    
    float rotationSpeed;
    int a;
    int b;
    int radius;
    int radiusPlanet;
    float x;
    
    glm::vec2 center;
    glm::vec2 point;
    glm::vec2 point1;
    glm::vec2 point2;
    glm::vec2 point3;
    glm::vec2 point4;
    glm::vec2 point5;
    glm::vec2 point6;
    glm::vec2 point7;
    glm::vec2 point8;
    
    ofxPanel gui;

    ofParameterGroup params;//colors
    ofParameter<ofVec3f> color;
    ofParameter<ofVec3f> color1;
    ofParameter<ofVec3f> color2;
    ofParameter<ofVec3f> color3;
    ofParameter<ofVec3f> color4;
    ofParameter<ofVec3f> color5;
    ofParameter<ofVec3f> color6;
    ofParameter<ofVec3f> color7;
    ofParameter<ofVec3f> color8;
    ofParameter<ofVec3f> colorSpace;
    ofParameter<ofVec4f> colorOrbits;
  
    bool isDrawGUI;
    
    ofParameterGroup mainGroup;
    
};
