#include "Conversation.hpp"


Conversation::Conversation(Request* r) {
	request = r;
	lock = new Lock();
}
