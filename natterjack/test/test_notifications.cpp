#include <gtest/gtest.h>

#include "notifications.h"

using namespace natterjack;

namespace {
	static NotificationCollection CreateNotificationCollection() {
		return NotificationCollection();
	}
}

TEST(NotificationCollection,Create_Succeeds) {
	auto notes = new NotificationCollection();
}

TEST(NotificationCollection,AddNotification_StoresNotification) {
	auto notes = CreateNotificationCollection();

	ASSERT_FALSE(notes.hasNotifications());

	notes.addNotification("A notification");

	ASSERT_TRUE(notes.hasNotifications());

}
