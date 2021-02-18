#pragma once

#include "../lib/Request.hpp"
#include "../lib/Lock.hpp"


class Conversation {
	public:
	Request* request;
	Request* answer;
	Lock* lock;

	Conversation(Request* request);
};
