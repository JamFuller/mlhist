#include <cstring>
#include <string>
#include <vector>
#include <istream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>

#include "lib/rapidjson/document.h"
#include "lib/rapidjson/writer.h"
#include "lib/rapidjson/stringbuffer.h"
#include "lib/rapidjson/rapidjson.h"
#include "lib/rapidjson/pointer.h"

#include "lib/gnuplot-cpp/gnuplot_i.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
#include <conio.h>   //for getch(), needed in wait_for_key()
#include <windows.h> //for Sleep()
void sleep(int i) { Sleep(i*1000); }
#endif

#include "history.cpp"

#define SLEEP_LGTH 2  // sleep time in seconds
#define NPOINTS    50 // length of array

using namespace rapidjson;
using namespace std;

void doPlot(string output, string plot, string units, string name, string resource, const Value &entries) {

  Gnuplot::set_terminal_std("dumb");
  Gnuplot g1("points");

  if (output.find("plot") != string::npos) {
    g1.cmd(string("load '") + plot + "'");
  } else if (output.find("jpeg") != string::npos) {
    g1.cmd("set terminal 'jpeg'");
    g1.cmd("set output 'mlhist.jpg'");
  }

  g1.set_ylabel(units);
  g1.set_xlabel("time");
  g1.cmd("set xdata time");
  g1.cmd("set timefmt '%Y-%m-%dT%H:%M:%S'");
  //g1.cmd("set xtics rotate");

  vector<string> x;
  vector<double> y;
  string firstDT, lastDT;
  for (SizeType i = 0; i < entries.Size(); i++) {
    const Value &entry = entries[i];
    if (i == 0) {
      firstDT = entry["dt"].GetString();
    }
    if (i == entries.Size() - 1) {
      lastDT = entry["dt"].GetString();
    }
    x.push_back(entry["dt"].GetString());
    y.push_back(entry["value"].GetDouble());
  }
  g1.cmd("set xrange ['" + firstDT + "':'" + lastDT + "']");
  g1.cmd(resource + ":" + name);
  g1.plot_xy(x, y);
}

int main(int argc, char *argv[]) {

  try {
    History history;
    history.setCurrentArgs(history.options(argc, argv));
    CommandLineArgs current = history.getCurrentArgs();
    Config config = history.getConfig();

    if (current.quiet == false) {
      cout << "mlhist: mlhist 1.0 | copyright (c)2016 Jim Fuller | see https://github.com/xquery/mlhist" << endl;
    }

    if (current.verbose) {
      cout << "----------------" << endl;
      cout << "~/.mlhist" << endl;
      cout << "----------------" << endl;
      cout << "user: " << config.user << endl;
      cout << "pass: " << config.pass << endl;
      cout << "host: " << config.host << endl;
      cout << "----------------" << endl;
      cout << "options" << endl;
      cout << "----------------" << endl;
      cout << "format: " << current.format << endl;
      cout << "period: " << current.period << endl;
      cout << "start: " << current.start << endl;
      cout << "end: " << current.end << endl;
      cout << "metric: " << current.metric << endl;
      cout << "resource: " << current.resource << endl;
      cout << "output: " << current.output << endl;
      cout << "gnuplot: " << current.gnuplot << endl;
    }

    history.setUrl(config.port, config.path, current.resource, "metrics");

    history.execute();

    string result = history.getReadBuffer();

    string graph_prefix = "graph";
    string output = current.output;

    if (!output.compare(0, graph_prefix.size(), graph_prefix)) {
      Document doc;
      doc.Parse(result.c_str());
      string res, units, name;

      if (strcmp(current.resource, "databases") == 0) {
        res = "database-metrics-list";
        units = doc[res.c_str()]["metrics-relations"]["database-metrics-list"]["metrics"][0]["master"][0][current.metric]["units"].GetString();
        name = doc[res.c_str()]["metrics-relations"]["database-metrics-list"]["metrics"][0]["master"][0][current.metric]["name"].GetString();
        const Value &entries = doc[res.c_str()]["metrics-relations"]["database-metrics-list"]["metrics"][0]["master"][0][current.metric]["summary"]["data"]["entry"];

        doPlot(output, current.gnuplot, units, name, string(current.resource), entries);

      } else if (strcmp(current.resource, "servers") == 0) {
        res = "server-metrics-list";

      } else if (strcmp(current.resource, "forests") == 0) {
        res = "forest-metrics-list";
        units = doc[res.c_str()]["metrics-relations"][res.c_str()]["metrics"][0][current.metric]["units"].GetString();
        name = doc[res.c_str()]["metrics-relations"][res.c_str()]["metrics"][0][current.metric]["name"].GetString();
        const Value &entries = doc[res.c_str()]["metrics-relations"]["forest-metrics-list"]["metrics"][0][current.metric]["summary"]["data"]["entry"];

        doPlot(output, current.gnuplot, units, name, string(current.resource), entries);

      } else if (strcmp(current.resource, "hosts") == 0) {
        res = "host-metrics-list";
      }
    } else {
      cout << result << endl;
    }

  } catch (std::bad_alloc) {
    cout << "Error with mlhist" << endl;
  }
  return EXIT_SUCCESS;
}