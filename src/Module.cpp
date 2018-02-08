//
//  Module.cpp
//  chitter
//
//  Created by Sam Ludford on 08/02/2018.
//

#include "Module.h"

Module::Module(ofPoint _pos) {
    pos = _pos;
    
    // audio setup
    tempo = ofMap(pos.x, 0, ofGetWidth(), 2, 2.1);
    
    // load sample
    sample.load(ofToDataPath("k.wav"));
}

void Module::drawCrosshair() {
    ofPushStyle();
    ofSetColor(255, 30);
    ofDrawLine(0,pos.y,ofGetWidth(),pos.y);
    ofDrawLine(pos.x,0,pos.x,ofGetHeight());
    ofPopStyle();
}

void Module::drawRings() {
    ofPushStyle();
    ofNoFill();
    for(int i=0 ; i < rings.size() ; i++) {
        float alpha = ofMap(i, 0, MAX_RINGS, 255, 0);
        ofSetColor(255, alpha);
        ofDrawCircle(pos.x, pos.y, rings[i]);
    }
    ofPopStyle();
}

void Module::draw() {
    ofPushStyle();
    
    if(focused) {
        ofSetColor(255,0,0, 255);
    } else {
        ofSetColor(255,0,0, 180);
    }
    
    ofFill();
    ofDrawCircle(pos.x, pos.y, rad);
    ofSetColor(0, 255);
    ofNoFill();
    ofDrawCircle(pos.x, pos.y, rad);
    ofPopStyle();
}

void Module::update() {
    for(int i=0 ; i < rings.size() ; i++) {
        rings[i] += RING_INC;
    }
}

void Module::setPosition(ofPoint _pos) {
    pos = _pos;
}

ofPoint Module::getPosition() {
    return pos;
}

void Module::setFocused(bool _focused) {
    focused = _focused;
}

// Sound

double Module::signal() {
    currentCount = (int) clock.phasor(tempo);
    if(lastCount != currentCount) {
        // also add ring
        rings.push_front(rad);
        if(rings.size()>MAX_RINGS) {
            rings.pop_back();
        }
        sample.trigger();
        lastCount = 0;
    }
    return sample.playOnce();
}

