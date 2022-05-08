#include "ofApp.h"
#include "circle.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    
    bottomLeft.x = 0;
    bottomLeft.y = ofGetHeight();
    bottomRight.x = ofGetWidth();
    bottomRight.y = ofGetHeight();
    
    
    topLeft.x = 0;
    topLeft.y = 0;
    topRight.x = ofGetWidth();
    topRight.y = 0;
    
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetVerticalSync(true);

    // Box2d
    box2d.init();

    box2d.createGround();
    box2d.registerGrabbing();
    box2d.createGround(bottomLeft, bottomRight);
    box2d.createGround(topLeft, topRight);
    
    
   // box2d.setFPS(60.0);
    //box2d.setGravity(-1, 0);
    box2d.setGravity(gravityX, gravityY);

    breakupIntoTriangles = true;
    bFill = false;
    
    protagonist.setPhysics(0.3, 1, 0.1); //density, bounce, friction
    protagonist.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2, 50);

    circle.setPhysics(0.3, 1, 0.1); //density, bounce, friction
    circle.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2, 50);

    
    ///////////////////////////////// start
    // register the listener so that we get the events
    ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
    ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);
    
     //load the 8 sfx soundfile
    for (int i=0; i<N_SOUNDS; i++) {
        sound[i].load("sfx/"+ofToString(i)+".mp3");
        sound[i].setMultiPlay(true);
        sound[i].setLoop(false);
    }
    
    protagonist.setData(new SoundData());
    auto * sd = (SoundData*)protagonist.getData();
    sd->soundID = ofRandom(0, N_SOUNDS);
    sd->bHit    = false;
    
    hitOnce = false;
    
}

void ofApp::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        
        // if we collide with the ground we do not
        // want to play a sound. this is how you do that
        if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
            
            SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
            SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
            
            if(aData) {
                aData->bHit = true;
                sound[aData->soundID].play();
            }
            
            if(bData) {
                bData->bHit = true;
                sound[bData->soundID].play();
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        
        SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
        SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();

        if(aData) {
            aData->bHit = false;
        }

        if(bData) {
            bData->bHit = false;
        }
    }
}


//--------------------------------------------------------------
void ofApp::update(){

    // remove shapes offscreen
    ofRemove(polyShapes, [](shared_ptr<ofxBox2dPolygon> shape) -> bool {
        return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape->getPosition());
    });
    ofRemove(circles, [](shared_ptr<ofxBox2dCircle> shape) -> bool {
        return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape->getPosition());
    });
    box2d.update();
    
    ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
    protagonist.addAttractionPoint(ofGetWidth()/2,ofGetHeight()/2,1.1);
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    ////////////// start
//    protagonist.setData(new SoundData());
//    auto * sd = (SoundData*)protagonist.getData();
//    sd->soundID = ofRandom(0, N_SOUNDS);
//    sd->bHit    = false;
    
    ofFill();
    ofSetColor(255, 255, 255);
    SoundData * data = (SoundData*)protagonist.getData();
    if(data && data->bHit)  ofSetHexColor(0xc0dd3b);
    else ofSetHexColor(0xff0000);
    
    protagonist.draw();

    ///////////////////end
    
    
   // protagonist.draw()
    
//    for(auto &circle : circles) {
//        ofFill();
//        ofSetHexColor(0xc0dd3b);
//        circle->draw();
//    }
//
    
    ////////////////////////start
    
    for(auto &circle : circles) {
        ofFill();
//        SoundData * data = (SoundData*)circle.get()->getData();
//
//        if(data && data->bHit) ofSetHexColor(0xff0000);
//        else ofSetHexColor(0x4ccae9);
        ofSetHexColor(0xc0dd3b);
        circle->draw();
    }
    ///////////////////end
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1') {
        auto circle = std::make_shared<ofxBox2dCircle>();
        circle->setPhysics(0.3, 0.5, 0.1); //density, bounce, friction
        circle->setup(box2d.getWorld(), mouseX, mouseY, ofRandom(10, 20));
        
        circle->setData(new SoundData());
        auto * sd = (SoundData*)circle->getData();
        sd->soundID = ofRandom(0, N_SOUNDS);
        sd->bHit    = false;
        
        circles.push_back(circle);
    }
    
    if(key == '2') box2d.enableEvents();
    if(key == '3') box2d.disableEvents();
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
