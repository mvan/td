#ifndef CDRIVER_H
#define CDRIVER_H
#include <QTimer>
#include <QApplication>
#include <QMainWindow>
#include <QVector>
#include "ContextMenu.h"
#include "ContextMenuGraphicsComponent.h"
#include "Player.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerGraphicsComponent.h"
#include "../client/MainWindow.h"
//#include "GameInfo.h"
//#include "GameObject.h"
namespace td {
  class CDriver : public QObject {
      Q_OBJECT
  
  private:
    //  GameInfo gameInfo;
    QTimer* gameTimer_;
    Player* human_;
    MainWindow* mainWindow_;
    //QVector<GameObject> objects;

    /**
     * A context menu that appears around the player.
     */
    ContextMenu* contextMenu_;

  public:
    // ctors and dtors
    CDriver(MainWindow* parent = 0);
    ~CDriver();

    /**
     * Creates a human player object.
     * Sets event filter for key presses to be passed to PlayerInputComponent.
     * 
     * @author Tom Nightingale
     * @return Player*, pointer to new player instance.
     */
    Player* createHumanPlayer(MainWindow *);
    
    /**
     * Connects all current GameObjects' SLOTs to a timer SIGNAL.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void bindAll();

    /**
     * Connects a single GameObject's SLOT to a timer SIGNAL.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void bindSingle(const GameObject& obj);
    /**
     * Connects the client driver to the server.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void connectToServer(char * servaddr);
    /**
     * Disconnects the client driver from the server.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void disconnectFromServer();

    /**
     * Stop game timer.
     * 
     * @author Duncan Donaldson
     * @return void
     */
    void endGame();
    
    /**
     * Load map from file, parse data, store in game info map property
     * 
     * @author Duncan Donaldson
     * @return int
     */
    //int loadMap(GameInfo &gi, char* map);
    
  public slots:
    /**
    * Initialize and start game timer.
    * [Hijacked and updated by Tom Nightingale] 
    * Client side objects are created here.
    *
    * @author Duncan Donaldson
    * @return void
    */
    void startGame();
  };
}
#endif
