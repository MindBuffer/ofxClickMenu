#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetCircleResolution(40);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    // LFOS
    ofxMenu lfos("LFOS");
    lfos.addButton("LFO1");
    lfos.addButton("LFO2");
    lfos.addButton("LFO3");
    lfos.addButton("LFO4");
    lfos.addButton("LFO5");
    lfos.addButton("REORDER1");
    lfos.addButton("REORDER2");
    lfos.addButton("REORDER3");
    
    // Jen Instruments
    ofxMenu instruments("Instruments");
    instruments.addButton("Kick Amp");
    instruments.addButton("Kick Pan");
    instruments.addButton("Snare Amp");
    instruments.addButton("Snare Pan");
    instruments.addButton("Ride Amp");
    instruments.addButton("Ride Pan");
    instruments.addButton("Ghost Amp");
    instruments.addButton("Ghost Pan");
    
    // Jen Playheads
    ofxMenu playheads("Playheads");
    playheads.addButton("Song");
    playheads.addButton("Part");
    playheads.addButton("Segment");
    playheads.addButton("Bar");
    playheads.addButton("Minim");
    playheads.addButton("Beat");
    playheads.addButton("Quaver");
    playheads.addButton("SemiQuaver");
    
    // Jen Type
    ofxMenu jen("JEN");
    jen.addMenu(instruments);
    jen.addMenu(playheads);
    
    modulatorMenu.addMenu(jen);
    modulatorMenu.addMenu(lfos);

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