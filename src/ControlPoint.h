//
//  ControlPoint.h
//  emptyExample
//
//  Created by Tetsuro Kato on 12/06/11.
//  Copyright (c) 2012年 KATO Tetsuro. All rights reserved.
//

#ifndef emptyExample_ControlPoint_h
#define emptyExample_ControlPoint_h

#include "ofVec2f.h"

class ControlPoint {    
    float duration;
public:
    float x, y;
    ControlPoint() {};
    ControlPoint(float x, float y);
    void set(ofVec2f startPos, bool forward);
    float getDuration();
};

#endif
