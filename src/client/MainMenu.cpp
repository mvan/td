#include "MainMenu.h"
#include "ui_MainMenu.h"
#include "settingswindow.h"
#include "keymap.h"
#include "../engine/CDriver.h"
#include <QApplication>

namespace td {

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    showing_ = false;

    settingsWindow* volume = new td::settingsWindow();
    connect (this, SIGNAL(signalVolumeWindow()),
             volume,SLOT(slotShowSettings()));
    connect(ui->pushMap, SIGNAL(clicked()), this, SLOT(slotPushKey()));
    connect(ui->pushOk, SIGNAL(clicked()), this, SLOT(slotShowMainMenu()));
    connect(ui->pushQuit, SIGNAL(clicked()), this, SLOT(slotPushQuit()));
    connect(ui->pushVolume,SIGNAL(clicked()), this, SLOT(slotPushSettings()));
    connect(volume, SIGNAL(signalWindowClosed()), this, SLOT(slotShowMainMenu()));

}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::slotPushOk() {
    slotShowMainMenu();
}

void MainMenu::slotPushSettings() {
    slotShowMainMenu();
    signalVolumeWindow();
}

void MainMenu::slotPushQuit() {
    qApp->quit();
}

void MainMenu::slotPushKey() {
    slotShowMainMenu();
    KeymapDialog* km = new KeymapDialog();
    if (km->exec() == QDialog::Accepted) {
        km->savemap();
        CDriver::instance()->getMainWindow()->loadKeymap();
    }
    slotShowMainMenu();
}

void MainMenu::slotShowMainMenu() {
    if (showing_) {
        showing_ = false;
        this->hide();
    } else {
        showing_ = true;
        this->show();
    }
}

}