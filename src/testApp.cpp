#include "testApp.h"
#include "ofxEasingFunc.h"

const int blockSize = 10;

float (*easingForward)(const float t) = &ofxEasingFunc::Cubic::easeIn;
float (*easingBackward)(const float t) = &ofxEasingFunc::Quad::easeOut;

//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    image.loadImage("gedou.jpg");
    cols = image.width / blockSize;
    rows = image.height / blockSize;
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    for (int y=0; y<rows; ++y) {
        for (int x=0; x<cols; ++x) {
            // 頂点
            mesh.addVertex(ofVec3f(x*blockSize, y*blockSize, 0));
            mesh.addVertex(ofVec3f((x+1)*blockSize, y*blockSize, 0));
            mesh.addVertex(ofVec3f((x+1)*blockSize, (y+1)*blockSize, 0));
            mesh.addVertex(ofVec3f((x+1)*blockSize, (y+1)*blockSize, 0));
            mesh.addVertex(ofVec3f(x*blockSize, (y+1)*blockSize, 0));
            mesh.addVertex(ofVec3f(x*blockSize, y*blockSize, 0));
            
            // テクスチャ貼る
            mesh.addTexCoord(ofVec2f(x*blockSize, y*blockSize));
            mesh.addTexCoord(ofVec2f((x+1)*blockSize, y*blockSize));
            mesh.addTexCoord(ofVec2f((x+1)*blockSize, (y+1)*blockSize));
             mesh.addTexCoord(ofVec2f((x+1)*blockSize, (y+1)*blockSize));
            mesh.addTexCoord(ofVec2f(x*blockSize, (y+1)*blockSize));
            mesh.addTexCoord(ofVec2f(x*blockSize, y*blockSize));
            
            // デフォの位置を覚えておく 無駄、多いですけどね・・・
            controlPoints.push_back(ControlPoint(x*blockSize, y*blockSize));
            controlPoints.push_back(ControlPoint((x+1)*blockSize, y*blockSize));
            controlPoints.push_back(ControlPoint((x+1)*blockSize, (y+1)*blockSize));
            controlPoints.push_back(ControlPoint((x+1)*blockSize, (y+1)*blockSize));
            controlPoints.push_back(ControlPoint(x*blockSize, (y+1)*blockSize));
            controlPoints.push_back(ControlPoint(x*blockSize, y*blockSize));

        }
    }
    
    ofSetWindowShape(image.width, image.height);
    
    status = VISIBLE;
}

//--------------------------------------------------------------
void testApp::update(){
    float elapsed = (ofGetElapsedTimef() - startTime);
    
    switch (status) {
        case VISIBLE:
            
            break;
        
        case FORWARD:
            if (elapsed > maxDuration) {
                vector<ofVec3f> verts = mesh.getVertices();
                for (vector<ofVec3f>::iterator it=verts.begin(); it!=verts.end(); ++it) {
                    it->x = clickedPosition.x;
                    it->y = clickedPosition.y;
                }
                status = INVISIBLE;
                break;
            }
            for (int y=0; y<rows; ++y) {
                for (int x=0; x<cols; ++x) {
                    for (int i=0; i<6; ++i) {
                        int index = 6*(y*cols+x) + i;
                        ControlPoint p = controlPoints[index];
                        float easedValue = easingForward(ofClamp(elapsed / p.getDuration(), 0.0, 1.0));
                        ofVec3f v;
                        
                        v.x = p.x + easedValue*(clickedPosition.x - p.x);
                        v.y = p.y + easedValue*(clickedPosition.y - p.y);
                        v.z = 0;
                        
                        mesh.setVertex(index, v);
                    }
                }
            }
            break;
            
        case INVISIBLE:
            break;
            
        case BACKWARD:
            if (elapsed > maxDuration) {
                vector<ofVec3f> verts = mesh.getVertices();
                for(int i=0; i<verts.size(); ++i) {
                    verts[i].x = controlPoints[i].x;
                    verts[i].y = controlPoints[i].y;
                }

                status = VISIBLE;
                break;
            }
            for (int y=0; y<rows; ++y) {
                for (int x=0; x<cols; ++x) {
                    for (int i=0; i<6; ++i) {
                        int index = 6*(y*cols+x) + i;
                        ControlPoint p = controlPoints[index];
                        float easedValue = easingBackward(ofClamp(elapsed / p.getDuration(), 0.0, 1.0));
                        ofVec3f v;
                        
                        v.x = clickedPosition.x + easedValue*(p.x - clickedPosition.x);
                        v.y = clickedPosition.y + easedValue*(p.y - clickedPosition.y);
                        v.z = 0;
                        
                        mesh.setVertex(index, v);
                    }
                }
            }
            break;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    image.getTextureReference().bind();
    mesh.draw();
    image.getTextureReference().unbind();
    
//    ofDrawBitmapString(ofToString(ofGetFrameRate(), 2), 10, 20);
}

//--------------------------------------------------------------
void testApp::exit() {
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if (status == VISIBLE) {
        status = FORWARD;
        startTime = ofGetElapsedTimef();
        clickedPosition.x = x;
        clickedPosition.y = y;
        updateDuration();
    }
    else if(status == INVISIBLE) {
        status = BACKWARD;
        startTime = ofGetElapsedTimef();
        clickedPosition.x = x;
        clickedPosition.y = y;
        updateDuration();
    }
    else {
        ofLogWarning("処理中だお");
    }
}

void testApp::updateDuration() {
    maxDuration = 0.0f;
    for (vector<ControlPoint>::iterator it=controlPoints.begin(); it != controlPoints.end(); ++it) {
        it->set(clickedPosition, status == FORWARD);
        maxDuration = max(maxDuration, it->getDuration());
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}