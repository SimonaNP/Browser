#ifndef BROWSER_H_INCLUDED
#define BROWSER_H_INCLUDED
#include "DoubleLinkedList.h"
#include <stdio.h>
#include <ctime>
#include <string.h>
#include<iostream>
#include <sstream>

struct Tab
{
    std::string URL;
    long int timestamp;

    Tab(std::string _URL = "about:blank",
        long int _timestamp = 0)
        :URL(_URL), timestamp(std::time(nullptr)) {}
};

class Browser
{
public:
    using I = DoubleLinkedListIterator<Tab>;
    I it;

    Browser()
    {
        initialize();
        std::cout<<"Welcome to our browser!"<<std::endl<<
                    "Here is a little cheat sheet of the commands you are allowed to use and what they do:"<<std::endl<<
                    "GO <url> - loads the page with URL <url> in the current tab."<<std::endl<<
                    "INSERT <url> - adds new tab with URL <url> directly after the current one and it becomes the current one."<<std::endl<<
                    "BACK - opening the tab directly before the current one, it becomes the current one."
                    "FORWARD - opening the tab directly after the current one, it becomes the current one."<<std::endl<<
                    "REMOVE - removes the current tab, current one becomes the one after it, if there is no tab after, current one becomes the one before"<<std::endl<<
                    "PRINT - prints all of the tabs, the one with the symbol '>' before it is the current one"<<std::endl<<
                    "X - exits the browser"<<std::endl;
    performance();
}


    void performance(){
        std::string input, command, url;
        std::getline(std::cin, input);
getValues(input, command, url);
        while(input != "X"){


           if(command == "GO"){
                go(url);
           }else if(command == "INSERT"){
               insert(url);
           }else if(command == "BACK"){
               back();
           }else if(command == "FORWARD"){
               forward();
           }else if(command == "REMOVE"){
               remove();
           }else if(command == "PRINT"){
               print();
           }
           std::getline(std::cin, input);
getValues(input, command, url);

    }

        }




  void getValues(std::string input, std::string& command, std::string& url){
  std::istringstream exprs(input);
  std::ostringstream commander;
  std::ostringstream urler;
  char devider = ' ';
  char c;
  int flag = 0;
  while (exprs.get(c)){
        if( c!=devider && flag == 0)
      commander << c;
      else if(c == devider)
        flag =1;
      else{
        urler<<c;
      }


}
     command.assign(commander.str());
     if(flag == 0) url = "";
     else
     url.assign(urler.str());
}




    void initialize()
    {
        if(browser.empty())
        {
            Tab t ;
            browser.insertBegin(t);
            it = browser.begin();
        }
    }

    void go(std::string url){
        for(I itter = browser.begin(); itter; ++itter)
        {

            if(!browser.getAt(itter).URL.compare(url))
            {
                it=itter;
                browser.getAt(itter).timestamp= time(nullptr);
            }

        }
    }

    void insert(std::string url)
    {
        Tab t(url);
        if (!browser.getAt(browser.begin()).URL.compare( "about:blank"))
        {
            Tab t2;
            browser.insertBegin(t);
            browser.deleteEnd(t2);
            it=browser.begin();


        }

            else{
            browser.insertAfter(t, it);
            it++;
            }
    }

    void back(){
        if(it==browser.begin()) return;
        it--;
    }

    void forward(){
        if(it==browser.end()) return;
        it++;
    }

    void remove(){
        Tab t;
        I itter = it;
        if(it==browser.end()){
            it--;
        }else{
            it++;
        }
        browser.deleteAt(t,itter);
        initialize();


    }
    void print()
    {

        for(I itter = browser.begin(); itter; ++itter)
        {

            if(itter == it)
            {
                std::cout<<'>';
            }
            std::cout << browser.getAt(itter).URL << ' '<<browser.getAt(itter).timestamp<< std::endl;
        }
    }



private:
    DoubleLinkedList<Tab> browser;

};



#endif // BROWSER_H_INCLUDED
