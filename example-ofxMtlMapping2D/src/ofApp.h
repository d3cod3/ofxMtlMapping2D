#pragma once

#include "ofMain.h"
#include "ofxMtlMapping2D.h"

class ofApp : public ofBaseApp{

public:
    void            setup();
    void            update();
    void            draw();

    void            keyPressed(ofKeyEventArgs &e);

    void            mouseDragged(ofMouseEventArgs &e);
    void            mousePressed(ofMouseEventArgs &e);
    void            mouseReleased(ofMouseEventArgs &e);
    void            mouseScrolled(ofMouseEventArgs &e);

    void            windowResized(ofResizeEventArgs &e);

private:

    ofxMtlMapping2D* _mapping;

};
