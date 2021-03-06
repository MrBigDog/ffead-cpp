/*
	Copyright 2009-2012, Sumeet Chhetri

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
/*
 * TestForm.cpp
 *
 *  Created on: Jul 14, 2011
 *      Author: sumeet
 */

#include "TestForm.h"

TestForm::TestForm() {
	num = 0;
}

std::string TestForm::getChe() const
{
    return che;
}

int TestForm::getNum() const
{
    return num;
}

std::string TestForm::getTxt() const
{
    return txt;
}

void TestForm::setChe(std::string che)
{
    this->che = che;
}

void TestForm::setNum(int num)
{
    this->num = num;
}

void TestForm::setTxt(std::string txt)
{
    this->txt = txt;
}

TestForm::~TestForm() {
	// TODO Auto-generated destructor stub
}
