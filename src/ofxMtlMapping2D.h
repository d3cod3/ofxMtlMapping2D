#pragma once

// OF
#include "ofMain.h"

//Mapping
#include "ofxMtlMapping2DSettings.h"
#include "ofxMtlMapping2DVertex.h"
#include "ofxMtlMapping2DQuad.h"
#include "ofxMtlMapping2DGrid.h"
#include "ofxMtlMapping2DTriangle.h"
#include "ofxMtlMapping2DMask.h"
#include "ofxMtlMapping2DShape.h"

#include "mtlUtils.h"

// Addons
#include "ofxXmlSettings.h"

#if defined(USE_OFX_SYPHON) && defined(TARGET_OSX)
#include "ofxSyphon.h"
#endif

//--------------------------------------------------------------
//--------------------------------------------------------------
enum MappingModeState
{
    MAPPING_LOCKED,
    MAPPING_EDIT
};

//--------------------------------------------------------------
//--------------------------------------------------------------
class ofxMtlMapping2D {
    
public:
    ofxMtlMapping2D();
    virtual ~ofxMtlMapping2D();
    
//  void init(int width, int height, string mappingXmlFilePath = "mapping/xml/shapes.xml", string uiXmlFilePath = "mapping/controls/mapping.xml", int numSample = 0);
    void init(int width, int height, int numSample = 0);
    void update();
    
    void bind();
    void unbind();
    void drawFbo();
    void draw();

    void setModeState(MappingModeState mappingModeState);
    MappingModeState getModeState();

    void mousePressed(ofMouseEventArgs &e);
    void keyPressed(ofKeyEventArgs &e);
    void windowResized(ofResizeEventArgs &e);

    vector<ofPolyline*> getMaskShapes();
    void chessBoard(int nbOfCol = 10);

    void loadXml(string xmlFile);
    
    bool bSaveShapes;
    bool bLoadShapes;
    bool bCreateQuad;
    bool bCreateGrid;
    bool bCreateTriangle;
    bool bCreateMask;

    bool bDeleteShape;

    bool bSelectedShapeChanged;
    int selectedShapeId;
    
#if defined(USE_OFX_SYPHON) && defined(TARGET_OSX)
    void selectSyphonServer(int syphonDirIdx);

    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
#endif


private:
    //string _mappingXmlFilePath;
    MappingModeState _mappingModeState;

    ofFbo _fbo;
    int _numSample;

    ofxXmlSettings _shapesListXML;
    list<ofxMtlMapping2DShape*>::iterator iteratorForShapeWithId(int shapeId);
    
#if defined(USE_OFX_SYPHON) && defined(TARGET_OSX)
    ofxSyphonServerDirectory _syphonServerDir;
    ofxSyphonClient _syphonClient;
    int _syphonDirIdx;
    
    void setupSyphon();
    void drawSyphon();
#endif

    void render();

    void createQuad();
    void createGrid();
    void createTriangle();
    void createMask();
    void deleteShape();

    void loadShapesList();
    void saveShapesList();

    void addListeners();
    void removeListeners();
};