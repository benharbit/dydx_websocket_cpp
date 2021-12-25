#ifndef ORDERBOOK_DYDX_H

#define  ORDERBOOK_DYDX_H



#include <vector>
#include <string>
#include "orderbook.h"

#include "parameters.hpp"
#include "boost/date_time/posix_time/posix_time.hpp" 

//#include <autobahn/autobahn.hpp>
//#include <autobahn/wamp_websocketpp_websocket_transport.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <boost/version.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <fstream>
#include <thread>
#include "/usr/include/boost/variant.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include "my_vars.h"
#include "client_kraken.h"
#include "client_ethereum.h"

#include <websocketpp/config/asio_client.hpp>

#include <websocketpp/client.hpp>
#include  "bitfinex_websocket.h"  


#include <iostream>
#include <chrono>

#include <websocketpp/config/asio_no_tls.hpp>

#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>
#include <boost/lockfree/stack.hpp>

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_tls_client::message_type::ptr message_ptr;
typedef websocketpp::lib::shared_ptr<boost::asio::ssl::context> context_ptr;
typedef client::connection_ptr connection_ptr;

typedef websocketpp::client<websocketpp::config::asio> client_no_tls;
typedef client_no_tls::connection_ptr connection_ptr_no_tls;
//typedef autobahn::wamp_websocketpp_websocket_transport<websocketpp::config::asio_tls_client> websocket_transport;

class orderbook_dydx: public orderbook{
public:
	boost::lockfree::spsc_queue<transaction, boost::lockfree::capacity<1024>>* pending_arbitrum_transaction_reports = nullptr;
	std::vector<boost::lockfree::stack<defi_price2, boost::lockfree::capacity<256>>* >  defi_prices_queue_vec;
	orderbook_dydx();

	orderbook_dydx(const orderbook_dydx& x){
		currency = x.currency;
		min_sequence_num = 0;
		num_kraken_messages_sent = 0;
		do_reinitialize_orderbook = false;
	};
	orderbook_dydx(monitor_trading* monitor_trading1); //: orderbook(sym1,sym2){};

	long numBlocksRead = 0;
	long numMsgsReceived = 0;
	boost::asio::io_service ioService;
	bool getPendingTransactions;				

	std::string log_id;
	
	void end(){};
	//void request_data();
	void start_and_monitor_orderbook22();

	std::shared_ptr<boost::asio::io_service::work> work2;

    boost::lockfree::spsc_queue<pass_place_order_fixed,boost::lockfree::capacity<1024>>* trade_reports = nullptr;
	boost::lockfree::spsc_queue<pass_place_order_fixed,boost::lockfree::capacity<1024>>* order_cancel_reports = nullptr;
	boost::lockfree::spsc_queue<pass_place_order_fixed,boost::lockfree::capacity<1024>>* order_time_reports = nullptr;
	boost::lockfree::stack<pass_place_order_fixed,boost::lockfree::capacity<256>>*  sent_orders = nullptr;
	boost::lockfree::stack<pass_place_order_fixed,boost::lockfree::capacity<256>>* suspected_orders_kraken = nullptr;
	void start122(std::string uri) ;
	order* order_rec_list = nullptr;
	std::atomic<long>* order_rec_length = nullptr;
	boost::lockfree::stack<gdax_trade,boost::lockfree::capacity<4096>>*  kraken_trades = nullptr;

	long trade_channel_id;
	long orderbook_channel_id;
	int debug_id = 0;
	
	long min_sequence_num ;
	long num_kraken_messages_sent;
	bool do_reinitialize_orderbook;
	void reinitialize_orderbook(){}; //this is an implimentation of virtual function which are needed
	void update_book_with_string(){}; //this is an implimentation of virtual function which are needed
	void update_book_with_string(std::string str22){}; //this is an implimentation of virtual function which are needed
	void start22();
	void operator=(const orderbook_dydx& rhs) const{
		
	}

    std::vector<order_done> orders_done;
    long size_orders_done = 50000;
    long orders_done_last = 0;

	boost::thread_group threadpool;
	boost::asio::io_service* io;
	client *ws_client;
	void on_open(websocketpp::connection_hdl hdl) ;
	void on_message(websocketpp::connection_hdl hdl, message_ptr bb) ;

	boost::lockfree::stack<pass_ob_data,boost::lockfree::capacity<4096>>*  queue_for_rest_quote_data;
	bool is_non_websocket = false;

};


#endif
