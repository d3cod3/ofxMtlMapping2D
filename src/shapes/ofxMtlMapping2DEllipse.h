#pragma once

#include "ofxMtlMapping2DShape.h"


//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxMtlMapping2DEllipse : public ofxMtlMapping2DShape {
	
    public:
        
        ofxMtlMapping2DEllipse();
        ~ofxMtlMapping2DEllipse();
        
    protected:
        virtual void createDefaultShape();
        virtual void render();
        virtual void calcHomography();

        float	radius;
};
