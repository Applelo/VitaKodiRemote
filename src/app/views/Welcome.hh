#ifndef VITAMATERIALKIT_WELCOME_HH
#define VITAMATERIALKIT_WELCOME_HH

#include "../../kit/core/View.hh"
#include "../../kit/utils/UtilsIME.hh"

class Welcome: public View {
private:
    UtilsIME *ime;

    ZoneEvent confirmButtonZE;
    ZoneEvent ipTextFieldZE, portTextFieldZE, usernameTextFieldZE, passwordTextFieldZE;
    ZoneEventCheckboxes authentificationCheckboxZE;
    std::string ip, username, password;
    UiCheckboxesStatus checkboxesStatus;
    int port;

public:
    Welcome(const char *name);
    void contents() override;
    void controls() override;

    void beforeEnter() override;

    void mounted() override;
};

#endif //VITAMATERIALKIT_WELCOME_HH
