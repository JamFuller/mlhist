#pragma once

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <wchar.h>
#include <vector>
#include <map>
#include <cassert>

#include <curl/curl.h>

#include "config.hpp"

struct CommandLineArgs
{
  CommandLineArgs()
    : format(""),
      period(""),
      start(""),
      end(""),
      metric(""),
      resource(""),
      database(""),
      group(""),
      output(""),
      gnuplot(""),
      quiet(true),
      verbose(false)
  {
  }
  
  void check(const char *progname){}
  
  const char *format, *period, *start, *end, *metric, *resource, *database, *group, *output, *gnuplot;
  bool quiet, verbose;
};

// interface for commands
class Command
{
private:
  Config config;
  CommandLineArgs current;  
  string readBuffer;
  
public:
  string url;

  Command(){
    //std::cout << "Default constructor called\n";
    loadConfig(config);
  };
  
  virtual ~Command(){
    //std::cout << "Default destructor called\n";
  };

  virtual int usage(const char *progname) =0;

  virtual CommandLineArgs options(int n_opts, char *opts[]) = 0;

  virtual string getReadBuffer(){
    return this->readBuffer;
  }
  
  virtual CommandLineArgs getCurrentArgs(){
    return this->current;
  }
  virtual void setCurrentArgs(CommandLineArgs args){
    this->current=args;
  }
  
  virtual Config getConfig(){
    return this->config;
  }
  
  virtual void setConfig(Config config){
    this->config=config;
  }
  
  virtual void setUrl(int port,
                      string root,
                      string path,
                      string view){

    string s_port = to_string(port);
    if(view == "metrics"){
      if(path.find("/") != string::npos){
        string res1 = path.substr(0, path.find("/")); 
        url="http://"+config.host+":"+s_port+root+"/"+res1+"?";
      }else{
        url="http://"+config.host+":"+s_port+root+"/"+path+"?";
      }
    }else{
      url="http://"+config.host+":"+s_port+root+"/"+path+"?";
    }
       
    if(view != ""){
      url += "view="+view;
    }

    string group = current.group;
    if(group != ""){
      url += "&group-id="+group;
    }
    string format = current.format;
    if(format != ""){
      url += "&format="+ format;
    }     
    string start = current.start;
    if(start != ""){
      url += "&start="+ start;
    }
    string end = current.end;
    if(end != ""){
      url += "&end="+ end;
    }
    string period = current.period;
    if(period != ""){
      url += "&period="+ period;
    }
    
    string metric = current.metric;
    if(metric != ""){
      string resource = current.resource;
      string delimiter = "/";
      string res1 = resource.substr(0, resource.find("/")); 
      if(res1 == "databases"){
        url += "&database-metrics="+ metric;
        if(resource.find("/") != string::npos){
          string res2 = resource.substr(resource.find("/")+1,resource.length()); 
          url += "&database="+ res2;}
      }else if(res1 == "servers"){
        url += "&server-metrics="+ metric;        
        if(resource.find("/") != string::npos){
          string res2 = resource.substr(resource.find("/")+1,resource.length()); 
          url += "&server="+ res2;}
      }else if(res1 == "hosts"){
        url += "&host-metrics="+ metric;        
        if(resource.find("/") != string::npos){
          string res2 = resource.substr(resource.find("/")+1,resource.length()); 
          url += "&host="+ res2;}
      }else if(res1 == "forests"){
        url += "&forest-metrics="+ metric;
        if(resource.find("/") != string::npos){
          string res2 = resource.substr(resource.find("/")+1,resource.length()); 
          url += "&forest="+ res2;}}}
  }
  
  virtual int execute(){
    
    CURLM *curlm;
    int handle_count;
    curlm = curl_multi_init();
    CURL *curl1 = NULL;
    curl1 = curl_easy_init();
    curl_multi_setopt(curlm, CURLMOPT_PIPELINING, 0L);
    
    if(curl1)
    {
      curl_easy_setopt(curl1, CURLOPT_USERNAME, config.user.c_str());  
      curl_easy_setopt(curl1, CURLOPT_PASSWORD, config.pass.c_str());

      if(current.verbose){
        curl_easy_setopt(curl1, CURLOPT_VERBOSE, 1L);
      }else{
        curl_easy_setopt(curl1, CURLOPT_HEADER,0);}

      curl_easy_setopt(curl1, CURLOPT_USERAGENT, "mlhist via curl/7.19.6");
      curl_easy_setopt(curl1, CURLOPT_HTTPAUTH, CURLAUTH_ANY); 
      curl_easy_setopt(curl1, CURLOPT_FOLLOWLOCATION, 1L);
      curl_easy_setopt(curl1, CURLOPT_URL,url.c_str());
      curl_easy_setopt(curl1, CURLOPT_HTTPGET, 1L);
      curl_easy_setopt(curl1, CURLOPT_NOPROGRESS, 1L);
      curl_easy_setopt(curl1, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl1, CURLOPT_WRITEDATA, &readBuffer);
      curl_multi_add_handle(curlm, curl1);

      CURLMcode code;
      while(1)
        {
          code = curl_multi_perform(curlm, &handle_count); 
          if(handle_count == 0)
            {
              break;
            }
        }
    }

  curl_global_cleanup();
  return EXIT_SUCCESS;
  };

  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
  {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
  }
};