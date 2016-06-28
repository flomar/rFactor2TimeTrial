// TimeTrialClient.cpp

#include "TimeTrialClient.hpp"
#include "TimeTrialUtilities.hpp"

Client::Client() :
	m_connected(false),
	m_socket(0) {
	
}

Client::~Client() {
	WSACleanup();
}

Client &Client::instance() {
	static Client client;
	return client;
}

bool Client::connectToServer(const int _port) {
	WSADATA wsaData;
	if (WSAStartup(0x0202, &wsaData) != 0) {
		return false;
	}
	if (wsaData.wVersion != 0x0202) {
		return false;
	}
	SOCKADDR_IN localhost;
	localhost.sin_family = AF_INET;
	localhost.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	localhost.sin_port = htons(_port);
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		return false;
	}
	if (connect(m_socket, (struct sockaddr*)(&localhost), sizeof(localhost)) == SOCKET_ERROR) {
		return false;
	}
	m_connected = true;
	return true;
}

bool Client::disconnectFromServer() {
	if (m_socket) {
		closesocket(m_socket);
	}
	m_connected = false;
	return true;
}

bool Client::sendMessage(const ClientServerMessage &_message) {
	if (!m_connected) return false;
	const bool result = (send(m_socket, (const char*)(&_message), sizeof(_message), 0) != SOCKET_ERROR);
	return result;
}
