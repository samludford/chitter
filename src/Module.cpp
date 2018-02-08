//
//  Module.cpp
//  chitter
//
//  Created by Sam Ludford on 08/02/2018.
//

#include "Module.h"

Module::Module(ofPoint _pos) {
    pos = _pos;
}

void Module::draw() {
    ofPushStyle();
    ofSetColor(255,0,0, 255);
    ofFill();
    ofDrawCircle(pos.x, pos.y, rad);
    ofSetColor(0, 255);
    ofNoFill();
    ofDrawCircle(pos.x, pos.y, rad);
    ofPopStyle();
}

void Module::update() {
    
}

void Module::setPosition(ofPoint _pos) {
    pos = _pos;
}

ofPoint Module::getPosition() {
    return pos;
}

