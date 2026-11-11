#include "../res/TelemetryMessageQueue.h"

bool TelemetryMessageQueue::Push(const TelemetryMessage& message)
{
	if (isClosed)
		return false;

	messages.push(message);
	return true;
}

bool TelemetryMessageQueue::WaitAndPop(TelemetryMessage& message)
{
	message = std::move(messages.front());
	messages.pop();
	return true;
}

void TelemetryMessageQueue::Close()
{
	isClosed = true;
}
