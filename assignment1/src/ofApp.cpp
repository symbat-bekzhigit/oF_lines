#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(80);
        
    //initial values
    angle1=0;
    angle2=4;
    angle3=1.9;
    angle4=0.2;
    angle5=3;
    angle6=5.7;
    angle7=3.8;
    angle8=4.8;
    rotationSpeed=0.015;
    a = 210;
    b = 70;
    radius = 65;
    radiusPlanet = 25;
    ofSetCircleResolution(100);
    
//    intSliderGroup.setName("Distribution");
//    intSliderGroup.add(intSlider1.set("Lines 1",395, 1, 500));
//    intSliderGroup.add(intSlider2.set("Lines 2", 301, 1, 500));

    params.setName("Colors");
    params.add(color.set("Sun", ofVec3f(200,150,255), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    params.add(colorSpace.set("Space", ofVec3f(0,0,0), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    params.add(colorOrbits.set("Orbits", ofVec4f(255,255,255,100), ofVec4f(0,0,0,0), ofVec4f(255,255,255,255)));
    params.add(color1.set("Mercury", ofVec3f(102,0,51), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    params.add(color2.set("Venus", ofVec3f(200,50,50), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    params.add(color3.set("Earth", ofVec3f(20,150,40), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    params.add(color4.set("Mars", ofVec3f(210,10,10), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    params.add(color5.set("Jupiter", ofVec3f(190,80,0), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    params.add(color6.set("Saturn", ofVec3f(255,120,0), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    params.add(color7.set("Uranus", ofVec3f(102,220,255), ofVec3f(0,0,0), ofVec3f(255,255,255)));
    params.add(color8.set("Neptun", ofVec3f(50,150,255), ofVec3f(0,0,0), ofVec3f(255,255,255)));

    
    
    mainGroup.add(params);//insert params into the main group
    gui.setup(mainGroup);//insert main group into the gui
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //press the mouse to stop the angle from incrementing.
    
    angle1+=rotationSpeed;//at each update the angle gets incremented
    angle2= angle2+rotationSpeed;
    angle3= angle3+rotationSpeed;
    angle4= angle4+rotationSpeed;
    angle5= angle5+rotationSpeed;
    angle6= angle6+rotationSpeed;
    angle7= angle7+rotationSpeed;
    angle8= angle8+rotationSpeed;
    
    //if the angle is more than or equal to two PI (a full rotation measured in Radians) then make it zero.
    //angle = ofWrap(angle, 0, TWO_PI);
    angle1 = ofWrap(angle1, 0, TWO_PI);
    angle2 = ofWrap(angle2, 0, TWO_PI);
    angle3 = ofWrap(angle3, 0, TWO_PI);
    angle4 = ofWrap(angle4, 0, TWO_PI);
    angle5 = ofWrap(angle5, 0, TWO_PI);
    angle6 = ofWrap(angle6, 0, TWO_PI);
    angle7 = ofWrap(angle7, 0, TWO_PI);
    angle8 = ofWrap(angle8, 0, TWO_PI);
    
    //here we set the planets' position
   // point = {cos(angle) * radius, sin(angle) * radius};
    point1 = { ofGetWidth()/2 + cos(angle1) * a, ofGetHeight()/2 + sin(angle1) * b };
    point2 = { ofGetWidth()/2 + cos(angle2) * a * 1.2, ofGetHeight()/2 + sin(angle2) * b * 1.2 };
    point3 = { ofGetWidth()/2 + cos(angle3) * a * 1.4, ofGetHeight()/2 + sin(angle3) * b * 1.4 };
    point4 = { ofGetWidth()/2 + cos(angle4) * a * 1.6, ofGetHeight()/2 + sin(angle4) * b * 1.6 };
    point5 = { ofGetWidth()/2 + cos(angle5) * a * 1.8, ofGetHeight()/2 + sin(angle5) * b * 1.8 };
    point6 = { ofGetWidth()/2 + cos(angle6) * a * 2.0, ofGetHeight()/2 + sin(angle6) * b * 2 };
    point7 = { ofGetWidth()/2 + cos(angle7) * a * 2.2, ofGetHeight()/2 + sin(angle7) * b * 2.2 };
    point8 = { ofGetWidth()/2 + cos(angle8) * a * 2.4, ofGetHeight()/2 + sin(angle8) * b * 2.4 };
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(colorSpace->x,colorSpace->y,colorSpace->z);

    
    //draw star and milky way
//    ofSetColor(255);
//    ofDrawLine(200, 200, ofSignedNoise(100), ofSignedNoise(200));
    
    for(int i=0; i<10; i++)
    {
        ofSetColor(colorOrbits->x, colorOrbits->y, colorOrbits->z);
        ofFill();
        ofDrawCircle(ofRandom(ofGetWidth(), ofNoise(ofGetWidth())), ofRandom(ofGetHeight(), ofNoise(ofGetHeight())), 2);
        
        ofSetColor(255,255,0);
        ofFill();
        ofDrawCircle(ofRandom(ofGetWidth(), ofNoise(ofGetWidth())), ofRandom(ofGetHeight(), ofNoise(ofGetHeight())), 3);

    }
    
    //draw the orbits
    ofNoFill();
    ofSetColor(colorOrbits->x, colorOrbits->y, colorOrbits->z, colorOrbits->w);
    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2,2*a,2*b);
    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2,2*a*1.2,2*b*1.2);
    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2,2*a*1.4,2*b*1.4);
    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2,2*a*1.6,2*b*1.6);
    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2,2*a*1.8,2*b*1.8);
    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2,2*a*2,2*b*2);
    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2,2*a*2.2,2*b*2.2);
    ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2,2*a*2.4,2*b*2.4);

    
    for (int i=0; i<40; i++)
    {
        //sun
        ofSetColor(255,color->x,66);
        angleSun1  = ofRandom(0,TWO_PI);
        angleSun2  = ofRandom(0,TWO_PI);
        ofDrawLine(ofGetWidth()/2 + radius * cos(angleSun1),ofGetHeight()/2 + radius * sin(angleSun1), ofGetWidth()/2 + radius * cos(angleSun2),ofGetHeight()/2  + radius * sin(angleSun2));

        ofSetColor(255,color->y,66);
        angleSun1  = ofRandom(0,TWO_PI);
        angleSun2  = ofRandom(0,TWO_PI);
        ofDrawLine(ofGetWidth()/2 + radius * cos(angleSun1),ofGetHeight()/2  + radius * sin(angleSun1), ofGetWidth()/2 + radius * cos(angleSun2),ofGetHeight()/2  + radius * sin(angleSun2));
        
        ofSetColor(255,color->z,66);
        angleSun1  = ofRandom(0,TWO_PI);
        angleSun2  = ofRandom(0,TWO_PI);
        ofDrawLine(ofGetWidth()/2 + radius * cos(angleSun1),ofGetHeight()/2 + radius * sin(angleSun1), ofGetWidth()/2 + radius * cos(angleSun2),ofGetHeight()/2 + radius * sin(angleSun2));
    }
    
    for(int i=0; i<20; i++)
    {
        
        //mercury
        anglePlanet  = ofRandom(0,TWO_PI);

        ofSetColor(color1->x,0,51);
        ofDrawLine(point1.x, point1.y, point1.x + radiusPlanet * cos(anglePlanet), point1.y + radiusPlanet * sin(anglePlanet));
        
        ofSetColor(102,color1->y,51);
        ofDrawLine(point1.x, point1.y, point1.x - radiusPlanet * cos(anglePlanet), point1.y - radiusPlanet * sin(anglePlanet));
        
        ofSetColor(102,0,color1->z);
        ofDrawLine(point1.x, point1.y, point1.x + radiusPlanet * cos(anglePlanet), point1.y - radiusPlanet * sin(anglePlanet));
        ofDrawLine(point1.x, point1.y, point1.x - radiusPlanet * cos(anglePlanet), point1.y + radiusPlanet * sin(anglePlanet));
        
        //venus
        
        ofSetColor(color2->x,50,50);
        ofDrawLine(point2.x, point2.y, point2.x + radiusPlanet * cos(anglePlanet), point2.y + radiusPlanet * sin(anglePlanet));
        
        ofSetColor(200,color2->y,50);
        ofDrawLine(point2.x, point2.y, point2.x - radiusPlanet * cos(anglePlanet), point2.y - radiusPlanet * sin(anglePlanet));
        
        ofSetColor(200,50,color2->z);
        ofDrawLine(point2.x, point2.y, point2.x + radiusPlanet * cos(anglePlanet), point2.y - radiusPlanet * sin(anglePlanet));
        ofDrawLine(point2.x, point2.y, point2.x - radiusPlanet * cos(anglePlanet), point2.y + radiusPlanet * sin(anglePlanet));
        
        //earth
        
        ofSetColor(color3->x,150,40);//green varying
        ofDrawLine(point3.x, point3.y, point3.x + radiusPlanet * cos(anglePlanet), point3.y + radiusPlanet * sin(anglePlanet));
        ofDrawLine(point3.x, point3.y, point3.x - radiusPlanet * cos(anglePlanet), point3.y + radiusPlanet * sin(anglePlanet));
        
        ofSetColor(20,color3->y,40);//blue varying
        ofDrawLine(point3.x, point3.y, point3.x - radiusPlanet * cos(anglePlanet), point3.y - radiusPlanet * sin(anglePlanet));

        ofSetColor(20,150,color->z);//white varying
        ofDrawLine(point3.x, point3.y, point3.x + radiusPlanet * cos(anglePlanet), point3.y - radiusPlanet * sin(anglePlanet));
        
        //mars

        ofSetColor(color4->x,10,10);//red varying
        ofDrawLine(point4.x, point4.y, point4.x + radiusPlanet * cos(anglePlanet), point4.y + radiusPlanet * sin(anglePlanet));
        
        ofSetColor(210,color4->y,10);//brown varying
        ofDrawLine(point4.x, point4.y, point4.x - radiusPlanet * cos(anglePlanet), point4.y - radiusPlanet * sin(anglePlanet));
        
        ofSetColor(210,10,color4->z);//black varying
        ofDrawLine(point4.x, point4.y, point4.x + radiusPlanet * cos(anglePlanet), point4.y - radiusPlanet * sin(anglePlanet));
        ofDrawLine(point4.x, point4.y, point4.x - radiusPlanet * cos(anglePlanet), point4.y + radiusPlanet * sin(anglePlanet));
        
        
        //jupiter
        
        ofSetColor(color5->x,80,0);//brown
        ofDrawLine(point5.x, point5.y, point5.x + radiusPlanet * cos(anglePlanet), point5.y + radiusPlanet * sin(anglePlanet));
        
        ofSetColor(190,color5->y,0);//orange
        ofDrawLine(point5.x, point5.y, point5.x - radiusPlanet * cos(anglePlanet), point5.y - radiusPlanet * sin(anglePlanet));
        
        ofSetColor(190,80,color5->z);//beige
        ofDrawLine(point5.x, point5.y, point5.x + radiusPlanet * cos(anglePlanet), point5.y - radiusPlanet * sin(anglePlanet));
        ofDrawLine(point5.x, point5.y, point5.x - radiusPlanet * cos(anglePlanet), point5.y + radiusPlanet * sin(anglePlanet));
     
        
        //saturn
        
        ofSetColor(color6->x,120,0);
        ofDrawLine(point6.x, point6.y, point6.x + radiusPlanet * cos(anglePlanet), point6.y + radiusPlanet * sin(anglePlanet));
        
        ofSetColor(255,color6->y,0);
        ofDrawLine(point6.x, point6.y, point6.x - radiusPlanet * cos(anglePlanet), point6.y - radiusPlanet * sin(anglePlanet));
        
        ofSetColor(255,120,color6->z);
        ofDrawLine(point6.x, point6.y, point6.x + radiusPlanet * cos(anglePlanet), point6.y - radiusPlanet * sin(anglePlanet));
        ofDrawLine(point6.x, point6.y, point6.x - radiusPlanet * cos(anglePlanet), point6.y + radiusPlanet * sin(anglePlanet));
        
        //uranus
        
        ofSetColor(color7->x,220,255);
        ofDrawLine(point7.x, point7.y, point7.x + radiusPlanet * cos(anglePlanet), point7.y + radiusPlanet * sin(anglePlanet));
        
        ofSetColor(102,color7->y,255);
        ofDrawLine(point7.x, point7.y, point7.x - radiusPlanet * cos(anglePlanet), point7.y - radiusPlanet * sin(anglePlanet));
        
        ofSetColor(102,220,color7->z);
        ofDrawLine(point7.x, point7.y, point7.x + radiusPlanet * cos(anglePlanet), point7.y - radiusPlanet * sin(anglePlanet));
        ofDrawLine(point7.x, point7.y, point7.x - radiusPlanet * cos(anglePlanet), point7.y + radiusPlanet * sin(anglePlanet));
        
        //neptun
        
        ofSetColor(color8->x,150,255);
        ofDrawLine(point8.x, point8.y, point8.x + radiusPlanet * cos(anglePlanet), point8.y + radiusPlanet * sin(anglePlanet));
        
        ofSetColor(50,color8->y,255);
        ofDrawLine(point8.x, point8.y, point8.x - radiusPlanet * cos(anglePlanet), point8.y - radiusPlanet * sin(anglePlanet));
        
        ofSetColor(50,150,color8->z);
        ofDrawLine(point8.x, point8.y, point8.x + radiusPlanet * cos(anglePlanet), point8.y - radiusPlanet * sin(anglePlanet));
        ofDrawLine(point8.x, point8.y, point8.x - radiusPlanet * cos(anglePlanet), point8.y + radiusPlanet * sin(anglePlanet));
        
    }
    
    if (isDrawGUI) {
           gui.draw();
       }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g')
        isDrawGUI = !isDrawGUI;
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
