#include "ofxMtlMapping2DQuad.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
ofxMtlMapping2DQuad::ofxMtlMapping2DQuad()
{

}

//--------------------------------------------------------------
ofxMtlMapping2DQuad::~ofxMtlMapping2DQuad(){

}

//--------------------------------------------------------------
void ofxMtlMapping2DQuad::render()
{    
    glPushMatrix();
    glMultMatrixf(inputPolygon->homoMatrix);
    glBegin(GL_POLYGON);
    
    if (ofIsGLProgrammableRenderer()) {
        quad.clear();
        quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        for (int i = 0; i < polyline->size(); i++) {
            quad.addVertex(glm::vec3(polyline->getVertices()[i].x - boundingBox.x, polyline->getVertices()[i].y - boundingBox.y, 0));
            quad.addTexCoord(glm::vec2(inputPolygon->polyline->getVertices()[i].x, inputPolygon->polyline->getVertices()[i].y));
        }
        ofPushMatrix();
        ofTranslate(boundingBox.x,boundingBox.y,0);
        quad.draw(OF_MESH_FILL);
        ofPopMatrix();
    }else{
        for (int i = 0; i < inputPolygon->polyline->size(); i++) {
            glTexCoord2f(inputPolygon->polyline->getVertices()[i].x, inputPolygon->polyline->getVertices()[i].y);
            glVertex2f(polyline->getVertices()[i].x - boundingBox.x, polyline->getVertices()[i].y - boundingBox.y);
        }
    }

    glEnd();
    glPopMatrix();
}


//--------------------------------------------------------------
void ofxMtlMapping2DQuad::createDefaultShape()
{
    shapeSettings["type"] = "quad";
    
    inputPolygon = new ofxMtlMapping2DInput();
    
    
    int xOffset = ofGetWidth()/2.0;
    int yOffset = ofGetHeight()/2.0;
    
    //Create a new vertex
    int x = 0;
    int y = 0;
    ofxMtlMapping2DVertex* newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    vertices.push_back(newVertex);
    
    // Input
    newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    newVertex->isDefiningTectureCoord = true;
    inputPolygon->vertices.push_back(newVertex);
    
    x = 100;
    y = 0;
    newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    vertices.push_back(newVertex);
    
    // Input
    newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    newVertex->isDefiningTectureCoord = true;
    inputPolygon->vertices.push_back(newVertex);
    
    x = 100;
    y = 100;
    newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    vertices.push_back(newVertex);
    
    // Input
    newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    newVertex->isDefiningTectureCoord = true;
    inputPolygon->vertices.push_back(newVertex);
    
    x = 0;
    y = 100;
    newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    vertices.push_back(newVertex);
    
    // Input
    newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    newVertex->isDefiningTectureCoord = true;
    inputPolygon->vertices.push_back(newVertex);
    
    // ----
    inputPolygon->init(shapeId);
}

//--------------------------------------------------------------
void ofxMtlMapping2DQuad::calcHomography()
{
    updatePolyline();
    
    inputPolygon->calcHomography(polyline->getVertices()[0].x, polyline->getVertices()[0].y,
                              polyline->getVertices()[1].x, polyline->getVertices()[1].y,
                              polyline->getVertices()[2].x, polyline->getVertices()[2].y,
                              polyline->getVertices()[3].x, polyline->getVertices()[3].y);
}
