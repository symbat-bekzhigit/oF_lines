#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    intSliderGroup.setName("Distribution");
    intSliderGroup.add(intSlider1.set("Lines 1", 50, 0, ofGetWidth()/2));//length of line - x component
    intSliderGroup.add(intSlider2.set("Lines 2", 50, 0, ofGetWidth()/2));//length of line - y component
    
    floatSliderGroup.setName("Thickness");
    floatSliderGroup.add(floatSlider1.set("Lines 1", 5, 1, 20));//thickness of line
    floatSliderGroup.add(floatSlider2.set("Lines 1", 5, 1, 20));//thickness of line
    
    
    params.setName("Colors");
    
    params.add(color1.set("Lines 1", ofVec3f(100,130,160), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    
    params.add(color2.set("Lines 2", ofVec3f(100,130,160), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    
    params.add(color3.set("Background", ofVec3f(0,0,0), ofVec3f(0,0,0), ofVec3f(255,255,255)));
 
    
    mainGroup.add(intSliderGroup);
    mainGroup.add(floatSliderGroup);
    mainGroup.add(params);
    gui.setup(mainGroup);//insert main group into the gui
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(color3->x, color3->y, color3->z);
    
    ofSetColor(color1->x,color1->y,color1->z);
    ofSetLineWidth(floatSlider1);
    
    ofDrawLine(0,ofGetHeight()/2,ofGetWidth(),ofGetHeight()/2);
    ofDrawLine(0,ofGetHeight()/2-intSlider1,ofGetWidth(),ofGetHeight()/2-intSlider1);
    ofDrawLine(0,ofGetHeight()/2+intSlider1,ofGetWidth(),ofGetHeight()/2+intSlider1);
    ofDrawLine(0,ofGetHeight()/2-2*intSlider1,ofGetWidth(),ofGetHeight()/2-2*intSlider1);
    ofDrawLine(0,ofGetHeight()/2+2*intSlider1,ofGetWidth(),ofGetHeight()/2+2*intSlider1);
    
    
    ofSetColor(color2->x, color2->y, color2->z);
    ofSetLineWidth(floatSlider2);
    
    ofDrawLine(0,ofGetHeight(),ofGetWidth(),0);
    ofDrawLine(0,ofGetHeight()-intSlider2,ofGetWidth()-intSlider2,0);
    ofDrawLine(0,ofGetHeight()-2*intSlider2,ofGetWidth()-2*intSlider2,0);
    ofDrawLine(0+intSlider2,ofGetHeight(),ofGetWidth(),0+intSlider2);
    ofDrawLine(0+2*intSlider2,ofGetHeight(),ofGetWidth(),0+2*intSlider2);
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
