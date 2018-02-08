//
//  Module.h
//  chitter
//
//  Created by Sam Ludford on 08/02/2018.
//

#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

class Module {
    
    public:
    
        float rad {20.0};
    
        Module(ofPoint _pos);

        void draw();
        void update();
        void setPosition(ofPoint _pos);
        ofPoint getPosition();
    
        void setFocused(bool _focused);
    
        // audio
    
        double signal();
        int currentCount {0};
        int lastCount;
        maxiOsc clock;
        maxiSample sample;
        double tempo;
        bool trigger;
    
    
    private:
    
        ofPoint pos;
        bool focused {false};
    
};
