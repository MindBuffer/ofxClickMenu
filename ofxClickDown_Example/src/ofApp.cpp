#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetCircleResolution(40);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
<<<<<<< HEAD
    
    // Add the JEN and LFOS menus to the modulatorMenu.
    ofxMenu* jen = modulatorMenu.addMenu("JEN");
    ofxMenu* lfos = modulatorMenu.addMenu("LFOS");
    
    // Add the Instruments and Playheads menus to the `jen` menu.
    ofxMenu* instruments = jen->addMenu("Instruments");
    ofxMenu* playheads = jen->addMenu("Playheads");
    
=======

    // Add the JEN and LFOS menus to the modulatorMenu.
    ofxMenu* jen = modulatorMenu.addMenu("JEN");
    ofxMenu* lfos = modulatorMenu.addMenu("LFOS");

    // Add the Instruments and Playheads menus to the `jen` menu.
    ofxMenu* instruments = jen->addMenu("Instruments");
    ofxMenu* playheads = jen->addMenu("Playheads");

>>>>>>> aacd72c73a0f455439d604e4abe0dfd44464b96a
    // Add the Instruments menu buttons.
    instruments->addButton("Kick Amp");
    instruments->addButton("Kick Pan");
    instruments->addButton("Snare Amp");
    instruments->addButton("Snare Pan");
    instruments->addButton("Ride Amp");
    instruments->addButton("Ride Pan");
    instruments->addButton("Ghost Amp");
    instruments->addButton("Ghost Pan");
<<<<<<< HEAD
    
=======

>>>>>>> aacd72c73a0f455439d604e4abe0dfd44464b96a
    // Add the Playheads menu buttons.
    playheads->addButton("Song");
    playheads->addButton("Part");
    playheads->addButton("Segment");
    playheads->addButton("Bar");
    playheads->addButton("Minim");
    playheads->addButton("Beat");
    playheads->addButton("Quaver");
    playheads->addButton("SemiQuaver");
<<<<<<< HEAD
    
=======

>>>>>>> aacd72c73a0f455439d604e4abe0dfd44464b96a
    // Add the LFOS menu buttons.
    lfos->addButton("LFO1");
    lfos->addButton("LFO2");
    lfos->addButton("LFO3");
    lfos->addButton("LFO4");
    lfos->addButton("LFO5");
    lfos->addButton("REORDER1");
    lfos->addButton("REORDER2");
    lfos->addButton("REORDER3");
<<<<<<< HEAD

    ofAddListener(modulatorMenu.selectedElement, this, &ofApp::menuEvent);

}

//--------------------------------------------------------------
void ofApp::menuEvent(string &s){
    cout << "Woooop our [ " + s + " ] button was clicked :) " << endl;
    cout << " --------------------------------------------- " << endl;
=======
>>>>>>> aacd72c73a0f455439d604e4abe0dfd44464b96a
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::black, ofColor::blue, OF_GRADIENT_LINEAR);
    
    ofSetHexColor(0xFFFFFF);
    ofDrawBitmapString("Click & open Menu Dialog.", 30,30);
    
    modulatorMenu.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    modulatorMenu.openByClick(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
