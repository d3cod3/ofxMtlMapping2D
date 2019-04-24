#include "ofxMtlMapping2DEllipse.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
ofxMtlMapping2DEllipse::ofxMtlMapping2DEllipse()
{
    radius = 100.0f;
}

//--------------------------------------------------------------
ofxMtlMapping2DEllipse::~ofxMtlMapping2DEllipse(){

}

//--------------------------------------------------------------
void ofxMtlMapping2DEllipse::render()
{    
    glPushMatrix();
    glMultMatrixf(inputPolygon->homoMatrix);
    glBegin(GL_POLYGON);
    
    
    for (int i = 0; i < inputPolygon->polyline->size(); i++) {
        glTexCoord2f(inputPolygon->polyline->getVertices()[i].x, inputPolygon->polyline->getVertices()[i].y);
        glVertex2f(inputPolygon->polyline->getVertices()[i].x - inputPolygon->boundingBox.x, inputPolygon->polyline->getVertices()[i].y - inputPolygon->boundingBox.y);
    }
    
    
    glEnd();
    glPopMatrix();
}


//--------------------------------------------------------------
void ofxMtlMapping2DEllipse::createDefaultShape()
{
    shapeSettings["type"] = "ellipse";
    
    inputPolygon = new ofxMtlMapping2DInput();
    
    
    int xOffset = ofGetWidth()/2.0;
    int yOffset = ofGetHeight()/2.0;

    for(int i=0;i<4;i++){
        //Create a new vertex
        ofxMtlMapping2DVertex* newVertex = new ofxMtlMapping2DVertex();
        newVertex->init(xOffset + radius*cosf(i*TWO_PI/4), yOffset + radius*sinf(i*TWO_PI/4));
        vertices.push_back(newVertex);

        // Input
        newVertex = new ofxMtlMapping2DVertex();
        newVertex->init(xOffset + radius*cosf(i*TWO_PI/4), yOffset + radius*sinf(i*TWO_PI/4));
        newVertex->isDefiningTectureCoord = true;
        inputPolygon->vertices.push_back(newVertex);
    }
        
    
    // ----
    inputPolygon->init(shapeId);
}

//--------------------------------------------------------------
void ofxMtlMapping2DEllipse::calcHomography()
{
    updatePolyline();
    
    inputPolygon->calcHomography(polyline->getVertices()[0].x, polyline->getVertices()[0].y,
                              polyline->getVertices()[1].x, polyline->getVertices()[1].y,
                              polyline->getVertices()[2].x, polyline->getVertices()[2].y,
                              polyline->getVertices()[3].x, polyline->getVertices()[3].y);
}
