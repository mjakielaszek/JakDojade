#include <iostream>
#include "map.h"
#include "fligths.h"
#include "city.h"
#include "list.h"
#include "base.h"
using namespace std;

int main() {
    int x, y, k;
    char buffer[2*BUFF];
    cin >> x;
    cin >> y;
    MapInfo map(x, y);
    DoubleList* cityHead = new DoubleList;
    DoubleList* horizontalHead = new DoubleList;
    DoubleList* verticalHead = new DoubleList;
    map.setCityList(&cityHead);
    map.setHorizontalList(&horizontalHead);
    map.setVerticalList(&verticalHead);
    gets_s(buffer, BUFF);
    char* sliceOfMap = new char[BUFF];
    for (int i = 0; i < y; i++) {
        gets_s(sliceOfMap, BUFF);
        map.setSlice(sliceOfMap, i);
    }
    map.getPositions();
    
    cin >> k;
    DoubleList* connectionsHead = new DoubleList;
    Connection* allConnections = new Connection;
    allConnections->setConnections(&connectionsHead);
    allConnections->setCityList(&cityHead);
    if (k > 0) {
        gets_s(buffer, BUFF);
        for (int i = 0; i < k; i++) {
            gets_s(buffer, 2 * BUFF);
            allConnections->findCities(buffer);
        }
    }
    map.setConnections(&connectionsHead);
    map.getNeighbours();
    map.makeArr();
    return 0;
}
