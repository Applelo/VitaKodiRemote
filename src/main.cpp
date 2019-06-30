#include <psp2/kernel/processmgr.h>
#include "kit/core/App.hh"
#include "app/views/Settings.hh"

int main() {

    auto *settings = new Settings("Settings");

    auto *app = new App("Settings");

    app->insertView(settings);


    app->main();

}
