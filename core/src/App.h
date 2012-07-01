#pragma once

#include <string>

#include "ofMain.h"
#include "lua/lua_wrapper.h"
#include "util/logging.h"

#include "graphic.h"
#include "text.h"

class App : public ofBaseApp{
private:
    glomp::lua::LuaWrapper lua_wrap;
    glomp::util::Logger logger;
    
    std::string internal_data_folder;
    std::string external_data_folder;
    
    ofTrueTypeFont	console_font;
    std::string console_output;
    
    glomp::graphics::Graphic root_graphic;
    glomp::graphics::Text log_line;
    
public:
    void setup();
    void exit();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
