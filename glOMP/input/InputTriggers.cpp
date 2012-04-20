/*
 * InputTriggers.cpp
 *
 *  Created on: Apr 18, 2012
 *      Author: jgraves
 */

#include "InputTriggers.h"
#include "Input.h"

#include <iostream>

namespace glomp {
namespace input {

KeyUpTrigger::KeyUpTrigger(int key_code) {
	this->key_code = key_code;
	this->prev_state = true;
}

bool KeyUpTrigger::check(Input &input) {
	bool state = (input.key_state(this->key_code) == GLFW_PRESS);
	bool result = (state == false && state != this->prev_state);
	this->prev_state = state;
	return result;
}

KeyDownTrigger::KeyDownTrigger(int key_code) {
	this->key_code = key_code;
	this->prev_state = false;
}

bool KeyDownTrigger::check(Input &input) {
	bool state = (input.key_state(this->key_code) == GLFW_PRESS);
	bool result = (state == true && state != this->prev_state);
	this->prev_state = state;
	return result;
}

KeyIsUpTrigger::KeyIsUpTrigger(int key_code) {
	this->key_code = key_code;
}

bool KeyIsUpTrigger::check(Input &input) {
	return (input.key_state(this->key_code) == GLFW_RELEASE);
}

KeyIsDownTrigger::KeyIsDownTrigger(int key_code) {
	this->key_code = key_code;
}

bool KeyIsDownTrigger::check(Input &input) {
	return (input.key_state(this->key_code) == GLFW_PRESS);
}

}
} /* namespace glomp */
