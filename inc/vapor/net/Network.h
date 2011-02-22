/************************************************************************
*
* vapor3D Server � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "net/Message.h"
#include "net/MessageHandler.h"
#include "ConcurrentQueue.h"

namespace vapor {

//-----------------------------------//

class Network
{
public:

	~Network();

	// Initializes the server context.
	bool init( int numThreads = 1 );

	// Sends a message to the host.
	void sendMessage( const MessagePtr& message );

	// Creates a new server socket.
	bool createServerSocket( const std::string& uri );

	// Creates a new client socket.
	bool createClientSocket( const std::string& uri );

	// Shutdowns the server.
	void shutdown();

	// Waits for messages.
	void waitMessages();

	// Dispatchs messages to their handlers.
	void dispatchMessages();

protected:

	// Logs an ZeroMQ error.
	void error(const char* str);

	// Keeps the message handlers.
	typedef std::map< MessageType::Enum, MessageHandler* > MessageHandlersMap;
	MessageHandlersMap messageHandlers;

	// Queue of undispatched messages.
	ConcurrentQueue<MessagePtr> messages;

	// ZeroMQ context.
	typedef void* ZMQContext;
	ZMQContext context;

	// ZeroMQ socket;
	typedef void* ZMQSocket;
	ZMQSocket socket;
};

//-----------------------------------//

} // end namespace