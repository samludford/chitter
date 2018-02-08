//
//  Module.h
//  chitter
//
//  Created by Sam Ludford on 08/02/2018.
//

#pragma once

#include "ofMain.h"

class Module {
    
    public:
    
        float rad {20.0};
    
        Module(ofPoint _pos);

        void draw();
        void update();
        void setPosition(ofPoint _pos);
        ofPoint getPosition();
    
    private:
    
        ofPoint pos;
    
};
