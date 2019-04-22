ofxMtlMapping2D
=====================================

MODDED FORK

Switched view to both separate INOUT & OUTPUT mode at the same time (MapMap or MadMapper style).
Using ofxInfiniteCanvas addon for draggable&zooming areas
Using ofxFontStash for correctly render fonts with zoom

![MapMap mode](https://raw.githubusercontent.com/d3cod3/ofxMtlMapping2D/master/capture.png)

Introduction
------------
C++ openFrameworks addon to achieve 2D projection-mapping of textures to physical objects. Each instance of ofxMtlMapping2D has its own FBO to draw content into. Each created shape has an output polygon used for mapping, and an input polygon defining the texture coordinates to be used.

Licence
-------
The code in this repository is available under the [MIT License](https://en.wikipedia.org/wiki/MIT_License)  
Copyright (c) 2013 Hugues Bruyère, Elie Zananiri, [www.morethanlogic.com](http://www.morethanlogic.com) | [www.departement.ca](http://www.departement.ca)    
More Than Logic

Installation
------------
Copy to your openFrameworks/addons folder.

Dependencies
------------
* [ofxFontStash](https://github.com/d3cod3/ofxFontStash)
* [ofxInfiniteCanvas](https://github.com/d3cod3/ofxInfiniteCanvas)
* ofxXmlSettings
* homography.h by Arturo Castro (included in this repo)

Compatibility
------------
OF 10.0.1
