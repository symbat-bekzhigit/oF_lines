#include "ofApp.h"
#include "circle.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetVerticalSync(true);

    // Box2d
    box2d.init();

    box2d.createGround();
    box2d.setFPS(60.0);
    //box2d.setGravity(-1, 0);
    box2d.setGravity(gravityX, gravityY);

    breakupIntoTriangles = true;
    bFill = false;
    
    protagonist.setPhysics(0.3, 1, 0.1); //density, bounce, friction
    protagonist.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2, 50);

    
//    Circle mainCircle;
//    mainCircle.setup(200,200,50);
    
}

//--------------------------------------------------------------
void ofApp::update(){
//    if(circle1 ==true){
//        gravityX=0.0;
//        gravityY=0.0;
//    }
//
//    else{
//        gravityX=-1.0;
//        gravityY=0.0;
//    }
//    box2d.setGravity(gravityX, gravityY);

    // remove shapes offscreen
    ofRemove(polyShapes, [](shared_ptr<ofxBox2dPolygon> shape) -> bool {
        return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape->getPosition());
    });
    ofRemove(circles, [](shared_ptr<ofxBox2dCircle> shape) -> bool {
        return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape->getPosition());
    });
    

    
    box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    circle1 = true;
//
//    ofSetColor(100, 100, 100);
//    auto circle = std::make_shared<ofxBox2dCircle>();
//    circle->setPhysics(0.3, 0.5, 0.1); //density, bounce, friction
//    circle->setup(box2d.getWorld(),ofGetElapsedTimef() * ofGetWidth(),
//    ofNoise(ofGetElapsedTimef()+1000) * ofGetHeight(),
//    20);
//    circles.push_back(circle);
//
//    circle1 = false;
    
    ofSetColor(255,50,50);
    protagonist.draw();

    for(auto &circle : circles) {
        ofFill();
        ofSetHexColor(0xc0dd3b);
        circle->draw();
    }
    
    
//    ofSetColor(100, 100, 100);
//    ofDrawCircle(ofNoise(ofGetElapsedTimef()) * ofGetWidth(),
//                        ofNoise(ofGetElapsedTimef()+1000) * ofGetHeight(),
//                        20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1') {
        auto circle = std::make_shared<ofxBox2dCircle>();
        circle->setPhysics(0.3, 0.5, 0.1); //density, bounce, friction
        
        circle->setup(box2d.getWorld(), mouseX, mouseY, ofRandom(10, 20));
        circles.push_back(circle);
    }
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
