#include "Utils.hh"

Utils::Utils() {
    this->init();
}

void Utils::init() {
   this->touch = new UtilsTouch();
   this->pad = new UtilsPad();
   this->i18n = new UtilsI18n();
   this->scroll = new UtilsScroll(this->touch);
   this->PTC = new UtilsPadTouchCtrl(this->pad, this->touch, this->scroll);
   this->config = new Config();
   this->request = new Request(this->config);
}

void Utils::read() {
    pad->read();
    touch->read();
    PTC->controller();
}

