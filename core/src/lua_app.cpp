//
//  lua_app.cpp
//  glOMP
//
//  Created by Jeffrey Graves on 7/1/12.
//  Copyright (c) 2012 Decultured. All rights reserved.
//

#include <iostream>
#include <string>
#include "lua_wrapper.h"
#include "lua_print.h"
#include "lua_graphic.h"
#include "lua_app.h"
#include "lua_graphics.h"
#include "lua_font.h"

namespace glomp {

    static int l_terminate(lua_State* L) {
        std::exit(EXIT_SUCCESS);
        return 0;
    }    
        
    static const struct luaL_reg glomp_app [] = {
        {"__glomp_terminate", l_terminate},
        {NULL, NULL}
    };    
        
    extern int luaopen_app(lua_State *L) {
        lua_getglobal(L, "_G");
        luaL_register(L, NULL, glomp_app);
        lua_pop(L, 1);
    }    
    
    LuaApp::LuaApp() : LuaWrapper() {
    }
    
    LuaApp::~LuaApp() {
        shutdown();
    }
    
    void LuaApp::init() {
        LuaWrapper::init();
        luaopen_app(L);
        luaopen_graphics(L);
        luaopen_font(L);
    }
    
    void LuaApp::shutdown() {
        LuaWrapper::shutdown();
    }
    
    void LuaApp::keyPressed(int key){
        lua_getglobal(L, "_glomp_key_pressed");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, key);
        
        if (lua_pcall(L, 1, 0, 0) != 0) {
            report_errors(L, "_glomp_key_pressed");
            return;
        }
    }
    
    void LuaApp::keyReleased(int key){
        lua_getglobal(L, "_glomp_key_released");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, key);
        
        if (lua_pcall(L, 1, 0, 0) != 0) {
            report_errors(L, "_glomp_key_released");
            return;
        }
    }
    
    void LuaApp::mouseMoved(int x, int y){
        lua_getglobal(L, "_glomp_mouse_moved");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);
        
        if (lua_pcall(L, 2, 0, 0) != 0) {
            report_errors(L, "_glomp_mouse_moved");
            return;
        }
    }
    
    void LuaApp::mouseDragged(int x, int y, int button){
        lua_getglobal(L, "_glomp_mouse_dragged");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);
        lua_pushnumber(L, button);
        
        if (lua_pcall(L, 3, 0, 0) != 0) {
            report_errors(L, "_glomp_mouse_dragged");
            return;
        }
    }
    
    void LuaApp::mousePressed(int x, int y, int button){
        lua_getglobal(L, "_glomp_mouse_pressed");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);
        lua_pushnumber(L, button);
        
        if (lua_pcall(L, 3, 0, 0) != 0) {
            report_errors(L, "_glomp_mouse_pressed");
            return;
        }
    }
    
    void LuaApp::mouseReleased(int x, int y, int button){
        lua_getglobal(L, "_glomp_mouse_released");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, x);
        lua_pushnumber(L, y);
        lua_pushnumber(L, button);
        
        if (lua_pcall(L, 3, 0, 0) != 0) {
            report_errors(L, "_glomp_mouse_released");
            return;
        }
    }
    
    void LuaApp::windowResized(int w, int h){
        lua_getglobal(L, "_glomp_window_resized");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, w);
        lua_pushnumber(L, h);
        
        if (lua_pcall(L, 2, 0, 0) != 0) {
            report_errors(L, "_glomp_window_resized");
            return;
        }
    }
    
    void LuaApp::draw() {
        lua_getglobal(L, "_glomp_draw");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        if (lua_pcall(L, 0, 0, 0) != 0) {
            report_errors(L, "_glomp_draw");
            return;
        }
    }
    
    void LuaApp::windowEntry(int state) {
        lua_getglobal(L, "_glomp_window_entry");
        if(!lua_isfunction(L,-1)) {
            lua_pop(L,1);
            return;
        }
        
        lua_pushnumber(L, state);
        
        if (lua_pcall(L, 1, 0, 0) != 0) {
            report_errors(L, "_glomp_window_entry");
            return;
        }
    }
    
}