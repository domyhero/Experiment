// =====================================================================================
// 
//       Filename:  asio_study.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年07月27日 20时39分16秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

using namespace boost::asio;
using boost::system::error_code;
using ip::tcp;

class HelloService
{
public:
	HelloService(io_service &iosev, int listen_port) 
		: iosev_(iosev), acceptor_(iosev, tcp::endpoint(tcp::v4(), listen_port))
	{
	}

	void start()
	{
		boost::shared_ptr<tcp::socket> psocket(new tcp::socket(iosev_));
		acceptor_.async_accept(*psocket, boost::bind(&HelloService::accept_handler, this, psocket, _1));
	}

	void accept_handler(boost::shared_ptr<tcp::socket> psocket, error_code ec)
	{
		if (ec) {
			return;
		}
		std::cout << psocket->remote_endpoint().address() << std::endl;

		boost::shared_ptr<std::string> pstr(new std::string("hello async world!"));
		psocket->async_write_some(buffer(*pstr), boost::bind(&HelloService::write_handler, this, pstr, _1, _2));
	}

	void write_handler(boost::shared_ptr<std::string> pstr, error_code ec, size_t bytes_transferred)
	{
		if (ec) {
		      std::cout<< "发送失败!" << std::endl;
		} else {
		      std::cout<< *pstr << " 已发送" << std::endl;
		}
	}

private:
	io_service &iosev_;
	ip::tcp::acceptor acceptor_;
};

int main(int argc, char *argv[])
{
	io_service iosev;

	HelloService service(iosev, 8086);

	service.start();

	iosev.run();

	return 0;
}

