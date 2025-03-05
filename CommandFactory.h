//
// Created by wiley on 3/4/2025.
//

#pragma once
#include <functional>
#include <unordered_map>
#include <memory>

#include "Command.h"

/// Easily create server commands that match a given TokenType
class CommandFactory {
public:
	using CommandPtr = std::unique_ptr<IServerCommand>;

	/// Return a Server ICommand that matches a TokenType, otherwise a nullptr
	static CommandPtr Create(TokenType type);
};

