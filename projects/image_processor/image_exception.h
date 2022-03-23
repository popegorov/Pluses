#pragma once

#include <exception>

class IncorrectInputOrOutputData : public std::exception {};

class IncorrectFilterInformation : public std::exception {};
