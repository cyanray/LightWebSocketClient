# LightWebSocketClient
A simple cross-platform WebSocket client.

![](https://github.com/cyanray/LightWebSocketClient/workflows/build/badge.svg)

## Features

* C++11
* Light
* Cross-platform
* Easy to use

## Usage

```c++
#include <iostream>
#include <WebSocketClient.h>
using namespace std;
using namespace cyanray;

int main()
{
  const string ws_uri = "ws://localhost:5539/chat?sessionkey=123";

  WebSocketClient client;
  try
  {
    client.Connect(ws_uri);
    cout << "working..." << endl;
  }
  catch (const std::exception& ex)
  {
    cout << ex.what() << endl;
    return 1;
  }

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
  while (getline(std::cin, c);)
  {
    if (c == "quit")
    {
      client.Close();
      break;
    }
    client.SendText(c);
  }

  return 0;
}
```

## Documentation

See comments in **WebSocketClient.h**.


