#include "server.hpp"
#include "client.hpp"

#include <iostream>
#include <thread>
#include <boost/program_options.hpp>
#include <tuple>
#include <optional>

std::tuple<char, std::optional<std::string>, unsigned short> command_line_parse(int argc, const char *argv[]) {
	boost::program_options::options_description description("options");
	description.add_options()
		("server", boost::program_options::value<unsigned short>())
		("client", boost::program_options::value<std::vector<std::string>>()->multitoken());

	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, description), vm);
	boost::program_options::notify(vm);
	char cli_or_srv;
	if (vm.count("server")) cli_or_srv = 's';
	else if (vm.count("client")) cli_or_srv = 'c';
	std::optional<std::string> ip;
	unsigned short port;
	if (cli_or_srv == 'c') {
		std::vector<std::string> ip_and_port = vm["client"].as<std::vector<std::string>>();
		ip = ip_and_port.at(0);
		port = std::stoi(ip_and_port.at(1));
	} else if (cli_or_srv == 's') {
		port = vm["server"].as<unsigned short>();
		ip = std::nullopt;
	}
	return std::make_tuple(cli_or_srv, ip, port);
}

int main(int argc, const char *argv[])
{
	try {
		if (sodium_init() == -1) return 1;

		auto [cli_or_srv, ip, port] = command_line_parse(argc, argv);
		boost::asio::io_service io;
		boost::asio::io_service::work work(io);
		std::string msg;
		c_session session = [&cli_or_srv, &port, &ip, &io](){
			if (cli_or_srv == 's') {
				c_server s(io);
				return s.start_accept(port);
			}
			if (cli_or_srv == 'c') {
				c_client c(io);
				return c.start_connect(ip.value(), port);
			}
		}();
		session.start();
		std::thread cli([&io](){io.run();});
		while(true) {
			std::cin>>msg;
			session.write(msg);
		}
		cli.join();
	} catch (const std::exception & e){
		std::cout<<e.what()<<std::endl;
	}
	return 0;
}



