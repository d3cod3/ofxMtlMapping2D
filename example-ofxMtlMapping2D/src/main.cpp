#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

    shared_ptr<ofApp> exampleApp(new ofApp);

    ofGLFWWindowSettings settings;
    settings.setGLVersion(2, 1);
    settings.stencilBits = 0;
    settings.setSize(1280,800);

    shared_ptr<ofAppBaseWindow> appWindow = ofCreateWindow(settings);

    ofRunApp(appWindow,exampleApp);
    ofRunMainLoop();

    return EXIT_SUCCESS;

}
