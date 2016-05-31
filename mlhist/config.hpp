#pragma once

using namespace std;

const string CONFIG_USER = "admin";
const string CONFIG_PASS = "admin";
const string CONFIG_PATH = "/manage/v2";
const string CONFIG_HOST = "localhost";
const int CONFIG_PORT = 8002;
const string CONFIG_PROTOCOL = "http";
const string CONFIG_FILE_NAME = ".mlhist";

struct Config {
  string user;
  string pass;
  string path;
  string host;
  int port;
  string protocol;
};

void loadConfig(Config& config) {
  config.user = CONFIG_USER;
  config.pass = CONFIG_PASS;
  config.host = CONFIG_HOST;
  config.port = CONFIG_PORT;
  config.path = CONFIG_PATH;

  std::string homepath = getenv("HOME");
  ifstream fin((homepath + "/" + CONFIG_FILE_NAME).c_str());
  if (!fin){
      cerr << "Could not open ~/"+CONFIG_FILE_NAME+" config file!"  <<  endl;}
  string line;
  while (getline(fin, line)) {
      istringstream sin(line.substr(line.find("=") + 1));
      if (line.find("user") != -1)
        sin >> config.user;
      else if (line.find("pass") != -1)
        sin >> config.pass;
      else if (line.find("host") != -1)
        sin >> config.host;
      else if (line.find("port") != -1) {
        string port;
        sin >> port;
        config.port = stoi(port);
      }else if (line.find("path") != -1)
        sin >> config.path;
      else if (line.find("protocol") != -1)
        sin >> config.protocol; }
}