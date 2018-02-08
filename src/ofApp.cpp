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
    
    float spacing = ofGetWidth() / person_count;
    float start_x = spacing / 2.0;
    for(int i=0 ; i <person_count ; i++) {
        people.push_back(ofPoint(start_x + i*spacing, ofGetHeight()/2.0));
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i=0 ; i < people.size() ; i++) {
        draw_person(people[i]);
    }
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
//        currentCount += (int) clock.phasor(tempo);
        wave = 0.0;

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
        people[people.size()-1] = ofPoint(x,y) - focus_offset;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofPoint mouse_pos = ofPoint(x,y);
    int focus = -1;
    // cycle backwards to pick up top elements first
    for(int i=people.size()-1 ; i >= 0 ; i--) {
        ofPoint delta = mouse_pos - people[i];
        float dist = sqrt(delta.x * delta.x + delta.y * delta.y);
        if(dist <= person_size) {
            focus = i;
            focus_offset = delta;
            break;
        }
    }
    if(focus >= 0) {
        ofPoint focused_person = people[focus];
        people.erase(people.begin() + focus);
        people.push_back(focused_person);
        focused = true;
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

void ofApp::draw_person(ofPoint pos) {
    
    ofPushStyle();
    ofSetColor(255,0,0, 255);
    ofFill();
    ofDrawCircle(pos.x, pos.y, person_size);
    ofSetColor(0, 255);
    ofNoFill();
    ofDrawCircle(pos.x, pos.y, person_size);
    ofPopStyle();
    
}

float ofApp::distance_from_center(ofPoint pos) {
    ofPoint delta = pos - ofPoint(ofGetWidth()/2.0, ofGetHeight()/2.0);
    return sqrt(delta.x * delta.x + delta.y * delta.y);
}


