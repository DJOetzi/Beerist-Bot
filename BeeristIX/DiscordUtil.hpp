#pragma once
#include <discordcoreapi/Index.hpp>

namespace Utility::Discord
{
	inline auto buildActivity(std::string name, DiscordCoreAPI::ActivityType type) -> DiscordCoreAPI::ActivityData
	{
		DiscordCoreAPI::ActivityData activity{};

		activity.name = name;
		activity.type = type;

		return activity;
	}

	inline auto repeatedFunctionBuilder(std::function<void(DiscordCoreAPI::DiscordCoreClient*)> func, uint64_t interval, bool repeated) -> DiscordCoreAPI::RepeatedFunctionData
	{
		DiscordCoreAPI::RepeatedFunctionData function01{};

		function01.function = func;
		function01.intervalInMs = interval;
		function01.repeated = repeated;

		return function01;
	}
}
