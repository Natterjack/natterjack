// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#include "notifications.h"

namespace natterjack
{
	void NotificationCollection::addNotification(const std::string& text)
	{
		notifications.push_back(text);
	}

	bool NotificationCollection::hasNotifications()
	{
		return notifications.size() > 0;
	}
		
	std::vector<std::string> NotificationCollection::getNotifications()
	{
		return notifications;
	}
}
