#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

#include "../res/TelemetryMessage.h"

class TelemetryMessageQueue
{
public:
	//If the queue is closed returns false.
	bool Push(const TelemetryMessage& message);

	//Transfer the front message of the queue into the passed in message. If no messages, wait for message.
	bool WaitAndPop(TelemetryMessage& message);

	//Prevent new messges
	void Close();

private:
	std::queue<TelemetryMessage> messages;
	bool isClosed = false;
	std::mutex queueLock;
	std::condition_variable cv;
};