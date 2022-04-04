//
//  Circle.hpp
//  oF_lines
//
//  Created by Symbat Bekzhigit on 03/04/2022.
//

#ifndef Circle_hpp
#define Circle_hpp

#include "ofMain.h"

class Circle{
public:
    void setup();
    
    ofParameterGroup params;
    ofParameter<ofVec3f> colors;//we'll have 3 sliders for colors
    ofParameter<int> x;
    ofParameter<int> y;
};

#endif /* Circle_hpp */
