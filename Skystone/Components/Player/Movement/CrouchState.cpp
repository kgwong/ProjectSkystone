#include "CrouchState.h"



CrouchState::CrouchState(GameObject& owner)
	:PlayerState(owner)
{
}


CrouchState::~CrouchState()
{
}

std::string CrouchState::name()
{
	return "CrouchState";
}
