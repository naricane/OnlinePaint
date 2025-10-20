#pragma once
#include <SDL3/SDL_messagebox.h>
#include <expected>
#include <format>
#include <iostream>
#include <string>

template<typename... Args>
void
panic(std::string_view message, const Args&... args)
{
	std::string str = std::vformat("{}", std::make_format_args(args...));
	std::cerr << str.data() << "\n";
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", str.data(), nullptr);
	std::abort();
}

template<typename T, typename E>
T
unwrap_or_abort(std::expected<T, E>&& exp)
{
	if (!exp) {
		panic("{}", exp.error());
	}
	return std::forward<T>(*exp);
}

struct SdlError
{
	std::string value;
};

template<>
struct std::formatter<SdlError> : std::formatter<std::string>
{
	auto format(SdlError error, format_context& ctx) const
	{
		return formatter<string>::format(std::format("{}", error.value), ctx);
	}
};
