//#include "libs/pugixml/src/pugixml.hpp"
#include "libs/pugixml/src/pugixml.cpp"
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <clocale>
using namespace std;

void show(pair<int, string> p) {
    cout << p.first << "->" << p.second << " ";
}
typedef unordered_map<string, string> numbersMap;
typedef unordered_map<string, int> countMap;
int main() {
    setlocale(LC_ALL, "Rus");

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("test.xml");

    if (!result)  
        return -1;

    vector<string> str;
    int i = 1;
    unordered_map<string, string> numbersMap;
    unordered_map<string, int> countMap;

    for (pugi::xml_node transport_station = doc.child("dataset").child("transport_station"); transport_station; transport_station = transport_station.next_sibling("transport_station")) {
        string tr = transport_station.child_value("type_of_vehicle");
        string numberOfTr = transport_station.child_value("routes");

        numbersMap.insert(make_pair(numberOfTr, tr));

        if (numbersMap.count(numberOfTr) == 1) {
            // cout << numberOfTr << " " << endl;
            if (countMap.find(numberOfTr) != countMap.end()) {
                countMap[numberOfTr] += 1;
                cout << "true: " << numberOfTr << " " << tr << " " << countMap[numberOfTr] << endl;
            } else {
                countMap.insert(make_pair(numberOfTr, 1));
                cout << "false: "  << numberOfTr << " " << tr << " " << 1 << endl;
            }
        }
    }
    for (auto x : numbersMap)
        cout << x.first << " " << x.second << endl;
    cout << endl;
    for (auto x : countMap)
        cout << x.first << " " << x.second << endl;

}