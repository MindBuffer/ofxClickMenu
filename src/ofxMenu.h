//
//  ofxMenu.h
//  ofxClickDownMenu_example
//
//  Created by Joshua Batty on 29/06/2015.
//
//

#pragma once
#include "ofMain.h"

enum ElementKind {
    MENU,
    BUTTON,
};


class MenuElement{
public:
    MenuElement(ElementKind _kind, string _name): kind(_kind), name(_name), isHighlighted(false){}
    ElementKind kind;
    string name;
    bool isHighlighted;
};


class Button : public MenuElement {
public:
    Button(string name): MenuElement(BUTTON, name) {}
};


class ofxMenu : public MenuElement {
public:
    ~ofxMenu();
    ofxMenu(string name);
    ofxMenu(const ofxMenu& other);
    ofxMenu& operator=(const ofxMenu& other);
    
    void clone(const ofxMenu& other);
    
    void addButton(string name);
    void addMenu(ofxMenu menu);
    void update();
    void draw();
    void openByClick(int x, int y);

    //Mouse & Key Events
    void mousePressed(ofMouseEventArgs& mouse){}
    void mouseDragged(ofMouseEventArgs& mouse){}
    void mouseMoved(ofMouseEventArgs& mouse);
    void mouseReleased(ofMouseEventArgs& mouse){}
    void mouseScrolled(ofMouseEventArgs& mouse){}
    void keyPressed(ofKeyEventArgs  &key){}
    void keyReleased(ofKeyEventArgs &key){}
    
    // Unhighlight and close all children elements.
    void closeChildren();
    void setHighlighted(int mouseX, int mouseY);
    void setPosition(int x, int y);
    bool isOverRect(int rectX, int rectY, int rectW, int rectH, int x, int y);

private:
    const int WIDTH = 100;
    const int HEIGHT = 20;
    const int TEXT_PAD_WIDTH = 10;
    const int TEXT_PAD_HEIGHT = 14;
    
    ofTrueTypeFont font;
    string highlightedName;
    ofPoint pos;
    bool bIsOpen;

    vector<MenuElement*> elements;
};
