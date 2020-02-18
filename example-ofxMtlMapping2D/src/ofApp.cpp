#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofBackground(50);
    
    // ----
    _mapping = new ofxMtlMapping2D();
    _mapping->init(1280, 720, ofToDataPath("mapping/default.xml"));
}

//--------------------------------------------------------------
void ofApp::update(){

    _mapping->update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    // ----
    _mapping->bind();
    
        // draw a test pattern
        _mapping->chessBoard();
    
    _mapping->unbind();
    
    
    //-------- mapping of the towers/shapes
    _mapping->draw();
     
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs &e){

    _mapping->keyPressed(e);

    if(e.key == 's'){
        // save mapping
        ofFileDialogResult saveFileResult = ofSystemSaveDialog("mapping.xml", "Save your mapping config");
        if (saveFileResult.bSuccess){
            _mapping->saveMappingAs(saveFileResult.getPath());
        }
    }else if(e.key == 'l'){
        // load mapping
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a mapping file");
        if (openFileResult.bSuccess){
            _mapping->loadMapping(openFileResult.getPath());
        }
    }
}


//--------------------------------------------------------------
void ofApp::mouseDragged(ofMouseEventArgs &e){
    _mapping->mouseDragged(e);
}

//--------------------------------------------------------------
void ofApp::mousePressed(ofMouseEventArgs &e){
    _mapping->mousePressed(e);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(ofMouseEventArgs &e){
    _mapping->mouseReleased(e);
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(ofMouseEventArgs &e){
    _mapping->mouseScrolled(e);
}

//--------------------------------------------------------------
void ofApp::windowResized(ofResizeEventArgs &e){
    _mapping->windowResized(e);
}
