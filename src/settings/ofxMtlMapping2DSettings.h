#pragma once

#include "ofMain.h"

#include "ofxFontStash.h"

//--------------------------------------------------------------
class ofxMtlMapping2DSettings {
    public:
       
        // --- available / activated options
        static const bool kIsManuallyCreatingShapeEnabled;   
        static const bool kIsManuallyAddingDeletingVertexEnabled;
    
        // ---
        static ofxFontStash infoFont;
    
        // ---
        static float gridDefaultNbCols;
        static float gridDefaultNbRows;
};
