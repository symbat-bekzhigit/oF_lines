#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(255, 255, 255);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetVerticalSync(true);

    // Box2d
    box2d.init();
    box2d.registerGrabbing();
    box2d.setGravity(gravityX, gravityY);
    breakupIntoTriangles = true;
    bFill = false;
    
    //set up the protagonist
    protagonist.setPhysics(0.3, 0.1, 0.1); //density, bounce, friction
    protagonist.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2, 50);

    
    //phase 1 setup
    
    // register the listener so that we get the events
    ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
    ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);

    //populate our array of colors with 5 different colors
    colors[0].setHex(0xED7F8C);
    colors[1].setHex(0xFEFF35);
    colors[2].setHex(0x61C7C9);
    colors[3].setHex(0xD5EBF6);
    colors[4].setHex(0xBB8B1F);

    //get the color data of the protagonist
    protagonist.setData(new ColorData());
    auto * sd = (ColorData*)protagonist.getData();
    sd->color.r = 255;
    sd->color.g = 255;
    sd->color.b = 255;
    sd->bHit  = false;
    hitOnce = false;

    
    //phase 2 setup
    
    // add just a few circles to the tails of the protagonist
    for (int i=0; i<1; i++) {
        auto circle = make_shared<ofxBox2dCircle>();
        circle->setPhysics(3.0, 0.1, 0.1); //desnity,bounce,fricition

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
    finalStage = false;
    gatherToCenter = true;
   
    //load the sound files and fonts
    mySound.load("Enchanted.mp3");
    mySound.play();
    
    explosion.load("explosion.mp3");
    
    introText.load("IndieFlower-Regular.ttf", 30);
    introTextSmall.load("IndieFlower-Regular.ttf", 20);
    isIntroScreen = true;
    
    
    endText.load("IndieFlower-Regular.ttf", 30);
    isEndScreen = false;
    counter = 0;
    
    box2d.enableEvents();
}

//--------------------------------------------------------------
//function for capturing the start of the collsision
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
//function for capturing the end of the collsision
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
    
//    ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
    protagonist.addAttractionPoint(ofGetWidth()/2,ofGetHeight()/2,1.1);
    
    //phase 1 - react
    //in this phase, protagonist will react to collision by changing its color the the color of the circle it collided with
    if(changeTheme == false and finalStage == false)
    {
        background1.load("bg1.jpg");
        
        //randomly appearing circles
        if((int)ofRandom(0, 50) == 0) {
            auto c = std::make_shared<ofxBox2dCircle>();
            c->setPhysics(1, 0.1, 0.9);
            radius = ofRandom(20, 40);
            c->setup(box2d.getWorld(),ofGetWidth()-radius, ofRandom(ofGetHeight()), radius);

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
    
    
    //phase 2 - adapt
    //in this phase, protagonist will react to collision by adding more circles in its tail
    else if(changeTheme == true and finalStage == false)
    {
        background1.load("bg2.jpg");
        
        //randomly appearing circles
        if((int)ofRandom(0, 150) == 0) {
            auto c = std::make_shared<ofxBox2dCircle>();
            c->setPhysics(1, 0.1, 0.9);
            radius = ofRandom(10, 30);
            c->setup(box2d.getWorld(),ofGetWidth()-radius, ofRandom(ofGetHeight()), radius);

            c->setData(new ColorData());
            auto * sd = (ColorData*)c->getData();
            sd->colorID = ofRandom(0, 5);
            sd->bHit    = false;
            
            circles.push_back(c);
        }
        
        //randomly appearing rectangles
        if((int)ofRandom(0, 100) == 0) {
            
            float w = ofRandom(10, 40);
            float h = ofRandom(10, 40);
            auto rect = std::make_shared<ofxBox2dRect>();
            rect->setPhysics(3.0, 0.1, 0.9);
            rect->setup(box2d.getWorld(), ofGetWidth()-radius, ofRandom(ofGetHeight()), w, h);
            
            rect->setData(new ColorData());
            auto * sd = (ColorData*)rect->getData();
            sd->colorID = ofRandom(0, 5);
            sd->bHit    = false;
            
            rectangles.push_back(rect);
        }
        
        //in the phase 2, protagonist will react to collision by adding more circles in its tail whose color correspond to the color of the object it collided with
        ColorData * data = (ColorData*)protagonist.getData();
        
        //if protagonist collided with some other circle..
        if((changeTheme == true) && (data && data->bHit))
        {
            // add a new circle
            auto circle = make_shared<ofxBox2dCircle>();
            circle->setPhysics(3.0, 0.1, 0.1);
            circle->setup(box2d.getWorld(), circlesForJoints.back()->getPosition().x+ofRandom(-30, 30), circlesForJoints.back()->getPosition().y-30, 8);
            
            //records the color data of the circle
            circle->setData(new ColorData());
            auto * sd = (ColorData*)circle->getData();
            sd->color = changeTo;
            sd->bHit    = false;
            
            //push back the cirlce to the corresponsing vector
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
  
    //phase 3 - evolve
    //in this phase, protagonist will be attracted to the center and the floating cirles and rectangles will be attracted to a protagonist
    else
    {
        background1.load("bg3.jpg");
        
        //remove the the tail and teh joints
        for (int i=0; i<joints.size(); i++) {
            joints.pop_back();
        }
        for (int i=0; i<circlesForJoints.size(); i++) {
            if(circlesForJoints[i] != NULL)
                circlesForJoints.pop_back();
        }
        changeTheme = false;

        
        //in this stage, random circles and rectangles will keep being generated
        if(gatherToCenter == true)
        {
            //randomly appearing circles
            if((int)ofRandom(0, 50) == 0) {
                auto c = std::make_shared<ofxBox2dCircle>();
                c->setPhysics(1, 0.1, 0.9);
                radius = ofRandom(20, 40);
                c->setup(box2d.getWorld(),ofGetWidth()-radius, ofRandom(ofGetHeight()), radius);

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
            
            //protagonsit willl be attracted to teh center
            protagonist.addAttractionPoint(ofGetWidth()/2, ofGetHeight()/2,5.0);
            ofVec2f position(ofGetWidth()/2, ofGetHeight()/2);
            float minDis = ofGetMousePressed() ? 300 : 200;
            
            
            //other objects will be attracted to the center too, surrounding the protagonist
            for(auto &circle : circles) {
                float dis = position.distance(circle->getPosition());
    
                if(dis < minDis) {
                    circle->addRepulsionForce(position, 0.5);
                }
                else {
                    circle->addAttractionPoint(position, 1.0);
                }
            }
    
            for(auto &rect : rectangles) {
                float dis = position.distance(rect->getPosition());
                if(dis < minDis) rect->addRepulsionForce(position, 1.2);
                rect->addAttractionPoint(position, 1.0);
            }
        }
        
        //if the user clicks "s" which stants for spread, the figures will be repulled from the centre
        else
        {
            
            ofVec2f position(ofGetWidth()/2, ofGetHeight()/2);
            float minDis = ofGetMousePressed() ? 300 : 200;
            
            //add repulsion force from the center
            protagonist.addRepulsionForce(position,6.0);
           
            for(auto &circle : circles) {
                float dis = position.distance(circle->getPosition());

                    circle->addRepulsionForce(position, 6.0);
            }
            
            for(auto &rect : rectangles) {
                float dis = position.distance(rect->getPosition());
                rect->addRepulsionForce(position, 6.0);
            }
        }


    }
}

//--------------------------------------------------------------
void ofApp::draw(){
     
    //draw this for an intro screen
    if(isIntroScreen == true)
    {
        ofSetBackgroundColor(255, 255, 255);
        ofSetColor(0, 0, 0);
        introText.drawString("The story of a circle", ofGetWidth()/4+60, ofGetHeight()/2);
        introTextSmall.drawString("A journey into the unknown", ofGetWidth()/4+90, ofGetHeight()/2+60);
        
    }
    
    //draw this for the end screen
    else if(isEndScreen == true)
    {
        ofSetBackgroundColor(255, 255, 255);
        ofSetColor(0, 0, 0);
        endText.drawString("The End", ofGetWidth()/2-60, ofGetHeight()/2);
        
    }
    
    //main story screen
    else {
        
        ofSetColor(255, 255, 255);
        background1.draw(0,0,ofGetWidth(),ofGetHeight());

        
        //draw randomly appearing circles and rectangles
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

        
        //1st phase
        if(changeTheme == false)
        {
            ofFill();
            ColorData * data = (ColorData*)protagonist.getData();
            if(data && data->bHit)  ofSetColor(changeTo);
            else ofSetColor(255, 255, 255);
            protagonist.draw();
        }
        
        //2nd phase
        else if(changeTheme == true)
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
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //draw more circles
    if(key == '1') {
        auto circle = std::make_shared<ofxBox2dCircle>();
        circle->setPhysics(0.3, 0.5, 0.1); //density, bounce, friction
        circle->setup(box2d.getWorld(), mouseX, mouseY, ofRandom(10, 20));

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
    
    if(key == 'c'){ //change theme
        changeTheme = !changeTheme;
    }
    
    if(key == 'f'){ //final stage
        finalStage = true;
        gatherToCenter = true;
        
    }
    if(key == 's') //spread
    {
        finalStage = true;
        gatherToCenter = false;
        explosion.play();
    }
    if(key == 'x') //for switching between entry/exit screens
    {
        if(counter == 0) //exit intro screen
        {
            isIntroScreen = false;
        }
        else if(counter == 1) //enter exit screen
        {
            isEndScreen = true;
           
        }
        counter++;
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
