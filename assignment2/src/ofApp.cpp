#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofDisableAntiAliasing();
    ofSetLogLevel(OF_LOG_NOTICE);
    
    changeColors = false;
    changeSpeed = false;

    color1.r = 226;
    color1.g = 240;
    color1.b = 203;
    
    color2.r = 225;
    color2.g = 154;
    color2.b = 162;
    
    color3.r = 199;
    color3.g = 206;
    color3.b = 234;
    
    // scrolling ground
    k = 0.5;
//    groundSpeed = 0.5;
    groundRes   = 30;
    
    // build the ground 1
    for(int i=0; i<groundRes; i++) {
        float x = ofMap(i, 0, groundRes-1, 0, ofGetWidth());
        float y = ofGetHeight()/2 + ofRandom(-30, 100);
        groundLine.addVertex(x, y);
    }
    
    // build the ground 2
    for(int i=0; i<groundRes; i++) {
        float x = ofMap(i, 0, groundRes-1, 0, ofGetWidth());
        float y = ofGetHeight()/3 + ofRandom(-30, 100);
        groundLine2.addVertex(x, y);
    }
    
    // build the ground 3
    for(int i=0; i<groundRes; i++) {
        float x = ofMap(i, 0, groundRes-1, 0, ofGetWidth());
        float y = 2*ofGetHeight()/3 + ofRandom(-30, 100);
        groundLine3.addVertex(x, y);
    }

    
    box2d.init();
    box2d.setGravity(0, 20);
    box2d.registerGrabbing();
}

//--------------------------------------------------------------
void ofApp::update() {
    groundSpeed = k;
    
    ofBackground(color3);
    
    ofRemove(circles, ofxBox2dBaseShape::shouldRemoveOffScreen);
    ofRemove(boxes, ofxBox2dBaseShape::shouldRemoveOffScreen);
    
    box2d.update();
    
    ground.clear();
    ground.addVertexes(groundLine);
    ground.create(box2d.getWorld());
    
    ground2.clear();
    ground2.addVertexes(groundLine2);
    ground2.create(box2d.getWorld());
    
    ground3.clear();
    ground3.addVertexes(groundLine3);
    ground3.create(box2d.getWorld());
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    for(auto & circle : circles) {
        ofFill();
        ofSetColor(color1);
        circle->draw();
    }

    for(auto & box : boxes) {
        ofFill();
        ofSetColor(color2);
        box->draw();
    }
   
//    for(auto & triangle : triangles) {
//        ofFill();
//        ofSetColor(255, 154, 162);
//        triangle->draw();
//    }
    
    float t = ofGetElapsedTimef() * groundSpeed;
    float y = ofSignedNoise(0.1, t) * 200;
   
    float newHeight = ofGetHeight()/2 + y;
    int n = (int)groundLine.size();
   
    for(int i=n-1; i>=1; i--) {
        groundLine[i].y = groundLine[i-1].y;
    }
    groundLine[0].y = newHeight;
    
    
 
    float newHeight2 = ofGetHeight()/3 + y;
    int nn = (int)groundLine2.size();
   
    for(int i=nn-1; i>=1; i--) {
        groundLine2[i].y = groundLine2[i-1].y;
    }
    groundLine2[0].y = newHeight2;
    
    
    float newHeight3 = 2*ofGetHeight()/3 + y;
    int nnn = (int)groundLine3.size();
   
    for(int i=nnn-1; i>=1; i--) {
        groundLine3[i].y = groundLine3[i-1].y;
    }
    groundLine3[0].y = newHeight3;

//    auto circle = make_shared<ofxBox2dCircle>();
//    circle->setPhysics(3.0, 0.53, 0.1);
//    circle->setup(box2d.getWorld(), groundLine[n/2].x, groundLine[n/2].y, 30);
//    wheels.push_back(circle);
//    circle->draw();
//
//
//    circle->setPhysics(3.0, 0.53, 0.1);
//    circle->setup(box2d.getWorld(), groundLine[n/2].x-100 , groundLine[n/2].y, 30);
//    wheels.push_back(circle);
//    circle->draw();
//
 
    ofSetColor(255);
    ground.updateShape();
    ofSetLineWidth(1);
    ground.draw();
    ofSetLineWidth(3);
    ground2.draw();
    ofSetLineWidth(5);
    ground3.draw();
   
    string info = "";
    info += "Press [c] for circles\n";
    info += "Press [b] for blocks\n";
    info += "Press [h] for changing the theme\n";
    info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
    ofSetColor(255);
    ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    if(key == 'c') {
        auto circle = make_shared<ofxBox2dCircle>();
        circle->setPhysics(3.0, 0.53, 0.1);
        circle->setup(box2d.getWorld(), mouseX, mouseY, ofRandom(20, 50));
        circles.push_back(circle);
    }
    
    
    if(key == 'b') {
        float w = ofRandom(10, 30);
        float h = ofRandom(10, 30);
        auto box = make_shared<ofxBox2dRect>();
        box->setPhysics(3.0, 0.53, 0.1);
        box->setup(box2d.getWorld(), mouseX, mouseY, w, h);
        boxes.push_back(box);
        
//        float a = ofRandom(10, 30);
//        float b = ofRandom(10, 30);
//        float c = ofRandom(10, 30);
//
//        auto triangle = make_shared<ofxBox2dPolygon>();
//
//        triangle->addTriangle((a,0), (b,0), (c,0));
//
//        triangle->setPhysics(1.0, 0.3, 0.3);
//
//        triangle->create(box2d.getWorld());
//
//        triangles.push_back(triangle);
    }
    
    if(key == 'h') {
        changeColors = !changeColors;
        
        if(changeColors)
        {
            color1.r = 231;
            color1.g = 84;
            color1.b = 102;
            
            color2.r = 43;
            color2.g = 45;
            color2.b = 66;
            
            color3.r = 141;
            color3.g = 153;
            color3.b = 174;
        }
        else
        {
            color1.r = 226;
            color1.g = 240;
            color1.b = 203;
            
            color2.r = 225;
            color2.g = 154;
            color2.b = 162;
            
            color3.r = 199;
            color3.g = 206;
            color3.b = 234;
            
        }
    }
    
    if(key == 's') {
        changeSpeed = !changeSpeed;
        
        if(changeSpeed)
        {
            k = 1.5;
        }
        else {
            k = 0.5;
        }
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::resized(int w, int h){
    
}
