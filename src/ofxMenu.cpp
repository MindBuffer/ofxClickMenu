//
//  ofxMenu.cpp
//  ofxClickDownMenu_example
//
//  Created by Joshua Batty on 29/06/2015.
//
//

#include "ofxMenu.h"

//-----------------------------------------
ofxMenu::~ofxMenu(){
    ofUnregisterMouseEvents(this);
    ofUnregisterKeyEvents(this);

    for(vector<MenuElement*>::iterator it = elements.begin(); it != elements.end(); it++){
        delete (*it);
        *it = NULL;
    }
}

//-----------------------------------------
ofxMenu::ofxMenu(string name): MenuElement(MENU, name), bIsOpen(false) {
//    font.loadFont("BebasNeue.TTF", 10);
    font.loadFont("HelveticaNeue.ttf", 10);
    bIsOpen = false;
    highlightedName = "NONE";
    pos = ofPoint(0,0);
    
    ofRegisterMouseEvents(this);
    ofRegisterKeyEvents(this);
    
    cout << "isOpen = " << bIsOpen << endl;
}

//-----------------------------------------
ofxMenu::ofxMenu(const ofxMenu& other): MenuElement(MENU, other.name),
font(other.font),
highlightedName(other.highlightedName),
pos(other.pos),
bIsOpen(false)
{
    for(vector<MenuElement*>::const_iterator it = other.elements.begin(); it != other.elements.end(); it++){
        switch ((*it)->kind) {
            case MENU: {
                // Cast MenuElement ptr to ofxMenu ptr.
                ofxMenu* menuPtr = (ofxMenu*)(*it);
                elements.push_back((MenuElement*)new ofxMenu(*menuPtr));
                break;
            }
            case BUTTON: {
                // Cast MenuElement ptr to Button ptr.
                Button* buttonPtr = (Button*)(*it);
                elements.push_back((MenuElement*)new Button(*buttonPtr));
                break;
            }
            default:
                break;
        }
        
    }
    ofRegisterMouseEvents(this);
    ofRegisterKeyEvents(this);

}

//-----------------------------------------
void ofxMenu::addButton(string name){
    this->elements.push_back((MenuElement*) new Button(name));
}

//-----------------------------------------
void ofxMenu::addMenu(ofxMenu menu){
    this->elements.push_back((MenuElement*) new ofxMenu(menu));
}

//-----------------------------------------
void ofxMenu::update(){
    
}

//-----------------------------------------
void ofxMenu::draw(){
    
    // If the menu is open, draw like this.
    if (bIsOpen) {
        
        int yOffset = 0;
        
        for(vector<MenuElement*>::iterator it = elements.begin(); it != elements.end(); it++){
            
            MenuElement* elem = (*it);
            int elemX = pos.x;
            int elemY = pos.y + yOffset;
            
            // Box That is the size of 1 element
            if(!elem->isHighlighted){
                ofSetColor(238, 237, 234);
            } else if(elem->isHighlighted==true){
                ofSetColor(0,100,255);
            }
            ofRect(elemX, elemY, WIDTH, HEIGHT);
            
            
            // Draw the name.
            ofSetColor(0);
            switch (elem->kind) {
                case MENU:
                    font.drawString(elem->name + " >", elemX + TEXT_PAD_WIDTH, elemY + TEXT_PAD_HEIGHT);
                    break;
                case BUTTON:
                    font.drawString(elem->name, elemX + TEXT_PAD_WIDTH, elemY + TEXT_PAD_HEIGHT);
                    break;
            }
            
            // Draw Divider Line
            ofSetColor(230,225,20);
            ofNoFill();
            ofRect(elemX, elemY, WIDTH, HEIGHT);
            ofFill();
            ofSetColor(255);
            
            // Draw the branch.
            switch (elem->kind) {
                case MENU: {
                    ofxMenu* menuPtr = (ofxMenu*)elem;
                    menuPtr->draw();
                    break;
                }
                default:
                    break;
            }
            
            
            yOffset += HEIGHT;
        }
        
    }
    
}

//-----------------------------------------
void ofxMenu::openByClick(int x, int y){
    cout << "openByClick " << x << y << endl;
    bIsOpen = true;
    this->setPosition(x, y);
}

//-----------------------------------------
void ofxMenu::setPosition(int x, int y) {
    pos.x = x;
    pos.y = y;
    
    int yOffset = 0;
    
    // Recursively set the position of all children menus.
    for(vector<MenuElement*>::iterator it = elements.begin(); it != elements.end(); it++){
        MenuElement* elem = (*it);
        
        if (elem->kind == MENU) {
            ofxMenu* menuPtr = (ofxMenu*)elem;
            menuPtr->setPosition(x + WIDTH, y + yOffset);
        }
        
        yOffset += HEIGHT;
    }
}

//-----------------------------------------
bool ofxMenu::isOverRect(int rectX, int rectY, int rectW, int rectH, int x, int y){
    return x < rectX + rectW && x > rectX
        && y < rectY + rectH && y > rectY;
}

//-----------------------------------------
void ofxMenu::closeChildren() {
    
    // Make sure all the children menus are closed.
    for (int i=0; i < elements.size(); i++) {
        MenuElement* elem = elements[i];
        
        elem->isHighlighted = false;
        
        // If over a menu, open the menu.
        if (elem->kind == MENU) {
            ofxMenu* menuPtr = (ofxMenu*)elem;
            menuPtr->bIsOpen = false;
            menuPtr->closeChildren();
        }
    }
}

//-----------------------------------------
void ofxMenu::setHighlighted(int mouseX, int mouseY){

    if(bIsOpen){
        
        int yOffset = 0;
        
        // Recursively set the highlighting for all child elements.
        for (int i=0; i < elements.size(); i++) {
            MenuElement* elem = elements[i];
            
            // Check if the mouse is over the child element.
            if(isOverRect(pos.x, pos.y + yOffset, WIDTH, HEIGHT, mouseX, mouseY)){
                elem->isHighlighted = true;
                
                // If over a menu, open the menu.
                if (elem->kind == MENU) {
                    ofxMenu* menuPtr = (ofxMenu*)elem;
                    menuPtr->bIsOpen = true;
                    
                    menuPtr->closeChildren();
                }
                
                // Check for menus at all other elements and set them to be closed.
                for (int j=0; j < elements.size(); j++) {
                    if (j != i) {
                        if (elements[j]->kind == MENU) {
                            ofxMenu* menuPtr = (ofxMenu*)elements[j];
                            menuPtr->bIsOpen = false;
                        }
                    }
                }
            } else {
                elem->isHighlighted = false;
            }
            
            yOffset += HEIGHT;
        }
    }
}

//-----------------------------------------
void ofxMenu::mouseMoved(ofMouseEventArgs &mouse){
    setHighlighted(mouse.x, mouse.y);
}




