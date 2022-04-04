#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0, 0, 0);
    //ofSetFrameRate(5);//draws lines 5 times per second
    //------------------
    
//    gui.setup();
//
//    gui.add(intSlider.setup("int slider", 64, 3, 64));
//    //value it's gonnar start at: 64
//    //min value it can take, and max value it can take
//    gui.add(floatSlider.setup("float slider", 30.0, 0.0, 300.0));
//
//    //toggle will always start in the off position
//    gui.add(toggle.setup("toggle", false));
//    //button will always stay off, until it's presses
//    gui.add(button.setup("button"));
//    gui.add(label.setup("label", "THIS IS A LABEL"));
//
//    gui.add(intField.setup("int field", 100, 0, 100));
//    gui.add(floatField.setup("float field", 100.0, 0.0, 100.0));
//    //first stirng is for naming the string field, second one is the one we can type in; "text" there will be until we type on it and change
//    gui.add(textField.setup("text filed", "text"));
//
//    //same as intsliders: 1st-name, 2nd-starting val; 3r-min, 4th-max
//    gui.add(vec2Slider.setup("vec2 slider", ofVec2f(0.0, 0.0), ofVec2f(0.0, 0.0), ofVec2f(ofGetWidth(), ofGetHeight())));
//    gui.add(vec3Slider.setup("vec3 slider",ofVec3f(100,150,190) , ofVec3f(0,0,0), ofVec3f(255,255,255)));
//    gui.add(vec4Slider.setup("vec4 slider", ofVec4f(0,0,0,0), ofVec4f(0,0,0,0), ofVec4f(255,255,255,255)));
//
//    //min is 0 for all of them, max is 255 for all of them
    
    sliderGroup.setName("sliders");
    sliderGroup.add(intSlider.set("int slider", 3, 3, 64));//thickness of lines
    sliderGroup.add(floatSlider.set("float slider", 32, 32, 256));//
    
    circle.setup();//setting cirle
    
    mainGroup.add(circle.params);//main group includes circle parameters
    mainGroup.add(sliderGroup);//main group also includes slider group ,consisting of int clider and float slider, as well
    
    
    gui.setup(mainGroup);//insert main group into the gui
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //myLine.addVertex(ofRandom(ofGetHeight()),ofRandom(ofGetWidth()));
    
    ofSetCircleResolution(intSlider);
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofColor myColor;
//    myColor.setHsb(255, 255, 255, 80);
//    ofSetColor(myColor);
//    ofSetLineWidth(5);
//    myLine.draw();
    //----------------------
//    if(button){
//        ofSetColor(ofRandom(vec3Slider->x), ofRandom(vec3Slider->y), ofRandom(vec3Slider->z));//vec3 determines the brightness,darnkenss of circle
//    }
//    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 128);
//    ofSetCircleResolution(intSlider);//used for resolution
//    ofSetColor(vec4Slider->x, vec4Slider->y, vec4Slider->z, vec4Slider->w);
//    ofDrawCircle(vec2Slider->x, vec2Slider->y, 128);
//
//    gui.draw();
    
    
    ofSetColor(circle.colors->x, circle.colors->y, circle.colors->z);
    
    ofDrawCircle(circle.x, circle.y, floatSlider);
    
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
