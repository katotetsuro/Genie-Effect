#pragma once

#include "ofMain.h"
#include "ControlPoint.h"

enum GenieStatus {
    VISIBLE,
    FORWARD,
    INVISIBLE,
    BACKWARD,
};

class testApp : public ofBaseApp{
private:
    void updateDuration();
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofMesh mesh;
    ofImage image;
    int cols, rows;
    
    vector<ControlPoint> controlPoints;
    float maxDuration;
    ofVec2f clickedPosition;
    GenieStatus status;
    float startTime;
};
