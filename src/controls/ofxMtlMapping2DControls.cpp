#include "ofxMtlMapping2DControls.h"
#include "ofxMtlMapping2DSettings.h"
#include "ofxMtlMapping2DShape.h"
#include "ofxMtlMapping2DShapes.h"
#include "ofxMtlMapping2DGrid.h"

#include "ofMain.h"

//--------------------------------------------------------------
ofxMtlMapping2DControls * ofxMtlMapping2DControls::_mapping2DControls = NULL;

//--------------------------------------------------------------
ofxMtlMapping2DControls * ofxMtlMapping2DControls::mapping2DControls(){
    if (_mapping2DControls == NULL) {
        _mapping2DControls = new ofxMtlMapping2DControls(kControlsMappingToolsPanelWidth);
    }
    return _mapping2DControls;
}

//--------------------------------------------------------------
ofxMtlMapping2DControls::ofxMtlMapping2DControls(int width){
    // ---- Shapes list
    // set default values
    _selectedShapeId = -1;
    _selectedShapeChanged = false;
    shapeCounter = 0;
    
    _shapesListCanvas = new ofxUIScrollableCanvas(width, 0, width, ofGetHeight());
    _shapesListCanvas->setScrollArea(width, 0, kControlsMappingShapesListPanelWidth, ofGetHeight());
    _shapesListCanvas->setScrollableDirections(false, true);
    _shapesListCanvas->setColorBack(ofColor(0, 210, 255, 90));
    _shapesListCanvas->autoSizeToFitWidgets();
    
    ofAddListener(_shapesListCanvas->newGUIEvent, this, &ofxMtlMapping2DControls::shapesListUiEvent);
    
    
    // --- Grid settings
    int gridSettingCanvasWidth = 200.0f;
    _gridSettingsCanvas = new ofxUICanvas();
    _gridSettingsCanvas->setPosition(width, ofGetHeight() - 90);
    _gridSettingsCanvas->setWidth(gridSettingCanvasWidth);
    _gridSettingsCanvas->setColorFill(ofxUIColor(200));
    _gridSettingsCanvas->setColorFillHighlight(ofxUIColor(255));
    _gridSettingsCanvas->setColorBack(ofColor(0, 210, 255, 90));
    
    ofxUISlider *nSlider;
    _gridSettingsCanvas->addLabel("GRID SETTINGS");
    nSlider = _gridSettingsCanvas->addSlider("NB COLS", 1.0, 20.0, &ofxMtlMapping2DSettings::gridDefaultNbCols);
    nSlider->setIncrement(1.0f);
    nSlider = _gridSettingsCanvas->addSlider("NB ROWS", 1.0, 20.0, &ofxMtlMapping2DSettings::gridDefaultNbRows);
    nSlider->setIncrement(1.0f);
    
    _gridSettingsCanvas->autoSizeToFitWidgets();
    ofAddListener(_gridSettingsCanvas->newGUIEvent, this, &ofxMtlMapping2DControls::gridSettingsListUiEvent);
    _gridSettingsCanvas->disable();
    
    // ---- Tool box
    shapeTypesAsString[MAPPING_2D_SHAPE_QUAD] = "quad";
    shapeTypesAsString[MAPPING_2D_SHAPE_ELLIPSE] = "ellipse";
    shapeTypesAsString[MAPPING_2D_SHAPE_GRID] = "grid";
    shapeTypesAsString[MAPPING_2D_SHAPE_TRIANGLE] = "triangle";
    shapeTypesAsString[MAPPING_2D_SHAPE_MASK] = "mask";
    
    // set default values
    _saveMapping = false;
    _loadMapping = false;
    _editShapes = false;
    _createNewQuad = false;
    _createNewEllipse = false;
    _createNewGrid = false;
    _createNewTriangle = false;
    _createNewMask = false;
    _showShapesId = true;
    _mappingModeChanged = true; // initialized to true so that when the app launch the 'shapes' are correctly setted.
    _mappingMode = MAPPING_MODE_OUTPUT;
    
    _toolsCanvas = new ofxUIScrollableCanvas(0, 0, width, ofGetHeight());
    _toolsCanvas->setScrollableDirections(false, true);
    _toolsCanvas->setColorBack(ofColor(0, 210, 255, 130));
    
    // add mapping shape controls
    if (ofxMtlMapping2DSettings::kIsManuallyCreatingShapeEnabled) {
        _toolsCanvas->addWidgetDown(new ofxUIImageToggle(kToggleSize, kToggleSize, _createNewQuad, "GUI/quad.png", kSettingMappingCreateNewQuad));
        //_toolsCanvas->addWidgetDown(new ofxUIImageToggle(kToggleSize, kToggleSize, _createNewEllipse, "GUI/quad.png", kSettingMappingCreateNewEllipse));
        _toolsCanvas->addWidgetDown(new ofxUIImageToggle(kToggleSize, kToggleSize, _createNewGrid, "GUI/grid.png", kSettingMappingCreateNewGrid));
        _toolsCanvas->addWidgetDown(new ofxUIImageToggle(kToggleSize, kToggleSize, _createNewTriangle, "GUI/triangle.png", kSettingMappingCreateNewTriangle));
        _toolsCanvas->addWidgetDown(new ofxUIImageToggle(kToggleSize, kToggleSize, _createNewMask, "GUI/mask.png", kSettingMappingCreateNewMask));
    }
    
    // ----
    ofAddListener(_toolsCanvas->newGUIEvent, this, &ofxMtlMapping2DControls::toolsUiEvent);
    
    setUIShapeEditingState(true);
}


#pragma mark -
#pragma mark Tool Box

//--------------------------------------------------------------
void ofxMtlMapping2DControls::toolsUiEvent(ofxUIEventArgs &event){
    string name = event.widget->getName();
    
    // ---- Creating a new shape
    if (name == kSettingMappingCreateNewQuad) {
        // will happen only if ofxMtlMapping2DSettings::kIsManuallyCreatingShapeEnabled is true
        if(getToggleValue(name)) {
            _createNewQuad = true;
        }
    }
    /*else if (name == kSettingMappingCreateNewEllipse) {
        // will happen only if ofxMtlMapping2DSettings::kIsManuallyCreatingShapeEnabled is true
        if(getToggleValue(name)) {
            _createNewEllipse = true;
        }
    }*/
    else if (name == kSettingMappingCreateNewGrid) {
        // will happen only if ofxMtlMapping2DSettings::kIsManuallyCreatingShapeEnabled is true
        if(getToggleValue(name)) {
            _createNewGrid = true;
        }
    }
    else if (name == kSettingMappingCreateNewTriangle) {
        // will happen only if ofxMtlMapping2DSettings::kIsManuallyCreatingShapeEnabled is true
        if(getToggleValue(name)) {
            _createNewTriangle = true;
        }
    }
    else if (name == kSettingMappingCreateNewMask) {
        // will happen only if ofxMtlMapping2DSettings::kIsManuallyCreatingShapeEnabled is true
        if(getToggleValue(name)) {
            _createNewMask = true;
        }
    }
    
    // ----
    if (getToggleValue(name)) {
        unselectShapesToggles();
        ofxMtlMapping2DShape::resetActiveShapeVars();
        ofxMtlMapping2DPolygon::resetActivePolygonVars();
        
        _mappingModeChanged = true;
        
        refreshShapesListForMappingMode(_mappingMode);

    }
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::setUIShapeEditingState(bool isOn)
{
    _editShapes = isOn;
    
    if (!_editShapes) {
        // Set all Shapes and their InteractiveObj
        list<ofxMtlMapping2DShape*>::iterator it;
        for (it=ofxMtlMapping2DShapes::pmShapes.begin(); it!=ofxMtlMapping2DShapes::pmShapes.end(); it++) {
            ofxMtlMapping2DShape* shape = *it;
            shape->setAsIdle();
        }
        
        // ---
        ofxMtlMapping2DShape::resetActiveShapeVars();
        ofxMtlMapping2DShape::resetActivePolygonVars();
        
        // ---
        _shapesListCanvas->disable();
        hideGridSettingsCanvas();
        
    } else {
        
        // ---
        _shapesListCanvas->enable();
        showGridSettingsCanvas();
    }
    
    // ----
    ((ofxUIImageToggle *)_toolsCanvas->getWidget(kSettingMappingCreateNewQuad))->setVisible(_editShapes);
    //((ofxUIImageToggle *)_toolsCanvas->getWidget(kSettingMappingCreateNewEllipse))->setVisible(_editShapes);
    ((ofxUIImageToggle *)_toolsCanvas->getWidget(kSettingMappingCreateNewGrid))->setVisible(_editShapes);
    ((ofxUIImageToggle *)_toolsCanvas->getWidget(kSettingMappingCreateNewTriangle))->setVisible(_editShapes);
    ((ofxUIImageToggle *)_toolsCanvas->getWidget(kSettingMappingCreateNewMask))->setVisible(_editShapes);
}


#pragma mark -
#pragma mark Shapes List Related

//--------------------------------------------------------------
void ofxMtlMapping2DControls::shapesListUiEvent(ofxUIEventArgs &event)
{
    string name = event.widget->getName();
    
    vector<string> result = ofSplitString(name, " ");
    int shapeId = ofToInt(result[1]);
    string shapeTypeAsString = result[2];
    int shapeType = -1;
    
    map<ofxMtlMapping2DShapeType,string>::iterator it;
    for ( it = shapeTypesAsString.begin() ; it != shapeTypesAsString.end(); it++ ) {
        if (it->second == shapeTypeAsString)
        {
            shapeType = it->first;
            break;
        }
    }
    
    setAsActiveShapeWithId(shapeId, shapeType);
    
    _selectedShapeId = shapeId;
    _selectedShapeChanged = true;
}


//--------------------------------------------------------------
void ofxMtlMapping2DControls::addShapeToList(int shapeID, int shapeType)
{
    shapeCounter++;
    _shapesListCanvas->addWidgetDown(new ofxUIToggle(("Shape " + ofToString(shapeID) + " " + shapeTypesAsString.find((ofxMtlMapping2DShapeType)shapeType)->second), false, kToggleSize, kToggleSize));

    resizeShapeList();
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::clearShapesList()
{
    _shapesListCanvas->removeWidgets();
    _shapesListCanvas->resetPlacer();
    resizeShapeList();
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::refreshShapesListForMappingMode(ofxMtlMapping2DMode mappingMode)
{
    clearShapesList();
    
    // Re populate the UI List
    ofxMtlMapping2DShapes::pmShapes.sort(Comparator());

    list<ofxMtlMapping2DShape*>::reverse_iterator it;
    for (it=ofxMtlMapping2DShapes::pmShapes.rbegin(); it!=ofxMtlMapping2DShapes::pmShapes.rend(); it++) {
        ofxMtlMapping2DShape* shape = *it;
        
        if (mappingMode == MAPPING_MODE_OUTPUT || (mappingMode == MAPPING_MODE_INPUT && shape->shapeType != MAPPING_2D_SHAPE_MASK)) {
            ofxMtlMapping2DControls::mapping2DControls()->addShapeToList(shape->shapeId, shape->shapeType);
        }
    }
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::resizeShapeList()
{
    _shapesListCanvas->autoSizeToFitWidgets();
    _shapesListCanvas->getRect()->setY(.0f);
    _shapesListCanvas->getRect()->setWidth(kControlsMappingShapesListPanelWidth);
    
    float listHeight = _shapesListCanvas->getRect()->height;
    if(listHeight < ofGetHeight()) {
        _shapesListCanvas->getRect()->setHeight(ofGetHeight());
    } else {
        _shapesListCanvas->getRect()->setHeight(listHeight + kBottomSpacerHeight);
    }
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::setAsActiveShapeWithId(int shapeID, int shapeType)
{    
    // ----
    for (int i=0; i < _shapesListCanvas->getWidgetsOfType(OFX_UI_WIDGET_TOGGLE).size(); i++) {
        ofxUIToggle * shapeToggle = (ofxUIToggle *)_shapesListCanvas->getWidgetsOfType(OFX_UI_WIDGET_TOGGLE)[i];
        if ( shapeToggle->getName() == ("Shape " + ofToString(shapeID) + " " + shapeTypesAsString.find((ofxMtlMapping2DShapeType)shapeType)->second) ) {
            shapeToggle->setValue(true);
        } else {
            shapeToggle->setValue(false);
        }
    }
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::unselectShapesToggles()
{
    for (int i=0; i < _shapesListCanvas->getWidgetsOfType(OFX_UI_WIDGET_TOGGLE).size(); i++) {
        ofxUIToggle * shapeToggle = (ofxUIToggle *)_shapesListCanvas->getWidgetsOfType(OFX_UI_WIDGET_TOGGLE)[i];
        shapeToggle->setValue(false);
    }
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::windowResized()
{
    _toolsCanvas->setHeight(ofGetHeight());
    _gridSettingsCanvas->setPosition(_toolsCanvas->getRect()->width, ofGetHeight() - 90);
}


#pragma mark -
#pragma mark Grid settings

//--------------------------------------------------------------
void ofxMtlMapping2DControls::gridSettingsListUiEvent(ofxUIEventArgs &event)
{
    if(ofxMtlMapping2DShape::activeShape) {
        if (ofxMtlMapping2DShape::activeShape->shapeType == MAPPING_2D_SHAPE_GRID) {
            ((ofxMtlMapping2DGrid*)ofxMtlMapping2DShape::activeShape)->updateGrid();
        }
    }
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::showGridSettingsCanvas()
{
    if(isEnabled() && ofxMtlMapping2DShape::activeShape) {
        if (ofxMtlMapping2DShape::activeShape->shapeType == MAPPING_2D_SHAPE_GRID) {
            _gridSettingsCanvas->removeWidgets();
            _gridSettingsCanvas->resetPlacer();
            
            ofxUISlider *nSlider;
            _gridSettingsCanvas->addLabel("GRID SETTINGS");
            nSlider = _gridSettingsCanvas->addSlider("NB COLS", 1.0, 20.0, &(((ofxMtlMapping2DGrid*)ofxMtlMapping2DShape::activeShape)->gridNbCols));
            nSlider->setIncrement(1.0f);
            nSlider = _gridSettingsCanvas->addSlider("NB ROWS", 1.0, 20.0, &(((ofxMtlMapping2DGrid*)ofxMtlMapping2DShape::activeShape)->gridNbRows));
            nSlider->setIncrement(1.0f);
             
            _shapesListCanvas->autoSizeToFitWidgets();

            _gridSettingsCanvas->enable();
        }
    }
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::hideGridSettingsCanvas()
{
    _gridSettingsCanvas->disable();
}


#pragma mark -
#pragma mark Reset widgets
//--------------------------------------------------------------
void ofxMtlMapping2DControls::resetSaveMapping()
{
    _saveMapping = false;
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::resetLoadMapping()
{
    _loadMapping = false;
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::resetCreateNewShape()
{
    _createNewQuad = false;
    ((ofxUIToggle *)_toolsCanvas->getWidget(kSettingMappingCreateNewQuad))->setValue(false);

    //_createNewEllipse = false;
    //((ofxUIToggle *)_toolsCanvas->getWidget(kSettingMappingCreateNewEllipse))->setValue(false);
    
    _createNewGrid = false;
    ((ofxUIToggle *)_toolsCanvas->getWidget(kSettingMappingCreateNewGrid))->setValue(false);
    
    _createNewTriangle = false;
    ((ofxUIToggle *)_toolsCanvas->getWidget(kSettingMappingCreateNewTriangle))->setValue(false);
    
    _createNewMask = false;
    ((ofxUIToggle *)_toolsCanvas->getWidget(kSettingMappingCreateNewMask))->setValue(false);
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::resetMappingChangedFlag()
{
    _mappingModeChanged = false;
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::resetSelectedShapeChangedFlag()
{
    _selectedShapeChanged = false;
}

#pragma mark -
#pragma mark Interface Methods
//--------------------------------------------------------------
bool ofxMtlMapping2DControls::getToggleValue(const string& name)
{
    return ((ofxUIToggle *)_toolsCanvas->getWidget(name))->getValue();
}

//--------------------------------------------------------------
float ofxMtlMapping2DControls::getSliderValue(const string& name)
{
    return ((ofxUISlider *)_toolsCanvas->getWidget(name))->getScaledValue();
}

//--------------------------------------------------------------
ofPoint ofxMtlMapping2DControls::get2DPadValue(const string& name)
{
    return ((ofxUI2DPad *)_toolsCanvas->getWidget(name))->getScaledValue();
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::enable()
{
    _toolsCanvas->enable();
    _shapesListCanvas->enable();
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::disable()
{
    _toolsCanvas->disable();
    _shapesListCanvas->disable();
    _gridSettingsCanvas->disable();
}

//--------------------------------------------------------------
void ofxMtlMapping2DControls::toggle()
{
    _toolsCanvas->toggleVisible();
    
    if (_toolsCanvas->isVisible() && _editShapes) {
        _shapesListCanvas->enable();
        showGridSettingsCanvas();
    } else {
        _shapesListCanvas->disable();
        hideGridSettingsCanvas();
    }
}

//--------------------------------------------------------------
bool ofxMtlMapping2DControls::isEnabled()
{
    return _toolsCanvas->isEnabled();
}

//--------------------------------------------------------------
bool ofxMtlMapping2DControls::isHit(int x, int y) {
    if (_toolsCanvas->isHit(x, y) || _shapesListCanvas->isHit(x, y) || _gridSettingsCanvas->isHit(x, y)) {
        return true;
    } else {
        return false;
    }
}


