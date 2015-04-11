// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#pragma once

#include <vector>
#include <string>

namespace natterjack
{
	// Notification Collection
	//
	// Represents a colleciton of compiler notifiactions. Can be used
	// to track the current error state of the cmpilation process.
	class NotificationCollection
	{
	public:
		// Store notifications in this object to be viewed later
		void addNotification(const std::string& text);

		// Check if there are any notifications in this collection
		bool hasNotifications();
		
		// Get the Notifications stored in this object
		std::vector<std::string> getNotifications();

	private:
		std::vector<std::string> notifications;
	};
}
