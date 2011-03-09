#ifndef TD_MAP_H
#define TD_MAP_H

#include "../util/mutex_magic.h"
#include <QObject>
#include <QPoint>
#include <QList>
#include <QSet>
#include <QMap>
#include <QMutex>
#include <math.h>

namespace Tiled {
class Map;
}

namespace td {

class Unit;
class Tile;

class Map : public QObject {
    Q_OBJECT

public:
    explicit Map(Tiled::Map * tMap);
    virtual ~Map() { }

private:
    /**  */
    QMap<int,QList<QPointF> > waypoints;

    /**  */
    Tile ***tiles_;

    /**  */
    Tiled::Map * tMap_;

    /**  */
    int heightInTiles_;

    /**  */
    int widthInTiles_;

public:
    /**
     * This is a testing function pending a real map load function.
     *
     * This function will fill the tiles array and create fully blocked tiles
     * around the edges of the map. This can be used for collision detection.
     *
     * @author Luke Queenan
     */
    void initMap();

    /**
     * basic map creator function.
     *
     * @author Ian Lee
     */
    void loadTestMap2();

    /**
     * gets the row and column from coords x,y.
     * stores in pointers row and column
     *
     *@author Ian Lee
     */
    void getTileCoords(double x, double y, int* row, int* column);

    /**
     * gets the Tile from coords x,y.
     *
     * @author Ian Lee
     */
    Tile* getTile(double x, double y);

    /**
     * gets the Units from Tiles surounding coords x,y in radius.
     * currently radius is an int -> number of tiles away
     *
     * @author Ian Lee
     */
    QSet<Unit*> getUnits(double x, double y, double radius);

    /**
      * gets all waypoints stored.
      *
      * @author Ian Lee
      */
    QMap<int,QList<QPointF> > getAllWaypoints(){
        return waypoints;
    }

    /**
     * gets waypoints associated with key
     *
     * @author Ian Lee
     */
    QList<QPointF> getWaypoints(int key){
        return waypoints[key];
    }

    /**
     * inserts waypoint list to qmap
     *
     * @author Ian Lee
     */
    void addWaypoints(int key ,QList<QPointF> newSet){
        waypoints.insert(key, newSet);
    }

    /**
      * Adds a pointer to a unit to the specified tile.
      *
      * @author Luke Queenan
      */
    void addUnit(double x, double y, Unit *unitToAdd);

    /**
      * Removes the unit from the specified tile.
      *
      * @author Luke Queenan
      */
    void removeUnit(double x, double y, Unit *unitToRemove);

public slots:
    /**
     * Slot for getting a tile's list of occupying units and blocking status
     *
     * For now, this function will only change the blocking type.
     *
     * @author Luke Queenan
     */
    void getTileType(double column, double row, int *blockingType);
};

}

#endif
