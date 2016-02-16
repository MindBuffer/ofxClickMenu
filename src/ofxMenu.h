//
//  ofxMenu.h
//  ofxClickDownMenu_example
//
//  Created by Joshua Batty on 29/06/2015.
//
//

#pragma once
#include "ofMain.h"
#include "ModulatorState.h"

enum ElementKind {
    MENU,
    BUTTON,
};

class MenuEvent {
public:
    MenuEvent(vector<int> _indexTree): indexTree(_indexTree){}
    vector<int> indexTree;
};

class MenuElement{
public:
    MenuElement(ElementKind _kind, string _name);
    
    void fillIndexTree(vector<int>* indexTree);
    vector<int> getIndexTree();
    
    ElementKind kind;
    string name;
    bool isHighlighted;
    
    // These will always be ofxMenus, but we can't do that because c++ is ok.
    MenuElement* topParent;
    MenuElement* parent;
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
    
    void cloneFrom(const ofxMenu& other);
    
    void clearButtons();
    void addButton(string name);
    ofxMenu* addMenu(string name);
    void update();
    void draw();
    void drawWithData(ModulatorState& modulatorState);
    void drawWithDataRecursive(ModulatorState &modulatorState, vector<int>* indexTree);
    void drawBox(MenuElement* elem, int elemX, int elemY);
    void drawName(MenuElement* elem, int elemX, int elemY);
    
    void openByClick(int x, int y);
    void getSelected();
    
    
    int sizeOfMenuAtIndexTree(vector<int>& indexTree);
    MenuElement* elemAtIndexTree(vector<int>& indexTree);
    string* nameAtIndexTree(vector<int>& indexTree);
    vector<vector<int> > indexTreeForEveryButtonInMenu(vector<int>& indexTree);
    void fillWithIndexTreeForEveryButtonInMenu(vector<vector<int> >& indexTrees);
    
    MenuEvent genRandomIndexTree();
    void genRandomIndexTreeRecursive(string& name, vector<int>& indexTree);
    
    //Mouse & Key Events
    void mousePressed(ofMouseEventArgs& mouse){}
    void mouseDragged(ofMouseEventArgs& mouse){}
    void mouseMoved(ofMouseEventArgs& mouse);
    void mouseReleased(ofMouseEventArgs& mouse);
    void mouseScrolled(ofMouseEventArgs& mouse){}
    
    // Unhighlight and close all children elements.
    void closeChildren();
    void setHighlighted(int mouseX, int mouseY);
    void setPosition(int x, int y);
    bool isOverRect(int rectX, int rectY, int rectW, int rectH, int x, int y);
    int getChildOffset();
    
    // Event for menu selection
    ofEvent<MenuEvent> selectedElement;

    vector<MenuElement*> elements;
    
private:
    const int WIDTH = 100;
    const int HEIGHT = 20;
    const int TEXT_PAD_WIDTH = 10;
    const int TEXT_PAD_HEIGHT = 14;
    
    ofTrueTypeFont font;
    string highlightedName;
    ofPoint pos;
    bool bIsOpen;
    
};