#pragma once

// OF
#include "ofMain.h"

// Addons
#include "ofxInfiniteCanvas.h"
#include "ofxXmlSettings.h"

//Mapping
#include "ofxMtlMapping2DVertex.h"
#include "ofxMtlMapping2DQuad.h"
#include "ofxMtlMapping2DGrid.h"
#include "ofxMtlMapping2DTriangle.h"
#include "ofxMtlMapping2DMask.h"
#include "ofxMtlMapping2DShape.h"

#include "mtlUtils.h"


//========================================================================
class ofxMtlMapping2D {
    
    public:    
        ofxMtlMapping2D();
        virtual ~ofxMtlMapping2D();
        
        void init(int width, int height, string mappingXmlFilePath = "mapping/xml/shapes.xml", string uiXmlFilePath = "mapping/controls/mapping.xml", int numSample = 0);
        void update();
        
        void    bind();
        void    unbind();
        void    drawFbo();
        void    draw();
        ofFbo   getOutputFbo();

        void mouseDragged(ofMouseEventArgs &e);
        void mousePressed(ofMouseEventArgs &e);
        void mouseReleased(ofMouseEventArgs &e);
        void mouseScrolled(ofMouseEventArgs &e);

        void keyPressed(ofKeyEventArgs &e);
        void windowResized(ofResizeEventArgs &e);

        vector<ofPolyline*> getMaskShapes();
        void chessBoard(int nbOfCol = 10);

    private:
        ofxInfiniteCanvas       canvasInput;
        ofEasyCam               easyCamInput;
        ofRectangle             canvasInputViewport;

        ofxInfiniteCanvas       canvasOutput;
        ofEasyCam               easyCamOutput;
        ofRectangle             canvasOutputViewport;

        ofVec2f                 actualMouse;

        bool                    isInputActive;
        bool                    isFocusChanged;

        string _mappingXmlFilePath;
        ofFbo _fbo;
        ofFbo _outputFbo;
        ofxXmlSettings _shapesListXML;
        list<ofxMtlMapping2DShape*>::iterator iteratorForShapeWithId(int shapeId);

        void render();
    
        void createQuad(float _x, float _y);
        void createGrid(float _x, float _y);
        void createTriangle(float _x, float _y);
        void createMask(float _x, float _y);
        void deleteShape();
    
        void loadShapesList();
        void saveShapesList();
    
        void addListeners();
        void removeListeners();
};
