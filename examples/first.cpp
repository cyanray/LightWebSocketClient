#include <iostream>
#include <future>
#include <WebSocketClient.h>
using namespace std;
using namespace cyanray;

int main()
{
	const string ws_uri = "ws://localhost:5539/command?authkey=RF4r8uEN";

	WebSocketClient client;
	client.Connect(ws_uri);
	// client.Connect("127.0.0.1", 5539, "/");
	cout << "working..." << endl;

	client.OnTextReceived([](WebSocketClient& client, string text)
		{
			cout << "received: " << text << endl;
		});

	client.OnLostConnection([ws_uri](WebSocketClient& client, int code)
		{
			cout << "Lost connection: " << code << endl;
			while (true)
			{
				try
				{
					client.Connect(ws_uri);
					cout << "Reconnected." << endl;
					break;
				}
				catch (const std::exception& ex)
				{
					cout << ex.what() << endl;
				}
			}
		});

	string c;
	while (getline(std::cin, c))
	{
		if (c == "ping")
		{
			client.Ping();
		}
		else if (c == "quit")
		{
			client.Close();
			break;
		}
		else
		{
			client.SendText(c);
		}
	}
	return 0;
}