#include "ofApp.h"

void ofApp::setup(){

    ofBackground(0);
 
    angle = 0;
    angle2 = 0;
    rotationSpeed=0.05;
    rotationSpeed2 = 1;
    width = 50;
    widthLarge = 500;;
    ofSetCircleResolution(100);
    
    ofSetFrameRate(60);
    i = 10;
    k = 20;
}

//--------------------------------------------------------------
void ofApp::update(){


    angle2 += rotationSpeed2;
    angle2 = ofWrap(angle2, 0, 2*width+2*k);
    
    
    x = ofMap( ofNoise( ofGetElapsedTimef()), 0, 1, ofGetWidth()/7, ofGetWidth()/7 + width);
    y = ofMap( ofNoise( ofGetElapsedTimef()), 0, 1, ofGetHeight()/7, ofGetHeight()/7 + width);
    
    //lower right
    x1 = ofMap( ofNoise( 1000.0 + ofGetElapsedTimef()), 0, 1, ofGetWidth()/2, ofGetWidth()/2 + width);
    y1 = ofMap( ofNoise( ofGetElapsedTimef()), 0, 1, ofGetHeight()/2, ofGetHeight()/2 + width);
    
    //lower left
    x2 = ofMap( ofNoise( ofGetElapsedTimef()), 0, 1, ofGetWidth()/4, ofGetWidth()/4 + width);
    y2 = ofMap( ofNoise( 2000.0 + ofGetElapsedTimef()), 0, 1, ofGetHeight()/2, ofGetHeight()/2 + width);
    
    //upper right
    x3 = ofMap( ofNoise( ofGetElapsedTimef()), 0, 1, ofGetWidth()/2, ofGetWidth()/2 + width);
    y3 = ofMap( ofNoise( 2000.0 + ofGetElapsedTimef()), 0, 1, ofGetHeight()/4, ofGetHeight()/4 + width);
    
    //upper left
    x4 = ofMap( ofNoise( 1000.0 + ofGetElapsedTimef()), 0, 1, ofGetWidth()/4, ofGetWidth()/4 + width);
    y4 = ofMap( ofNoise( ofGetElapsedTimef()), 0, 1, ofGetHeight()/4, ofGetHeight()/4 + width);
    
    point2 = { x2 + angle2, y2};
    point = { x1, y1 + angle2};
    point3 = { x3 , y3 + angle2};
    point4 = { x4 + angle2, y4};
    
    point2_2 = { x2 + angle2, y2};
    point_2 = { x1, y1 + angle2};
    point3_2 = { x3 , y3 + angle2};
    point4_2 = { x4 + angle2, y4};
    

    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofNoFill();//large rectangle
    ofSetColor(255);
    ofDrawRectangle(x, y, widthLarge, widthLarge);
    
   
    for(int i=0; i<100; i+=20)//lower right
    {
        ofNoFill();//rect 1
        ofSetColor(255);
        ofDrawRectangle(x1+i, y1+i, 2*width+2*k - i, 2*width+2*k - i);
    }
    
   // ofDrawCircle(x1+80+(width-80)/2, y1+80+(width-80)/2, (width-80)/2);
    //ofDrawRectangle(x1+2*width+2*k, y1+80,  2*width+2*k - 80, 2*width+2*k - 80);
    
    ofFill();
    ofSetColor(200, 10, 10);//red circle
    ofDrawCircle(point, 10);
    
    ofSetColor(0,0,255);//blue circle
    ofDrawCircle(point.x+2*width+2*k,point.y, 10);
    
    
    for(int i=0; i<100; i+=30)//lower left rect
    {
        ofNoFill();
        ofSetColor(255);
        ofDrawRectangle(x2+i, y2+i, 2*width+2*k - i, 2*width+2*k - i);
    }
    
    ofFill();
    ofSetColor(200, 10, 10);//red circle
    ofDrawCircle(point2, 10);
    
    ofSetColor(0,0,255);//blue circle
    ofDrawCircle(point2.x,point2.y+2*width+2*k, 10);



    for(int i=0; i<100; i+=40)//upper right rect
    {
        ofNoFill();
        ofSetColor(255);
        ofDrawRectangle(x3+i, y3+i, 2*width+2*k-i, 2*width+2*k-i);
    }
    
    ofFill();
    ofSetColor(200, 10, 10);//red circle
    ofDrawCircle(point3, 10);
    
    ofSetColor(0,0,255);//blue circle
    ofDrawCircle(point3.x+2*width+2*k,point3.y, 10);
    
    
    for(int i=0; i<100; i+=50)//upper left rect
    {
        ofNoFill();//rect 1
        ofSetColor(255);
        ofDrawRectangle(x4+i, y4+i, 2*width+2*k-i, 2*width+2*k-i);
    }
  
    ofFill();
    ofSetColor(200, 10, 10);//red circle
    ofDrawCircle(point4, 10);
    
    ofSetColor(0,0,255);//blue circle
    ofDrawCircle(point4.x,point4.y+2*width+2*k, 10);
    


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
