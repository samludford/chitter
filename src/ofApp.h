#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "Module.h"

#define PLANETS 8
#define RAD_OFFSET 3
#define PEOPLE 8
#define PERSON_SIZE 15


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // Audio output and input methods
    
        void audioOut(float * output, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);
     
    
    int		bufferSize; /* buffer size */
    int		sampleRate;
    
    double left;
    double right;
    double stereoOut[2];
    maxiMix mixer;
    
    // drawing
    
    vector<Module*> modules;
    
    float distance_from_center(ofPoint pos);
    void set_focus();
    
    bool focused {false};
    ofPoint focus_offset;
    
    
};
