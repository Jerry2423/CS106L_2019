
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "SimpleGraph.h"

using std::cin;
using std::cout;	using std::endl;
using std::vector; using std::string; using std::pair;
using std::istringstream; using std::ostringstream;
using std::ifstream; using std::ofstream;
using std::sqrt; using std::pow;
const double kPi = 3.14159265358979323;
const double kRepel = 0.001;
const double kAttr = 0.001;

void Welcome();

string getStirng(const string& prompt) {
    cout << prompt;
    string s;
    if (!getline(cin, s)) {
        throw "error";
    }
    return s;
}

// assumption: the file can be open
void readGraphFromFile(ifstream& file, SimpleGraph& myGraph) {
    string line;
    size_t curr_line = 0;
    while (getline(file, line)) {
        istringstream s(line);
        if (curr_line == 0) {
            size_t num_nodes;
            s >> num_nodes;
            for (size_t i = 0; i < num_nodes; i++) {
                myGraph.nodes.push_back({cos(2*kPi * i / num_nodes), sin(2*kPi * i / num_nodes)});
            }
        } else {
            size_t start, end;
            s >> start >> end;
            myGraph.edges.push_back({start, end});
        }
        curr_line++;
    }
}

void graphGen(SimpleGraph& myGraph) {
    while (true) {
       string file_name = getStirng("enter the graph file name: ");
       ifstream file(file_name);
       if (file) {
           readGraphFromFile(file, myGraph);
           cout << "read succeed!" << endl;
           return;
       }
       cout << "invalid file name, please enter again" << endl;
    }
}

double getDouble(const string& prompt, const string& reprompt = "invalid input, please enter again") {
    while (true) {
       cout << prompt;
       string line;
       if (!getline(cin, line)) {
           throw "input error";
       }
       istringstream s(line);
       double num;
       char trash;
       if (s >> num && !(s >> trash)) {
           return num;
       }
       cout << reprompt << endl;
    }
}


// Main method
int main() {
    Welcome();
    SimpleGraph myGraph;
    graphGen(myGraph);
    InitGraphVisualizer(myGraph);
    DrawGraph(myGraph);

    double run_time = getDouble("enter the running time: ");
    time_t start_time = time(NULL);

    while (difftime(time(NULL), start_time) <= run_time) {
        // create vector of pairs to record each point's delta_x/y
        size_t num_nodes = myGraph.nodes.size();
        vector<pair<double, double>> net_force(num_nodes, std::make_pair<double, double>(0, 0)); // first x and second y
        // compute repel forces
        for (size_t i = 0; i < num_nodes; i++) {
            for (size_t j = i+1; j < num_nodes; j++) {
                double x0 = myGraph.nodes[i].x, y0 = myGraph.nodes[i].y, x1 = myGraph.nodes[j].x, y1 = myGraph.nodes[j].y;
                double theta = atan2(y1 - y0, x1 - x0);
                double f_repel = kRepel / sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
                net_force[i].first -= f_repel * cos(theta);
                net_force[i].second -= f_repel * sin(theta);
                net_force[j].first += f_repel * cos(theta);
                net_force[j].second += f_repel * sin(theta);
            }
        }

        // compute attractive forces
        for (const auto& i : myGraph.edges) {
            double x0 = myGraph.nodes[i.start].x, y0 = myGraph.nodes[i.start].y, x1 = myGraph.nodes[i.end].x, y1 = myGraph.nodes[i.end].y;
            double f_attr = kAttr * (pow(x1 - x0, 2) + pow(y1 - y0, 2));
            double theta = atan2(y1 - y0, x1 - x0);
            net_force[i.start].first += f_attr * cos(theta);
            net_force[i.start].second += f_attr * sin(theta);
            net_force[i.end].first -= f_attr * cos(theta);
            net_force[i.end].second -= f_attr * sin(theta);
        }

        // move each node
        for (size_t i = 0; i < num_nodes; i++) {
            myGraph.nodes[i].x += net_force[i].first;
            myGraph.nodes[i].y += net_force[i].second;
        }

        DrawGraph(myGraph);

    }

    cout << "running ends!" << endl;


    return 0;
}

/* Prints a message to the console welcoming the user and
 * describing the program.*/
void Welcome() {
    cout << "Welcome to CS106L GraphViz!" << endl;
    cout << "This program uses a force-directed graph layout algorithm" << endl;
    cout << "to render sleek, snazzy pictures of various graphs." << endl;
    cout << endl;
}



