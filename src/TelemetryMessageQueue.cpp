#include "../res/TelemetryMessageQueue.h"

bool TelemetryMessageQueue::Push(const TelemetryMessage& message)
{
	if (isClosed)
		return false;


	std::lock_guard<std::mutex> lock(queueLock);
	messages.push(message);
	cv.notify_one();
	
	return true;
}

bool TelemetryMessageQueue::WaitAndPop(TelemetryMessage& message)
{
	//waits till the queue is not empty
	std::unique_lock<std::mutex> lock(queueLock);
	cv.wait(lock, [this] { return messages.empty(); });
	message = std::move(messages.front());
	messages.pop();
	
	return true;
}

void TelemetryMessageQueue::Close()
{
	isClosed = true;
	cv.notify_one();
}
