//
//  ControlPoint.cpp
//  emptyExample
//
//  Created by Tetsuro Kato on 12/06/11.
//  Copyright (c) 2012年 KATO Tetsuro. All rights reserved.
//

#include "ControlPoint.h"
#include "ofMain.h"

ControlPoint::ControlPoint(float _x, float _y) : x(_x), y(_y) {
    
}

void ControlPoint::set(ofVec2f startPos, bool forward) {
    duration = sqrt((startPos.x - x)*(startPos.x - x) + 
                    (startPos.y - y)*(startPos.y - y)) / 200.f;
    
    if (!forward) {
        duration = ofClamp( 1.0 / duration * 5.0, 0, 4);
    }
}

float ControlPoint::getDuration() {
    return duration;
}