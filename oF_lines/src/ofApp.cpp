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
    
    intSliderGroup.setName("Distribution");
    intSliderGroup.add(intSlider1.set("Lines 1", 50, 0, ofGetWidth()/2));//length of line - x component
    intSliderGroup.add(intSlider2.set("Lines 2", 50, 0, ofGetWidth()/2));//length of line - y component
    
    floatSliderGroup.setName("Thickness");
    floatSliderGroup.add(floatSlider1.set("Lines 1", 5, 1, 20));//thickness of line
    floatSliderGroup.add(floatSlider2.set("Lines 1", 5, 1, 20));//thickness of line
    
    
    params.setName("Colors");
    params.add(color1.set("Lines 1", ofVec3f(100,130,160), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    
    params.add(color2.set("Lines 2", ofVec3f(100,130,160), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    
    //circle.setup();//setting cirle
    //mainGroup.add(circle.params);//main group includes circle parameters
    
    
    mainGroup.add(intSliderGroup);
    mainGroup.add(floatSliderGroup);
    mainGroup.add(params);
    gui.setup(mainGroup);//insert main group into the gui
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //myLine.addVertex(ofRandom(ofGetHeight()),ofRandom(ofGetWidth()));
    
    ofSetCircleResolution(intSlider1);
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
    
    
    //ofSetColor(circle.color1->x, circle.color1->y, circle.color1->z);
    ofSetColor(color1->x,color1->y,color1->z);
    ofSetLineWidth(floatSlider1);
    
    ofDrawLine(0,ofGetHeight()/2,ofGetWidth(),ofGetHeight()/2);
    ofDrawLine(0,ofGetHeight()/2-intSlider1,ofGetWidth(),ofGetHeight()/2-intSlider1);
    ofDrawLine(0,ofGetHeight()/2+intSlider1,ofGetWidth(),ofGetHeight()/2+intSlider1);
    ofDrawLine(0,ofGetHeight()/2-2*intSlider1,ofGetWidth(),ofGetHeight()/2-2*intSlider1);
    ofDrawLine(0,ofGetHeight()/2+2*intSlider1,ofGetWidth(),ofGetHeight()/2+2*intSlider1);
    
    
    //ofSetColor(circle.color2->x, circle.color2->y, circle.color2->z);
    ofSetColor(color2->x, color2->y, color2->z);
    ofSetLineWidth(floatSlider2);
    
    ofDrawLine(0,ofGetHeight(),ofGetWidth(),0);
    ofDrawLine(0,ofGetHeight()-intSlider2,ofGetWidth()-intSlider2,0);
    ofDrawLine(0,ofGetHeight()-2*intSlider2,ofGetWidth()-2*intSlider2,0);
    ofDrawLine(0+intSlider2,ofGetHeight(),ofGetWidth(),0+intSlider2);
    ofDrawLine(0+2*intSlider2,ofGetHeight(),ofGetWidth(),0+2*intSlider2);
    
//
//    ofDrawLine(ofGetWidth()/6+20,ofGetHeight()/2,2*(ofGetWidth()/6+20),ofGetHeight()/2);
//    ofDrawLine(ofGetWidth()/6+20,ofGetHeight()/2-intSlider3,2*(ofGetWidth()/6+20),ofGetHeight()/2-intSlider3);
//    ofDrawLine(ofGetWidth()/6+20,ofGetHeight()/2+intSlider3,2*(ofGetWidth()/6+20),ofGetHeight()/2+intSlider3);
//    ofDrawLine(ofGetWidth()/6+20,ofGetHeight()/2-2*intSlider3,2*(ofGetWidth()/6+20),ofGetHeight()/2-2*intSlider3);
//    ofDrawLine(ofGetWidth()/6+20,ofGetHeight()/2+2*intSlider3,2*(ofGetWidth()/6+20),ofGetHeight()/2+2*intSlider3);
    
    //WHAT TO UPDATE/ADD: fix the issue with liens made by slider2; lower the opacity of colors; make two diferent controllers of the thickness; OPTIONAL-add maybe a third line
    
    
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
