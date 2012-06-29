//
//  graphic.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 6/28/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include "graphic.h"
#include "ofMain.h"

Graphic::Graphic() {
    x = 0;
    y = 0;
    rot = 0;
}

Graphic::~Graphic() {
    
}

Graphic *Graphic::add_child(Graphic *new_child) {
    children.push_back(new_child);
}

void Graphic::Render() {
    PreDraw();
    Draw();
    PostDraw();
}

void Graphic::PreDraw() {
    ofPushMatrix();
    ofTranslate(x, y);
    ofRotate(rot);
}

void Graphic::Draw() {

}

void Graphic::PostDraw() {
    for (draw_iter = children.begin(); draw_iter != children.end(); ++draw_iter) {
        (*draw_iter)->Render();
    }
    ofPopMatrix();
}

void Graphic::position(float x, float y) {
    this->x = x;
    this->y = y;
}

void Graphic::rotation(float rot) {
    this->rot = rot;
}
