#include <QtGui>
#include <QTimer>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QWidget>
#include "GameInfo.h"
#include "GameObject.h"
#include "CDriver.h"
#include "../network/netclient.h"
#include "../network/stream.h"

namespace td {

  td::Stream* CDriver::updates_;

  CDriver::CDriver(MainWindow *mainWindow) {
      mainWindow_ = mainWindow;
  }

  CDriver::~CDriver() {
    delete this -> gameTimer_;
    delete this -> human_;
    td::AudioManager::instance()->shutdown();
  }

  void CDriver::connectToServer(char * servaddr) {
    td::NetworkClient::init(QHostAddress(servaddr));
    CDriver::updates_ = new Stream();
  }
  void CDriver::disconnectFromServer() {
    delete CDriver::updates_;
    td::NetworkClient::instance() -> shutdown();
  }
  void CDriver::updateServer(int data) {
    CDriver::updates_ -> writeInt(data);
    td::NetworkClient::instance() -> send(CDriver::updates_ -> data());
  }
  Player* CDriver::createHumanPlayer(MainWindow *gui) {
    PhysicsComponent* physics = new PlayerPhysicsComponent();
    GraphicsComponent* graphics = new PlayerGraphicsComponent();
    PlayerInputComponent* input = new PlayerInputComponent();
    //gui->installEventFilter(input);
    connect(gui, SIGNAL(signalKeyPressed(int)), input, SLOT(keyPressed(int)));
    connect(gui, SIGNAL(signalKeyReleased(int)), input, SLOT(keyReleased(int)));
    
    return new Player((InputComponent*) input, physics, graphics);
  }

    void CDriver::startGame() {
        CDriver::gameTimer_   = new QTimer(this);
        CDriver::human_       = createHumanPlayer(mainWindow_);
        CDriver::contextMenu_ = new ContextMenu(human_);

        connect(mainWindow_,  SIGNAL(signalSpacebarPressed()),
                contextMenu_, SLOT(toggleMenu()));
        connect(mainWindow_,  SIGNAL(signalNumberPressed(int)),
                contextMenu_, SLOT(selectMenuItem(int)));
        connect(gameTimer_,   SIGNAL(timeout()), 
                human_,       SLOT(update()));

        CDriver::gameTimer_ -> start(30);
    }

  void CDriver::endGame() {
    this -> gameTimer_ -> stop();
    //cleanup code
  }
}
