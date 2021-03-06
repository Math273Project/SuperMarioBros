#pragma once
#define WIN32_LEAN_AND_MEAN
#include <string>
#include <exception>

namespace gameErrors
{
	// Error codes
	// Negative numbers are fatal errors that may require the game to be
	// shutdown.
	// Positive numbers are warnings that do not require the game to be
	// shutdown.
	const int FATAL_ERROR = -1;
	const int WARNING = 1;
}
// Game Error class. Thrown when an error is detected by the game engine.
// Inherits from std::exception
class GameError : public std::exception
{
private:
	int errorCode;
	std::string message;
public:
	// Default constructor
	GameError() throw() :errorCode(gameErrors::FATAL_ERROR),
		message("Undefined Error in game.") {}
	// Copy constructor
	GameError(const GameError& e) throw() : std::exception(e),
		errorCode(e.errorCode), message(e.message) {}
	// Constructor with args
	GameError(int code, const std::string &s) throw() :errorCode(code),
		message(s)
	{}
	// Assignment operator
	GameError& operator= (const GameError& rhs) throw()
	{
		std::exception::operator=(rhs);
		this->errorCode = rhs.errorCode;
		this->message = rhs.message;
	}
	// Destructor
	virtual ~GameError() throw() {};
	// Override what from base class
	virtual const char* what() const throw() { return this->getMessage(); }
	const char* getMessage() const throw() { return message.c_str(); }
	int getErrorCode() const throw() { return errorCode; }
};
