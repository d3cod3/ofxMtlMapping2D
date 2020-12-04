#include "ofxMtlMapping2DTriangle.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
ofxMtlMapping2DTriangle::ofxMtlMapping2DTriangle()
{

}

//--------------------------------------------------------------
ofxMtlMapping2DTriangle::~ofxMtlMapping2DTriangle(){

}

//--------------------------------------------------------------
void ofxMtlMapping2DTriangle::render()
{    
    glPushMatrix();
    glBegin(GL_POLYGON);

    if (ofIsGLProgrammableRenderer()) {
        quad.clear();
        quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        for (int i = 0; i < polyline->size(); i++) {
            quad.addVertex(glm::vec3(polyline->getVertices()[i].x, polyline->getVertices()[i].y, 0));
            quad.addTexCoord(glm::vec2(inputPolygon->polyline->getVertices()[i].x, inputPolygon->polyline->getVertices()[i].y));
        }
        quad.draw(OF_MESH_FILL);
    }else{
        for (int i = 0; i < inputPolygon->polyline->size(); i++) {
            glTexCoord2f(inputPolygon->polyline->getVertices()[i].x, inputPolygon->polyline->getVertices()[i].y);
            glVertex2f(polyline->getVertices()[i].x, polyline->getVertices()[i].y);
        }
    }
    
    glEnd();
    glPopMatrix();
}

//--------------------------------------------------------------
void ofxMtlMapping2DTriangle::createDefaultShape()
{
    shapeSettings["type"] = "triangle";
    inputPolygon = new ofxMtlMapping2DInput();
    
    int xOffset = ofGetWidth()/2.0;
    int yOffset = ofGetHeight()/2.0;

    int x = 50;
    int y = 0;
    
    ofxMtlMapping2DVertex* newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    vertices.push_back(newVertex);
    
    // Input
    newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    newVertex->isDefiningTectureCoord = true;
    inputPolygon->vertices.push_back(newVertex);
    
    x = 0;
    y = 100;
    
    //Create a new vertex
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
    
    //Create a new vertex
    newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    vertices.push_back(newVertex);
    
    // Input
    newVertex = new ofxMtlMapping2DVertex();
    newVertex->init(xOffset + x - newVertex->width/2, yOffset + y - newVertex->height/2);
    newVertex->isDefiningTectureCoord = true;
    inputPolygon->vertices.push_back(newVertex);
    
    inputPolygon->init(shapeId);
}
