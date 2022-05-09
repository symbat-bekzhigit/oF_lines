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
    
    
    ofSetBackgroundColor(255, 255, 255);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetVerticalSync(true);

    // Box2d
    box2d.init();
    box2d.createGround();
    box2d.registerGrabbing();
    box2d.createGround(bottomLeft, bottomRight);
    box2d.createGround(topLeft, topRight);
    box2d.setGravity(gravityX, gravityY);

    
    breakupIntoTriangles = true;
    bFill = false;
    
    protagonist.setPhysics(0.3, 0.1, 0.1); //density, bounce, friction
    protagonist.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2, 50);
//
//    circle.setPhysics(0.3, 1, 0.1); //density, bounce, friction
//    circle.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2, 50);

    //phase 1 setup
    // register the listener so that we get the events
    ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
    ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);
    
     //load the 8 sfx soundfile
//    for (int i=0; i<N_SOUNDS; i++) {
//        sound[i].load("sfx/"+ofToString(i)+".mp3");
//        sound[i].setMultiPlay(true);
//        sound[i].setLoop(false);
//    }
    
    for (int i=0; i<5; i++) {
        colors[i].r = ofRandom(255);
        colors[i].g = ofRandom(255);
        colors[i].b = ofRandom(255);
        
    }
    
//    protagonist.setData(new SoundData());
//    auto * sd = (SoundData*)protagonist.getData();
//    sd->soundID = ofRandom(0, N_SOUNDS);
//    sd->bHit    = false;
//
//    hitOnce = false;
    
    protagonist.setData(new ColorData());
    auto * sd = (ColorData*)protagonist.getData();
    sd->color.r = 255;
    sd->color.g = 255;
    sd->color.b = 255;
    sd->bHit  = false;
    hitOnce = false;
    
    background1.load("/Users/symbat/Desktop/projects/assignment3/bin/data/citycolorful.jpeg");
    
    
    //phase 2 setup

    // first we add just a few circles
    for (int i=0; i<1; i++) {
        auto circle = make_shared<ofxBox2dCircle>();
        circle->setPhysics(3.0, 0.1, 0.1); //desnity,bounce,fricition

//        circle->setup(box2d.getWorld(), ofGetWidth()/2, 100+(i*20), 8);
        circle->setup(box2d.getWorld(), protagonist.getPosition().x-100, 100+(i*20), 8);
        
        circle->setData(new ColorData());
        auto * sd = (ColorData*)circle->getData();
        sd->color = changeTo;
        sd->bHit    = false;
        
        circlesForJoints.push_back(circle);
    }
    
    // now connect each circle with a joint
    for (int i=0; i<circlesForJoints.size(); i++) {
        auto joint = make_shared<ofxBox2dJoint>(box2d.getWorld(), i == 0 ? protagonist.body : circlesForJoints[i-1]->body, circlesForJoints[i]->body);
        
        joint->setLength(80);
        joints.push_back(joint);
    }
    
    
    changeTheme = false;
    
}

//void ofApp::contactStart(ofxBox2dContactArgs &e) {
//    if(e.a != NULL && e.b != NULL) {
//
//        // if we collide with the ground we do not
//        // want to play a sound. this is how you do that
//        if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
//
//            SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
//            SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
//
//            if(aData) {
//                aData->bHit = true;
//                sound[aData->soundID].play();
//            }
//
//            if(bData) {
//                bData->bHit = true;
//                sound[bData->soundID].play();
//            }
//        }
//    }
//}

void ofApp::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        
        if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
            
            ColorData * aData = (ColorData*)e.a->GetBody()->GetUserData();
            ColorData * bData = (ColorData*)e.b->GetBody()->GetUserData();
            
            if(aData) {
                aData->bHit = true;
                changeTo = colors[aData->colorID];
            }
            
            if(bData) {
                bData->bHit = true;
                changeTo = colors[bData->colorID];
            }
        }
    }
}


//--------------------------------------------------------------
//void ofApp::contactEnd(ofxBox2dContactArgs &e) {
//    if(e.a != NULL && e.b != NULL) {
//
//        SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
//        SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
//
//        if(aData) {
//            aData->bHit = false;
//        }
//
//        if(bData) {
//            bData->bHit = false;
//        }
//    }
//}


void ofApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        
        ColorData * aData = (ColorData*)e.a->GetBody()->GetUserData();
        ColorData * bData = (ColorData*)e.b->GetBody()->GetUserData();

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
    ofRemove(rectangles, [](shared_ptr<ofxBox2dRect> shape) -> bool {
        return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape->getPosition());
    });
    ofRemove(circles, [](shared_ptr<ofxBox2dCircle> shape) -> bool {
        return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape->getPosition());
    });
    
 
    box2d.update();
    
    ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
    protagonist.addAttractionPoint(ofGetWidth()/2,ofGetHeight()/2,1.1);

    
    if(changeTheme == false) //phase 1
    {
        //randomly appearing circles
        if((int)ofRandom(0, 50) == 0) {
            auto c = std::make_shared<ofxBox2dCircle>();
            c->setPhysics(1, 0.1, 0.9);
            radius = ofRandom(20, 40);
            c->setup(box2d.getWorld(),ofGetWidth()-radius, ofRandom(ofGetHeight()), radius);

    //        c->setData(new SoundData());
    //        auto * sd = (SoundData*)c->getData();
    //        sd->soundID = ofRandom(0, N_SOUNDS);
    //        sd->bHit    = false;
            
            c->setData(new ColorData());
            auto * sd = (ColorData*)c->getData();
            sd->colorID = ofRandom(0, 5);
            sd->bHit    = false;
            
            circles.push_back(c);
        }
        
        //randomly appearing rectangles
        if((int)ofRandom(0, 50) == 0) {
            
            float w = ofRandom(20, 60);
            float h = ofRandom(20, 60);
            auto rect = std::make_shared<ofxBox2dRect>();
            rect->setPhysics(3.0, 0.1, 0.9);
            rect->setup(box2d.getWorld(), ofGetWidth()-radius, ofRandom(ofGetHeight()), w, h);
            
            rect->setData(new ColorData());
            auto * sd = (ColorData*)rect->getData();
            sd->colorID = ofRandom(0, 5);
            sd->bHit    = false;
            
            rectangles.push_back(rect);
        }
    }
    
    else //phase 2
    {
        //randomly appearing circles
        if((int)ofRandom(0, 150) == 0) {
            auto c = std::make_shared<ofxBox2dCircle>();
            c->setPhysics(1, 0.1, 0.9);
            radius = ofRandom(10, 30);
            c->setup(box2d.getWorld(),ofGetWidth()-radius, ofRandom(ofGetHeight()), radius);

    //        c->setData(new SoundData());
    //        auto * sd = (SoundData*)c->getData();
    //        sd->soundID = ofRandom(0, N_SOUNDS);
    //        sd->bHit    = false;
            
            c->setData(new ColorData());
            auto * sd = (ColorData*)c->getData();
            sd->colorID = ofRandom(0, 5);
            sd->bHit    = false;
            
            circles.push_back(c);
        }
        
        //randomly appearing rectangles
        if((int)ofRandom(0, 100) == 0) {
            
            float w = ofRandom(10, 30);
            float h = ofRandom(10, 30);
            auto rect = std::make_shared<ofxBox2dRect>();
            rect->setPhysics(3.0, 0.1, 0.9);
            rect->setup(box2d.getWorld(), ofGetWidth()-radius, ofRandom(ofGetHeight()), w, h);
            
            rect->setData(new ColorData());
            auto * sd = (ColorData*)rect->getData();
            sd->colorID = ofRandom(0, 5);
            sd->bHit    = false;
            
            rectangles.push_back(rect);
        }
    }
  
    
    
    ColorData * data = (ColorData*)protagonist.getData();
    if((changeTheme == true) && (data && data->bHit))
    {
        // add a new circle
        auto circle = make_shared<ofxBox2dCircle>();
//        circle->setPhysics(3.0, 0.53, 0.1); (0.1, 0.1, 0.1)
        circle->setPhysics(3.0, 0.1, 0.1);
        circle->setup(box2d.getWorld(), circlesForJoints.back()->getPosition().x+ofRandom(-30, 30), circlesForJoints.back()->getPosition().y-30, 8);
        
        circle->setData(new ColorData());
        auto * sd = (ColorData*)circle->getData();
        sd->color = changeTo;
        sd->bHit    = false;
        
        circlesForJoints.push_back(circle);
    
        // get this cirlce and the prev cirlce
        int a = (int)circlesForJoints.size()-2;
        int b = (int)circlesForJoints.size()-1;

        // now connect the new circle with a joint
        auto joint = make_shared<ofxBox2dJoint>(box2d.getWorld(), circlesForJoints[a]->body, circlesForJoints[b]->body);
        joint.get()->setLength(25);
        joints.push_back(joint);
        
        data->bHit = false; //sometimes when the contact is too long, it will keep adding new joints, so i chnage bhit to false
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //start
    ofSetColor(255, 255, 255);
    background1.draw(0,0,ofGetWidth(),ofGetHeight());

    
    for(size_t i=0; i<circles.size(); i++) {
        ofFill();
        ColorData * data = (ColorData*)circles[i].get()->getData();
        ofSetColor(colors[data->colorID]);
        circles[i].get()->draw();
        
    }
    
    for(size_t i=0; i<rectangles.size(); i++) {
        ofFill();
        ColorData * data = (ColorData*)rectangles[i].get()->getData();
        ofSetColor(colors[data->colorID]);
        rectangles[i].get()->draw();
        
    }

    
    
    if(changeTheme == false)
    {
        ofFill();
        ColorData * data = (ColorData*)protagonist.getData();
        if(data && data->bHit)  ofSetColor(changeTo);
        else ofSetColor(255, 255, 255);
        protagonist.draw();
    }
    
    if(changeTheme == true)
    {
        ofFill();
        ofSetColor(255, 255, 255);
        protagonist.draw();
        
        for(auto &circle : circlesForJoints) {
            ofFill();
            ColorData * data = (ColorData*)circle->getData();
            ofSetColor(data->color);
            circle->draw();
        }
        
        
        for(auto &joint : joints) {
            ofSetColor(0x444342);
            joint->draw();
        }
        
    }
    

  
    
    ///////////////////end
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //draw more circles
    if(key == '1') {
        auto circle = std::make_shared<ofxBox2dCircle>();
        circle->setPhysics(0.3, 0.5, 0.1); //density, bounce, friction
        circle->setup(box2d.getWorld(), mouseX, mouseY, ofRandom(10, 20));

//        circle->setData(new SoundData());
//        auto * sd = (SoundData*)circle->getData();
//        sd->soundID = ofRandom(0, N_SOUNDS);
//        sd->bHit    = false;
        
        circle->setData(new ColorData());
        auto * sd = (ColorData*)circle->getData();
        sd->colorID = ofRandom(0, 5);
        sd->bHit    = false;
        
        circles.push_back(circle);
    }
    
    
    //draw more rectangles
    if(key == '2') {
        float w = ofRandom(14, 20);
        float h = ofRandom(14, 20);
        auto rect = std::make_shared<ofxBox2dRect>();
        rect->setPhysics(3.0, 0.53, 0.9);
        rect->setup(box2d.getWorld(), mouseX, mouseY, w, h);
        
        rect->setData(new ColorData());
        auto * sd = (ColorData*)rect->getData();
        sd->colorID = ofRandom(0, 5);
        sd->bHit    = false;
        
        rectangles.push_back(rect);
    }
    
    if(key == 'e') box2d.enableEvents();
    if(key == 'd') box2d.disableEvents();
//    if(key == 'n') {
//
//        // add a new circle
//        auto circle = make_shared<ofxBox2dCircle>();
//        circle->setPhysics(3.0, 0.53, 0.1);
//        circle->setup(box2d.getWorld(), circlesForJoints.back()->getPosition().x+ofRandom(-30, 30), circlesForJoints.back()->getPosition().y-30, 8);
//
//        circle->setData(new ColorData());
//        auto * sd = (ColorData*)circle->getData();
//        sd->color = changeTo;
//        sd->bHit    = false;
//
//        circlesForJoints.push_back(circle);
//
//        // get this cirlce and the prev cirlce
//        int a = (int)circlesForJoints.size()-2;
//        int b = (int)circlesForJoints.size()-1;
//
//        // now connect the new circle with a joint
//        auto joint = make_shared<ofxBox2dJoint>(box2d.getWorld(), circlesForJoints[a]->body, circlesForJoints[b]->body);
//        joint.get()->setLength(25);
//        joints.push_back(joint);
//    }
    if(key == 'w'){
        changeTheme = !changeTheme;
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
