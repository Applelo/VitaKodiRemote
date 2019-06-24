#include <psp2/kernel/processmgr.h>
#include "kit/core/App.hh"
#include "app/views/Welcome.hh"

int main() {

    auto *welcome = new Welcome("Welcome");

    auto *app = new App("Welcome");

    app->insertView(welcome);


    app->main();

}
