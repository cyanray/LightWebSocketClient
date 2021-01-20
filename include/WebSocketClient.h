#pragma once
#ifndef LightWSClient_include_WebSocketClient_H_
#define LightWSClient_include_WebSocketClient_H_
#include <string>
#include <vector>
#include <functional>
using std::vector;
using std::string;

namespace cyanray
{
	class WebSocketClient
	{
	public:
		template<typename T>
		using Callback = std::function<void(WebSocketClient&, T)>;

		enum class Status
		{
			Open, Closed
		};

		WebSocketClient();
		WebSocketClient(const WebSocketClient&) = delete;
		WebSocketClient& operator=(const WebSocketClient&) = delete;
		~WebSocketClient();

		Status GetStatus() const { return status; }
		void Connect(const string& ws_uri);
		void Connect(const string& hostname, int port, const string& path = "/");
		void Shutdown();
		void OnTextReceived(Callback<string> callback);
		void OnBinaryReceived(Callback<vector<uint8_t>> callback);
		void OnError(Callback<string> callback);
		void OnLostConnection(Callback<int> callback);
		void SendText(const string& text);
		void SendBinary(const char* data, size_t length);
		void SendBinary(const uint8_t* data, size_t length);
		void Ping();
		void Pong();
		void Close();
	private:
		void RecvLoop();
		Callback<string> TextReceivedCallback;
		Callback<vector<uint8_t>> BinaryReceivedCallback;
		Callback<string> ErrorCallback;
		Callback<int> LostConnectionCallback;
		Status status;
		// avoid including implementation-related headers.
		struct pimpl;
		pimpl* PrivateMembers;
	};
}


#endif // !LightWSClient_include_WebSocketClient_H_