//
//  ofxMenu.cpp
//  ofxClickDownMenu_example
//
//  Created by Joshua Batty on 29/06/2015.
//
//

#include "ofxMenu.h"

//-----------------------------------------
MenuElement::MenuElement(ElementKind _kind, string _name):
kind(_kind),
name(_name),
isHighlighted(false) {
    topParent = this;
    parent = NULL;
}


//-----------------------------------------
// Construct the index tree by checking our index within our parent's elements vector.
void MenuElement::fillIndexTree(vector<int>* indexTree) {
    if (this->topParent != this) {
        ofxMenu* parentMenu = (ofxMenu*) parent;
        for (int i=0; i < parentMenu->elements.size(); i++) {
            if (parentMenu->elements[i]->name == this->name) {
                indexTree->push_back(i);
                parentMenu->fillIndexTree(indexTree);
            }
        }
    }
}

//-----------------------------------------
// Return the index tree of our position within the topParent's menus.
vector<int> MenuElement::getIndexTree() {
    vector<int> indexTree;
    indexTree.reserve(16);
    fillIndexTree(&indexTree);
    std::reverse(indexTree.begin(), indexTree.end());
    return indexTree;
}







//-----------------------------------------
ofxMenu::~ofxMenu(){
    ofUnregisterMouseEvents(this);
    
    for(vector<MenuElement*>::iterator it = elements.begin(); it != elements.end(); it++){
        delete (*it);
        *it = NULL;
    }
}

//-----------------------------------------
ofxMenu::ofxMenu(string name): MenuElement(MENU, name), bIsOpen(false) {
    font.loadFont("Fonts/HelveticaNeue.ttf", 10);
    bIsOpen = false;
    highlightedName = "NONE";
    pos = ofPoint(0,0);
    topParent = this;
    parent = NULL;
    
    ofRegisterMouseEvents(this);
}

//-----------------------------------------
ofxMenu::ofxMenu(const ofxMenu& other): MenuElement(MENU, other.name)
{
    this->cloneFrom(other);
}

//-----------------------------------------
ofxMenu& ofxMenu::operator=(const ofxMenu& other)
{
    this->cloneFrom(other);
    return *this;
}

//-----------------------------------------
void ofxMenu::cloneFrom(const ofxMenu& other)
{
    // Copy stack based data by assignment.
    this->font = other.font;
    this->highlightedName = other.highlightedName;
    this->pos = other.pos;
    this->bIsOpen = other.bIsOpen;
    this->topParent = other.topParent;
    this->parent = other.parent;
    
    // Reserve room in the vector.
    this->elements.reserve(other.elements.size());
    
    // Deep copy heap allocated menu itmes.
    for(vector<MenuElement*>::const_iterator it = other.elements.begin(); it != other.elements.end(); it++){
        switch ((*it)->kind) {
            case MENU: {
                // Cast MenuElement ptr to ofxMenu ptr.
                ofxMenu* menuPtr = (ofxMenu*)(*it);
                this->elements.push_back((MenuElement*)new ofxMenu(*menuPtr));
                break;
            }
            case BUTTON: {
                // Cast MenuElement ptr to Button ptr.
                Button* buttonPtr = (Button*)(*it);
                this->elements.push_back((MenuElement*)new Button(*buttonPtr));
                break;
            }
            default:
                break;
        }
    }
    
    // Register unique mouse and key events for this new menu.
    ofRegisterMouseEvents(this);
}

//-----------------------------------------
void ofxMenu::clearButtons(){
    this->elements.clear();
}

//-----------------------------------------
void ofxMenu::addButton(string name){
    Button* newButton = new Button(name);
    newButton->topParent = this->topParent;
    newButton->parent = this;
    this->elements.push_back((MenuElement*)newButton);
}

//-----------------------------------------
ofxMenu* ofxMenu::addMenu(string name){
    ofxMenu* newMenu = new ofxMenu(name);
    newMenu->topParent = this->topParent;
    newMenu->parent = this;
    this->elements.push_back((MenuElement*)newMenu);
    return newMenu;
}

//-----------------------------------------
string* ofxMenu::nameAtIndexTree(vector<int>& indexTree){
    assert(indexTree.size() != 0);
    MenuElement* elem = elemAtIndexTree(indexTree);
    if (elem->kind == BUTTON) {
        return &elem->name;
    } else {
        return NULL;
    }
}

//-----------------------------------------
vector<vector<int> > ofxMenu::indexTreeForEveryButtonInMenu(vector<int>& indexTree) {
    MenuElement* elem = elemAtIndexTree(indexTree);
    assert(elem->kind == MENU);
    ofxMenu* menu = (ofxMenu*) elem;
    vector<vector<int> > indexTrees;
    indexTrees.reserve(64);
    menu->fillWithIndexTreeForEveryButtonInMenu(indexTrees);
    return indexTrees;
}

//-----------------------------------------
void ofxMenu::fillWithIndexTreeForEveryButtonInMenu(vector<vector<int> >& indexTrees) {
    for (int i=0; i < elements.size(); i++) {
        MenuElement* elem = elements[i];
        if (elem->kind == BUTTON) {
            indexTrees.push_back(elem->getIndexTree());
        }
        if (elem->kind == MENU) {
            ofxMenu* menu = (ofxMenu*)elem;
            menu->fillWithIndexTreeForEveryButtonInMenu(indexTrees);
        }
    }
}

//-----------------------------------------
MenuElement* ofxMenu::elemAtIndexTree(vector<int> &indexTree){
    ofxMenu* currentMenu = this;
    for (int i=0; i < indexTree.size(); i++) {
        
        // If at our last branch, we can return the elem.
        if (i == indexTree.size()-1) {
            return currentMenu->elements[indexTree[i]];
        }
        // Otherwise, set the menu at i as our currentMenu.
        currentMenu = (ofxMenu*)currentMenu->elements[indexTree[i]];
    }
    return (MenuElement*)currentMenu;
}

//-----------------------------------------
int ofxMenu::sizeOfMenuAtIndexTree(vector<int>& indexTree){
    MenuElement* elem = elemAtIndexTree(indexTree);
    assert(elem->kind == MENU);
    ofxMenu* menu = (ofxMenu*) elem;
    return menu->elements.size();
}

//-----------------------------------------
void ofxMenu::update(){

}

//-----------------------------------------
void ofxMenu::drawBox(MenuElement* elem, int elemX, int elemY){
    // Box That is the size of 1 element
    if(!elem->isHighlighted){
        ofSetColor(238, 237, 234);
    } else if(elem->isHighlighted==true){
        ofSetColor(0,100,255);
    }
    ofRect(elemX, elemY, WIDTH, HEIGHT);
    
    // Draw Divider Line
    ofSetColor(230,225,20);
    ofNoFill();
    ofRect(elemX, elemY, WIDTH, HEIGHT);
    ofFill();
    ofSetColor(255);
}

//-----------------------------------------
void ofxMenu::drawName(MenuElement* elem, int elemX, int elemY){
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
}

//-----------------------------------------
void ofxMenu::drawWithData(ModulatorState &modulatorState){
    
    vector<int> indexTree;
    indexTree.reserve(16);
    drawWithDataRecursive(modulatorState, &indexTree);
}

//-----------------------------------------
void ofxMenu::drawWithDataRecursive(ModulatorState &modulatorState, vector<int>* indexTree) {
    // If the menu is open, draw like this.
    if (bIsOpen) {
        
        int yOffset = 0;
        int offsetAmount = getChildOffset();
        
        for(int i = 0; i < elements.size(); i++){
            indexTree->push_back(i);
            
            MenuElement* elem = elements.at(i);
            int elemX = pos.x;
            int elemY = pos.y + yOffset;
            // Draw out Element Box
            drawBox(elem, elemX, elemY);
            
            if(elem->kind == BUTTON){
                
                // Draw Incoming Moudalator Data in the MenuElement
                ofSetColor(68,138,185,140);
                
                float modValue = modulatorState.paramAtIndexTree(indexTree);
                ofRect(elemX, elemY, modValue*WIDTH, HEIGHT);
            }
            // Draw Name of Element
            drawName(elem, elemX, elemY);
            
            // Draw the branch.
            if(elem->kind == MENU){
                ofxMenu* menuPtr = (ofxMenu*)elem;
                menuPtr->drawWithDataRecursive(modulatorState, indexTree);
            }
            yOffset += offsetAmount;
            
            indexTree->pop_back();
        }
    }
}

//-----------------------------------------
void ofxMenu::draw(){
    
    // If the menu is open, draw like this.
    if (bIsOpen) {
        
        int yOffset = 0;
        int offsetAmount = getChildOffset();
        
        for(vector<MenuElement*>::iterator it = elements.begin(); it != elements.end(); it++){
            
            MenuElement* elem = (*it);
            int elemX = pos.x;
            int elemY = pos.y + yOffset;
            
            // Draw out Element Box
            drawBox(elem, elemX, elemY);

            // Draw Name of Element
            drawName(elem, elemX, elemY);
            
            // Draw the branch.
            if(elem->kind == MENU){
                ofxMenu* menuPtr = (ofxMenu*)elem;
                menuPtr->draw();
            }
            yOffset += offsetAmount;
        }
    }
}
//-----------------------------------------
void ofxMenu::openByClick(int x, int y){
    if(bIsOpen == false){
        bIsOpen = true;
        this->setPosition(x, y);
    }
}

//-----------------------------------------
void ofxMenu::getSelected(){
    if(bIsOpen == true){
        for(int i=0; i < elements.size(); i++){
            MenuElement* elem = elements[i];
            
            if(elem->kind == BUTTON && elem->isHighlighted ){
                
                vector<int> indexTree = elem->getIndexTree();
                
                // Construct our event!
                MenuEvent event = MenuEvent(indexTree);
                
                ofxMenu* topParentMenu = (ofxMenu*) topParent;
                ofNotifyEvent(topParentMenu->selectedElement, event, topParent);
                topParentMenu->closeChildren();
                topParentMenu->bIsOpen = false;
            }
        }
    }
}

//-----------------------------------------
MenuEvent ofxMenu::genRandomIndexTree() {
    string name = "";
    vector<int> indexTree;
    indexTree.reserve(16);
    
    // Loop until we actually generate a valid indexTree.
    // Bit hackish...
    bool foundBranch = false;
    while (foundBranch == false) {
        genRandomIndexTreeRecursive(name, indexTree);
        if (name != "") {
            foundBranch = true;
        }
    }
    return MenuEvent(indexTree);
}

//-----------------------------------------
void ofxMenu::genRandomIndexTreeRecursive(string& name, vector<int>& indexTree){
    if (elements.size() == 0) {
        return;
    }
    
    int randomIndex = (int)ofRandom(0.0, elements.size());
    indexTree.push_back(randomIndex);
    
    if (elements[randomIndex]->kind == MENU) {
        ofxMenu* childMenu = (ofxMenu*)elements[randomIndex];
        childMenu->genRandomIndexTreeRecursive(name, indexTree);
    } else {
        name = elements[randomIndex]->name;
    }
}


//-----------------------------------------
void ofxMenu::setPosition(int x, int y) {
    pos.x = x;
    pos.y = y;
    
    int yOffset = 0;
    int offsetAmount = getChildOffset();
    
    // Recursively set the position of all children menus.
    for(vector<MenuElement*>::iterator it = elements.begin(); it != elements.end(); it++){
        MenuElement* elem = (*it);
        
        if (elem->kind == MENU) {
            ofxMenu* menuPtr = (ofxMenu*)elem;
            menuPtr->setPosition(x + WIDTH, y + yOffset);
        }
        yOffset += offsetAmount;
    }
}

//-----------------------------------------
bool ofxMenu::isOverRect(int rectX, int rectY, int rectW, int rectH, int x, int y){
    return x < rectX + rectW && x > rectX
    && y < rectY + rectH && y > rectY;
}

//-----------------------------------------
int ofxMenu::getChildOffset() {
    int totalHeight = elements.size() * HEIGHT;
    int distanceFromBottom = ofGetHeight() - pos.y;
    if(totalHeight > distanceFromBottom){
        return -HEIGHT;
    } else {
        return HEIGHT;
    }
}

//-----------------------------------------
void ofxMenu::closeChildren() {
    
    // Make sure all the children menus are closed.
    for (int i=0; i < elements.size(); i++) {
        MenuElement* elem = elements[i];
        
        elem->isHighlighted = false;
        
        // If over a menu, close its children too.
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
        int offsetAmount = getChildOffset();
        
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
            yOffset += offsetAmount;
        }
    }
}

//-----------------------------------------
void ofxMenu::mouseMoved(ofMouseEventArgs &mouse){
    setHighlighted(mouse.x, mouse.y);
}

//-----------------------------------------
void ofxMenu::mouseReleased(ofMouseEventArgs &mouse){
    getSelected();
}