#include <vector>

#include <unistd.h> 
#include "orderbook_dydx.h"
#include <future>
#include <thread>
#include <sstream>
#include <string>
#include "my_funcs.h"


#include "/usr/include/boost/variant.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include "client_polo.h"
#include <string>
#include "client_kraken.h"
#include <iostream>


orderbook_dydx::orderbook_dydx(monitor_trading* monitor_trading1aa){
  monitor_trading1 = monitor_trading1aa;
  num_kraken_messages_sent = 0;

  min_sequence_num = 0;
  do_reinitialize_orderbook =false;
  did_disconnect = false;
  
  url = "wss://api.dydx.exchange/v3/ws";
  m_endpoint.set_open_handler(bind(&orderbook_dydx::on_open,this,::_1));
  m_endpoint.set_message_handler(bind(&orderbook_dydx::on_message,this,::_1,::_2));
  m_endpoint.set_open_handler(bind(&orderbook_dydx::on_open,this,::_1));
  m_endpoint.set_message_handler(bind(&orderbook_dydx::on_message,this,::_1,::_2));
 
  trade_channel_id = 0;
  orderbook_channel_id = 0;

  work2 = std::make_shared < boost::asio::io_service::work > (ioService);
  
  for (int i = 0; i < 30; ++i) {
    threadpool.create_thread(
        boost::bind(&boost::asio::io_service::run, &ioService));
  };
 };










orderbook_dydx::orderbook_dydx(){
  std::cout<<"enter orderbook_dydx::orderbook_dydx"<<std::endl;
  num_kraken_messages_sent = 0;

  min_sequence_num = 0;
  do_reinitialize_orderbook =false;
  did_disconnect = false;


  url = "ws://localhost:8548";
   
  m_endpoint.set_open_handler(bind(&orderbook_dydx::on_open,this,::_1));
  m_endpoint.set_message_handler(bind(&orderbook_dydx::on_message,this,::_1,::_2));
    //synthetic_tick_data = NULL;


  trade_channel_id = 0;
  orderbook_channel_id = 0;

  std::cout<<"leave end orderbook_dydx::orderbook_dydx"<<std::endl;
}

  



void orderbook_dydx::start22(){
    try{
        start_thread = std::thread(&orderbook_dydx::start_and_monitor_orderbook22,this);
        set_affinity(start_thread);    
    }

    catch (const std::exception& e) {
                        std::cerr << "orderbook::start error"<<e.what() << std::endl;
  
    }


}



void orderbook_dydx::start_and_monitor_orderbook22(){
    try{
      std::cout<<"enter start_and_monitor_orderbook22"<<std::endl;

      std::ofstream out55a("t_t_T.txt",std::ios::app) ;
      out55a<<"monitor peftest::start_and_monitor_orderbook"<<std::endl;
      out55a.close();

      start_thread_2 = std::thread(&orderbook_dydx::start122,this,url);
      set_affinity(start_thread_2);
      std::this_thread::sleep_for(std::chrono::seconds(60));
        
      std::ofstream out55c("perftest_debug.txt",std::ios::app) ;
      out55c<<"peftest::after_called thread"<<std::endl;
      out55c.close();

      while(!do_exit){
            std::this_thread::sleep_for(std::chrono::seconds(60));
            
            if(did_disconnect || std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1)- last_time_received>60000){
              std::cout<<"dfjasdkfadsk"<<std::endl;
              std::ofstream out55b("orderbook_dydx.txt",std::ios::app) ;
              out55b<<did_disconnect<<" "<<last_time_received<<" "<<get_date()<<std::endl;

              websocketpp::lib::error_code ec;

              std::ofstream out1("orderbook_dydx.txt",std::ios::app);
              out1<<"tried to reconnect "<<url<<" "<<did_disconnect<<" "<<last_time_received<<std::endl;
              m_endpoint.close(con, 0,"",ec); 
              out1<<con->get_ec() << " :"  << con->get_ec().message()<<std::endl;
              did_disconnect = false;
              m_endpoint.stop();
              m_endpoint.reset();
                 
              start_thread_2.join();
              std::this_thread::sleep_for(std::chrono::seconds(20));
              start_thread_2 =  std::thread(&orderbook_dydx::start122,this,url);
              set_affinity(start_thread_2);
               
              num_kraken_messages_sent = 0;
              std::this_thread::sleep_for(std::chrono::seconds(10));
              out1<<"did_try to recconect"<<std::endl;
              out1.close();
            }
      }

      m_endpoint.stop();
    
      start_thread_2.join();

      std::this_thread::sleep_for(std::chrono::seconds(2));
      std::ofstream out55("perftest_debug.txt",std::ios::app) ;
      out55<<"exiting peftest::start_and_monitor_orderbook"<<std::endl;
      out55.close();
    }


    catch (const std::exception& e) {
                        std::cerr << "orderbook::start_and_monitor_orderbook error"<<e.what() << std::endl;
    }



}

void orderbook_dydx::start122(std::string uri) {
      try{
        global_uri = uri;
        
        if(true){  
          m_endpoint.set_access_channels(websocketpp::log::alevel::all);  
          m_endpoint.set_error_channels(websocketpp::log::elevel::all);
          
          m_endpoint.set_tls_init_handler([this](websocketpp::connection_hdl) {
                 return websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv12);
          });
          m_endpoint.set_socket_init_handler(bind(&type::on_socket_init, this, ::_1));
          m_endpoint.set_open_handler(bind(&orderbook_dydx::on_open,this,::_1));
          m_endpoint.set_message_handler(bind(&orderbook_dydx::on_message,this,::_1,::_2));
          m_endpoint.set_close_handler(bind(&type::on_close,this,::_1));
          m_endpoint.set_fail_handler(bind(&type::on_fail,this,::_1));
        }

        std::ofstream out1("tried_to_reconnect_orderbook_dydx.txt",std::ios::app);
        out1<<"enter start"<<std::endl;
        out1.close();
        websocketpp::lib::error_code ec;

        con = m_endpoint.get_connection(uri, ec);
       
      

        if(ec) {
            std::cout<<"connection didn't work"<<std::endl;
            m_endpoint.get_alog().write(websocketpp::log::alevel::app,ec.message());
            return;
        }
        else{
          std::cout<<"connection worked"<<std::endl;
        }

        m_start = std::chrono::high_resolution_clock::now();


        m_endpoint.connect(con);  
        m_endpoint.run();
        
        
      }
      catch(std::exception& e){
        std::cout<<"error ffff: "<<e.what()<<std::endl;
        
      }
}


void orderbook_dydx::on_open(websocketpp::connection_hdl hdl) {
  std::ofstream out1("orderbook_dydx.txt",std::ios::app);
  out1<<"on_open"<<std::endl<<std::endl;

  std::cout<<"enter on_orderbook_dydx::on_open "<<get_date()<<std::endl;
  m_open = std::chrono::high_resolution_clock::now();
  char buff[500];
       
  strncpy(buff, "{\"id\": 1, \"type\": \"subscribe\", \"channel\": \"v3_orderbook\", \"id\":\"ETH-USD\"}", 500);

  std::cout<<"url="<<url<<std::endl;
  std::cout<<"sent message ="<<buff<<std::endl;
 
  m_endpoint.send(hdl,buff, websocketpp::frame::opcode::text);
}


 void orderbook_dydx::on_message(websocketpp::connection_hdl hdl, message_ptr bb) {
    int debug_loc = 0;
    std::string debug_str55;
    try{
      std::string str22 = bb->get_payload();
      last_time_received = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
        
      std::istringstream str33(str22);
      boost::property_tree::ptree info;
      boost::property_tree::read_json(str33,info);
      ++numMsgsReceived;
      double price, quant;
      int counter = 0;
      ob_data x;
      long long now1 = get_now();

      BOOST_FOREACH (boost::property_tree::ptree::value_type& level1, info.get_child("contents")) {
            if(level1.first=="asks" || level1.first=="bids" ){
              BOOST_FOREACH (boost::property_tree::ptree::value_type& level2, level1.second) {
                counter = 0;
                BOOST_FOREACH (boost::property_tree::ptree::value_type& level3, level2.second) {
                  if(counter==0)
                    price = atof(level3.second.get_value<std::string>().c_str());
                  else
                    quant = atof(level3.second.get_value<std::string>().c_str());
                  ++counter;
                }
                if(counter==2){
                  bool isbuy = level1.first=="bids";
                  x.price = price;
                  x.quant = quant;
                  x.time1 = now1;

                  update_book( x,quant>1e-10, isbuy, true);
                }
              }
            }
        //  }                
      }
      return;  
    }
    catch(std::exception& e){
      std::cout<<"orderbook_dydx::on_message:"<<e.what()<<std::endl;
    }

  }
     









