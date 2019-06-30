#include "Settings.hh"



Settings::Settings(const char *name) : View(name) {

}

void Settings::contents() {

    ipTextFieldZE = ui->textFields->filledDrawLeadingIcon(SCREEN_HALF_WIDTH - (TEXTFIELD_DEFAULT_WIDTH / 2), 10, TEXTFIELD_MODE_SINGLE, utils->PTC->isY(PADTOUCHCTRL_IS_FIRST), "Adresse IP", ICON_MDI_IP_NETWORK, ip);
    portTextFieldZE = ui->textFields->filledDrawLeadingIcon(SCREEN_HALF_WIDTH - (TEXTFIELD_DEFAULT_WIDTH / 2), 20 + ipTextFieldZE.y + ipTextFieldZE.height, TEXTFIELD_MODE_SINGLE, utils->PTC->isY(2), "Port", ICON_MDI_SERIAL_PORT, std::to_string(port));
    authentificationCheckboxZE = ui->checkboxes->drawWithText(SCREEN_HALF_WIDTH - (authentificationCheckboxZE.width / 2), 10 + portTextFieldZE.y + portTextFieldZE.height, checkboxesStatus, "Identification", utils->PTC->isY(3));

    if (checkboxesStatus == CHECKBOX_CHECKED) {
        usernameTextFieldZE = ui->textFields->filledDraw(SCREEN_HALF_WIDTH - (TEXTFIELD_DEFAULT_WIDTH / 2), authentificationCheckboxZE.y + authentificationCheckboxZE.height, TEXTFIELD_MODE_SINGLE, utils->PTC->isY(4), "Utilisateur", username);
        passwordTextFieldZE = ui->textFields->filledDraw(SCREEN_HALF_WIDTH - (TEXTFIELD_DEFAULT_WIDTH / 2), 20 + usernameTextFieldZE.y + usernameTextFieldZE.height, TEXTFIELD_MODE_SINGLE, utils->PTC->isY(5), "Mot de passe", password);
        confirmButtonZE = ui->buttons->containedDraw("Valider", SCREEN_HALF_WIDTH - (confirmButtonZE.width / 2), 30 + passwordTextFieldZE.y + passwordTextFieldZE.height, THEME_PRIMARY, utils->PTC->isY(PADTOUCHCTRL_IS_LAST), ICON_MDI_CHECK);
    }
    else {
        confirmButtonZE = ui->buttons->containedDraw("Valider", SCREEN_HALF_WIDTH - (confirmButtonZE.width / 2), 30 + authentificationCheckboxZE.y + authentificationCheckboxZE.height, THEME_PRIMARY, utils->PTC->isY(PADTOUCHCTRL_IS_LAST), ICON_MDI_CHECK);
    }

    if (tryConnection)
        ui->texts->draw(0, 0, Body1, "LOL");
    else
        ui->texts->draw(0, 0, Body1, "Sad");
}

void Settings::controls() {

    //events

    if (EventUi::onTouch(ipTextFieldZE, utils->touch->lastClickPoint) ||
            EventUi::onPad(ipTextFieldZE, utils->pad->pressed.cross)) {
        ip = ime->getUserText("IP", ip.c_str(), SCE_IME_TYPE_EXTENDED_NUMBER);
    }
    if (EventUi::onTouch(portTextFieldZE, utils->touch->lastClickPoint) ||
            EventUi::onPad(portTextFieldZE, utils->pad->pressed.cross)) {
        port = std::stoi(ime->getUserText("Port", std::to_string(port).c_str(), SCE_IME_TYPE_NUMBER));
    }
    if (checkboxesStatus == CHECKBOX_CHECKED) {
        if (EventUi::onTouch(usernameTextFieldZE, utils->touch->lastClickPoint) ||
                EventUi::onPad(usernameTextFieldZE, utils->pad->pressed.cross)) {
            username = ime->getUserText("Utilisateur", username.c_str());
        }
        if (EventUi::onTouch(passwordTextFieldZE, utils->touch->lastClickPoint) ||
                EventUi::onPad(passwordTextFieldZE, utils->pad->pressed.cross)) {
            password = ime->getUserText("Mot de passe", password.c_str());
        }
    }

    if (utils->PTC->isTouchMode()) {
        checkboxesStatus = ui->checkboxes->onTouchAuto(authentificationCheckboxZE, utils->touch->lastClickPoint);
    }
    else {
        checkboxesStatus = ui->checkboxes->onPadAuto(authentificationCheckboxZE, utils->pad->pressed.cross);
    }

    if (EventUi::onTouch(confirmButtonZE, utils->touch->lastClickPoint) ||
            EventUi::onPad(confirmButtonZE, utils->pad->pressed.cross)) {
        utils->config->setConnection(ip, port, checkboxesStatus == CHECKBOX_CHECKED, username, password);
        utils->config->save();
        //tryConnection = utils->request->tryConnection();
    }


    if (checkboxesStatus == CHECKBOX_CHECKED) {
        this->utils->PTC->setLimit(1, 6);
    }
    else {
        this->utils->PTC->setLimit(1, 4);
    }


}

void Settings::beforeEnter() {
    ip = utils->config->getIp();
    port = utils->config->getPort();
    checkboxesStatus = utils->config->isAuthentication() ? CHECKBOX_CHECKED : CHECKBOX_UNCHECKED;
    username = utils->config->getUsername();
    password = utils->config->getPassword();
}

void Settings::mounted() {
    ime = new UtilsIME();
}


