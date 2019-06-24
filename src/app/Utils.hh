#ifndef VITAMATERIALKIT_UTILS_HH
#define VITAMATERIALKIT_UTILS_HH

#include "../kit/utils/UtilsI18n.hh"
#include "../kit/utils/UtilsTouch.hh"
#include "../kit/utils/UtilsPad.hh"
#include "../kit/utils/UtilsPadTouchCtrl.hh"
#include "../kit/utils/UtilsScroll.hh"
#include "utils/Config.hh"

class Utils {
protected:
    virtual void init();
public:
    UtilsTouch *touch;
    UtilsPad *pad;
    UtilsI18n *i18n;
    UtilsPadTouchCtrl *PTC;
    UtilsScroll *scroll;
    Config *config;

    Utils();
    virtual void read();
};


#endif //VITAMATERIALKIT_UTILS_HH
