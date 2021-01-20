#include <iostream>
#include <WebSocketClient.h>
using namespace std;
using namespace cyanray;

int main()
{
	const string ws_uri = "ws://localhost:5539/chat?sessionkey=123";

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
	while (true)
	{
		getline(std::cin, c);
		if (c == "quit")
		{
			client.Close();
			break;
		}
		client.SendText(c);
	}

	return 0;
}