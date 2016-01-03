#pragma once

#include "Command.h"

#include <queue>

class CommandQueue
{
	public:
	void Push(const Command & command)
	{
		queue_.push(command);
	}

	Command Pop()
	{
		Command command = queue_.front();
		queue_.pop();
		return command;
	}

	bool Empty() const
	{
		return queue_.empty();
	}

	private:
	std::queue<Command>	queue_;
};