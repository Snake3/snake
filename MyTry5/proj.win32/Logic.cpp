#include "Logic.h"

Logic* Logic::mInstance = new Logic();

Logic* Logic::getInstance()
{
	return mInstance;
}

Logic::Logic()
{

}

Logic::~Logic()
{
	delete mInstance;
}