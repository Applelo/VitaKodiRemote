#include "Welcome.hh"



Welcome::Welcome(const char *name) : View(name) {

}

void Welcome::contents() {

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


}

void Welcome::controls() {

    //events

    if (ui->textFields->onTouch(ipTextFieldZE, utils->touch->lastClickPoint) ||
        ui->textFields->onPad(ipTextFieldZE, utils->pad->pressed.cross)) {
        ip = ime->getUserText("IP", ip.c_str(), SCE_IME_TYPE_EXTENDED_NUMBER);
    }
    if (ui->textFields->onTouch(portTextFieldZE, utils->touch->lastClickPoint) ||
        ui->textFields->onPad(portTextFieldZE, utils->pad->pressed.cross)) {
        port = std::stoi(ime->getUserText("Port", std::to_string(port).c_str(), SCE_IME_TYPE_NUMBER));
    }
    if (checkboxesStatus == CHECKBOX_CHECKED) {
        if (ui->textFields->onTouch(usernameTextFieldZE, utils->touch->lastClickPoint) ||
            ui->textFields->onPad(usernameTextFieldZE, utils->pad->pressed.cross)) {
            ip = ime->getUserText("Utilisateur", username.c_str());
        }
        if (ui->textFields->onTouch(passwordTextFieldZE, utils->touch->lastClickPoint) ||
            ui->textFields->onPad(passwordTextFieldZE, utils->pad->pressed.cross)) {
            ip = ime->getUserText("Mot de passe", ip.c_str());
        }
    }

    if (utils->PTC->isTouchMode()) {
        checkboxesStatus = ui->checkboxes->onTouchAuto(authentificationCheckboxZE, utils->touch->lastClickPoint);
    }
    else {
        checkboxesStatus = ui->checkboxes->onPadAuto(authentificationCheckboxZE, utils->pad->pressed.cross);
    }

    if (ui->buttons->onTouch(confirmButtonZE, utils->touch->lastClickPoint) ||
        ui->buttons->onPad(confirmButtonZE, utils->pad->pressed.cross)) {

    }



    if (checkboxesStatus == CHECKBOX_CHECKED) {
        this->utils->PTC->setLimit(1, 6);
    }
    else {
        username = "";
        password = "";
        this->utils->PTC->setLimit(1, 4);
    }


}

void Welcome::beforeEnter() {
    this->checkboxesStatus =  CHECKBOX_CHECKED;
}

void Welcome::mounted() {
    ime = new UtilsIME();
    ip = utils->config->getIp();
}


