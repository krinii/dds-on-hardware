// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file MyType.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace { char dummy; }
#endif

#include "MyType.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

MyType::MyType()
{
    // m_value com.eprosima.idl.parser.typecode.PrimitiveTypeCode@e720b71
    m_value = 0;
    // m_message com.eprosima.idl.parser.typecode.StringTypeCode@74ad1f1f
    m_message ="";

}

MyType::~MyType()
{


}

MyType::MyType(const MyType &x)
{
    m_value = x.m_value;
    m_message = x.m_message;
}

MyType::MyType(MyType &&x)
{
    m_value = x.m_value;
    m_message = std::move(x.m_message);
}

MyType& MyType::operator=(const MyType &x)
{

    m_value = x.m_value;
    m_message = x.m_message;

    return *this;
}

MyType& MyType::operator=(MyType &&x)
{

    m_value = x.m_value;
    m_message = std::move(x.m_message);

    return *this;
}

size_t MyType::getMaxCdrSerializedSize(size_t current_alignment)
{
    size_t initial_alignment = current_alignment;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + 255 + 1;


    return current_alignment - initial_alignment;
}

size_t MyType::getCdrSerializedSize(const MyType& data, size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);


    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4) + data.message().size() + 1;


    return current_alignment - initial_alignment;
}

void MyType::serialize(eprosima::fastcdr::Cdr &scdr) const
{

    scdr << m_value;
    scdr << m_message;
}

void MyType::deserialize(eprosima::fastcdr::Cdr &dcdr)
{

    dcdr >> m_value;
    dcdr >> m_message;
}

/*!
 * @brief This function sets a value in member value
 * @param _value New value for member value
 */
void MyType::value(int32_t _value)
{
m_value = _value;
}

/*!
 * @brief This function returns the value of member value
 * @return Value of member value
 */
int32_t MyType::value() const
{
    return m_value;
}

/*!
 * @brief This function returns a reference to member value
 * @return Reference to member value
 */
int32_t& MyType::value()
{
    return m_value;
}

/*!
 * @brief This function copies the value in member message
 * @param _message New value to be copied in member message
 */
void MyType::message(const std::string &_message)
{
m_message = _message;
}

/*!
 * @brief This function moves the value in member message
 * @param _message New value to be moved in member message
 */
void MyType::message(std::string &&_message)
{
m_message = std::move(_message);
}

/*!
 * @brief This function returns a constant reference to member message
 * @return Constant reference to member message
 */
const std::string& MyType::message() const
{
    return m_message;
}

/*!
 * @brief This function returns a reference to member message
 * @return Reference to member message
 */
std::string& MyType::message()
{
    return m_message;
}

size_t MyType::getKeyMaxCdrSerializedSize(size_t current_alignment)
{
    size_t current_align = current_alignment;





    return current_align;
}

bool MyType::isKeyDefined()
{
   return false;
}

void MyType::serializeKey(eprosima::fastcdr::Cdr &scdr) const
{
    (void) scdr;
     
     
}
