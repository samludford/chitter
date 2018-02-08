/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    // audio setup
    sampleRate 	= 44100;
    bufferSize	= 512;
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
    // graphics setup
    
    ofBackground(0);
    ofSetColor(0);
    
    ofSetCircleResolution(100);
    
    float count = 8;
    float spacing = ofGetWidth() / count;
    float start_x = spacing / 2.0;
    for(int i=0 ; i <8 ; i++) {
        Module *m = new Module(ofPoint(start_x + i*spacing, ofGetHeight()/2.0));
        modules.push_back(m);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i=0 ; i < modules.size() ; i++) {
        modules[i]->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i=0 ; i < modules.size() ; i++) {
        modules[i]->draw();
    }
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
//        currentCount += (int) clock.phasor(tempo);
        wave = 0.0;
        
        for(int i=0 ; i < modules.size() ; i++) {
            wave += modules[i]->signal();
        }
        
        wave /= modules.size();

        output[i*nChannels    ] = wave;
        output[i*nChannels + 1] = wave;

    }
    
}

// remove - not needed
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'a') {
        Module *m = new Module(ofPoint(ofGetWidth()/2.0, ofGetHeight()/2.0));
        modules.push_back(m);
    } else if (key == 's') {
        if(modules.size() > 0 ) {
            modules.pop_back();
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(focused) {
        Module *m = modules[modules.size()-1];
        m->setPosition(ofPoint(x,y) - focus_offset);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofPoint mouse_pos = ofPoint(x,y);
    int focus = -1;
    // cycle backwards to pick up top elements first
    for(int i=modules.size()-1 ; i >= 0 ; i--) {
        Module *m = modules[i];
        ofPoint delta = mouse_pos - m->getPosition();
        float dist = sqrt(delta.x * delta.x + delta.y * delta.y);
        if(dist <= m->rad) {
            focus = i;
            focus_offset = delta;
            break;
        }
    }
    if(focus >= 0) {
        Module *focused_module = modules[focus];
        modules.erase(modules.begin() + focus);
        modules.push_back(focused_module);
        focused = true;
        set_focus();
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    focused = false;
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

// utilities

float ofApp::distance_from_center(ofPoint pos) {
    ofPoint delta = pos - ofPoint(ofGetWidth()/2.0, ofGetHeight()/2.0);
    return sqrt(delta.x * delta.x + delta.y * delta.y);
}

void ofApp::set_focus() {
    for(int i=0 ; i < modules.size() ; i++) {
        modules[i]->setFocused(i==modules.size()-1);
    }
}


