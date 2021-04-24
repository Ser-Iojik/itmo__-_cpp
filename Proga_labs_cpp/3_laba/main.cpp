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

int ctoi(char c){
    return c - '0';
}

typedef unordered_map<string, string> numbersMap;
typedef unordered_map<string, int> countMap;
int main() {
    setlocale(LC_ALL, "Rus");

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("test.xml");

    if (!result)  
        return -1;

    vector<wstring> str;
    int i = 1;
    unordered_map<int, string> numbersMap;
    unordered_map<int, int> countMap;

    for (pugi::xml_node transport_station = doc.child("dataset").child("transport_station"); transport_station; transport_station = transport_station.next_sibling("transport_station")) {
        wstring tr = transport_station.child_value(L"type_of_vehicle");
        string routes = transport_station.child_value("routes");
        
        // int numberOfTr = stoi(routes);

        for (int i = 0; i < routes.size(); i++) {
            
            if ((routes[i] >= '0' && routes[i] <= '9') && (routes[i+1] == ',' || routes[i+1] == '.' || routes[i+1] == '\0')) {
                if (!(routes[i-1] >= '0' && routes[i-1] <= '9')) {
                    // cout << routes << "= " << routes[i] << endl;
                    int numberOfTr = ctoi(routes[i]);
                    // cout << numberOfTr << endl;

                    /* подсчёт остановок */
                    numbersMap.insert(make_pair(numberOfTr, tr));
                    if (numbersMap.count(numberOfTr) == 1) {
                        // cout << numberOfTr << " " << endl;
                        if (countMap.find(numberOfTr) != countMap.end()) {
                            countMap[numberOfTr] += 1;
                            // cout << "true: " << numberOfTr << " " << tr << " " << countMap[numberOfTr] << endl;
                        } else {
                            countMap.insert(make_pair(numberOfTr, 1));
                            // cout << "false: "  << numberOfTr << " " << tr << " " << 1 << endl;
                        }
                    }
                    /* подсчёт остановок */
                }
            }

            if ((routes[i-1] >= '0' && routes[i-1] <= '9' && routes[i] >= '0' && routes[i] <= '9') && (routes[i+1] == ',' || routes[i+1] == '.' || routes[i+1] == '\0')) {
                if (!(routes[i-2] >= '0' && routes[i-2] <= '9')) {
                    // cout << routes << "= " << routes[i-1] << " " << routes[i] << endl;
                    auto numberOfRoute = std::string(1,routes[i-1]) + routes[i];
                    int numberOfTr = stoi(numberOfRoute);
                    // cout << numberOfTr << endl;

                    /* подсчёт остановок */
                    numbersMap.insert(make_pair(numberOfTr, tr));
                    if (numbersMap.count(numberOfTr) == 1) {
                        // cout << numberOfTr << " " << endl;
                        if (countMap.find(numberOfTr) != countMap.end()) {
                            countMap[numberOfTr] += 1;
                            // cout << "true: " << numberOfTr << " " << tr << " " << countMap[numberOfTr] << endl;
                        } else {
                            countMap.insert(make_pair(numberOfTr, 1));
                            // cout << "false: "  << numberOfTr << " " << tr << " " << 1 << endl;
                        }
                    }
                    /* подсчёт остановок */
                }
            }

            if (routes[i-2] >= '0' && routes[i-2] <= '9' && routes[i-1] >= '0' && routes[i-1] <= '9' && routes[i] >= '0' && routes[i] <= '9' && (routes[i+1] == ',' || routes[i+1] == '.' || routes[i+1] == '\0')) {
                if (!(routes[i-3] >= '0' && routes[i-3] <= '9')) {
                    // cout << routes << "= " << routes[i-2] << " " << routes[i-1] << routes[i] << endl;
                    auto numberOfRoute = std::string(1,routes[i-2]) + routes[i-1] + routes[i];
                    int numberOfTr = stoi(numberOfRoute);
                    // cout << numberOfTr << endl;

                    /* подсчёт остановок */
                    numbersMap.insert(make_pair(numberOfTr, tr));
                    if (numbersMap.count(numberOfTr) == 1) {
                        // cout << numberOfTr << " " << endl;
                        if (countMap.find(numberOfTr) != countMap.end()) {
                            countMap[numberOfTr] += 1;
                            // cout << "true: " << numberOfTr << " " << tr << " " << countMap[numberOfTr] << endl;
                        } else {
                            countMap.insert(make_pair(numberOfTr, 1));
                            // cout << "false: "  << numberOfTr << " " << tr << " " << 1 << endl;
                        }
                    }
                    /* подсчёт остановок */
                }
            }
        }


    }

    // for (auto x : numbersMap)
    //     cout << x.first << " " << x.second << endl;
    // cout << endl;
    for (auto x : countMap)
        cout << x.first << " " << x.second << endl;

}