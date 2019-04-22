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
void ofApp::keyPressed(int key){
    if(key == 's'){
        // save mapping
        ofFileDialogResult saveFileResult = ofSystemSaveDialog("mapping.xml", "Save your mapping config");
        if (saveFileResult.bSuccess){
            _mapping->saveMappingAs(saveFileResult.getPath());
        }
    }else if(key == 'l'){
        // load mapping
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a mapping file");
        if (openFileResult.bSuccess){
            _mapping->loadMapping(openFileResult.getPath());
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
