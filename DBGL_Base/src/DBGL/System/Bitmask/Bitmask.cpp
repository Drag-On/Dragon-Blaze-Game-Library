//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Bitmask/Bitmask.h"

namespace dbgl
{
    Bitmask::Bitmask(int bits)
    {
	m_length = sizeof(int) / sizeof(char);
	m_pData = new char[m_length];
	char* ptr = (char*)&bits;
	for (unsigned int i = 0; i < m_length; i++)
	    m_pData[i] = ptr[i];
    }

    Bitmask::Bitmask(std::string bits)
    {
	m_length = (int) ceil((float) bits.length() / CHAR_BIT);
	m_pData = new char[m_length];
	for(unsigned int i = 0; i < m_length; i++)
	    m_pData[i] = 0;
	fromString(bits);
    }

    Bitmask::Bitmask(char* bits, unsigned int length)
    {
	m_length = length;
	m_pData = new char[length];
	for(unsigned int i = 0; i < length; i++)
	    m_pData[i] = bits[i];
    }

    Bitmask::Bitmask(Bitmask const& other)
    {
	m_length = other.m_length;
	m_pData = new char[other.m_length];
	for (unsigned int i = 0; i < other.m_length; i++)
	    m_pData[i] = other.m_pData[i];
    }

    Bitmask::~Bitmask()
    {
	delete [] m_pData;
    }

    unsigned int Bitmask::getSize() const
    {
	return m_length * CHAR_BIT;
    }

    void Bitmask::set(unsigned int index)
    {
	if(getSize() > index)
	{
	    unsigned int byteNo = index / CHAR_BIT;
	    unsigned char bitNo = index % CHAR_BIT;
	    m_pData[byteNo] |= (1 << bitNo);
	}
	else
	{
	    std::stringstream msg;
	    msg << "Bit index out of bounds: " << index;
	    throw std::out_of_range(msg.str());
	}
    }

    void Bitmask::set(int mask)
    {
	Bitmask other(mask);
	for(unsigned int i = 0; i < other.getSize(); i++)
	{
	    if(other.get(i))
		set(i);
	}
    }

    void Bitmask::clear(unsigned int index)
    {
	if (getSize() > index)
	{
	    unsigned int byteNo = index / CHAR_BIT;
	    unsigned char bitNo = index % CHAR_BIT;
	    m_pData[byteNo] &= ~(1 << bitNo);
	}
	else
	{
	    std::stringstream msg;
	    msg << "Bit index out of bounds: " << index;
	    throw std::out_of_range(msg.str());
	}
    }

    void Bitmask::clear(int mask)
    {
	Bitmask other(mask);
	for(unsigned int i = 0; i < other.getSize(); i++)
	{
	    if(other.get(i))
		clear(i);
	}
    }

    void Bitmask::toggle(unsigned int index)
    {
	if (getSize() > index)
	{
	    unsigned int byteNo = index / CHAR_BIT;
	    unsigned char bitNo = index % CHAR_BIT;
	    m_pData[byteNo] ^= (1 << bitNo);
	}
	else
	{
	    std::stringstream msg;
	    msg << "Bit index out of bounds: " << index;
	    throw std::out_of_range(msg.str());
	}
    }

    void Bitmask::toggle(int mask)
    {
	Bitmask other(mask);
	for(unsigned int i = 0; i < other.getSize(); i++)
	{
	    if(other.get(i))
		toggle(i);
	}
    }

    bool Bitmask::get(unsigned int index) const
    {
	if (getSize() > index)
	{
	    unsigned int byteNo = index / CHAR_BIT;
	    unsigned char bitNo = index % CHAR_BIT;
	    return m_pData[byteNo] & (1 << bitNo);
	}
	else
	{
	    std::stringstream msg;
	    msg << "Bit index out of bounds: " << index;
	    throw std::out_of_range(msg.str());
	}
	return false;
    }

    bool Bitmask::isSet(int mask) const
    {
	Bitmask other(mask);
	for(unsigned int i = 0; i < other.getSize(); i++)
	{
	    if(other.get(i) && (i > getSize() || !get(i)))
		return false;
	}
	return true;
    }

    void Bitmask::fromString(std::string bits)
    {
	unsigned int length = bits.length();
	if(length > getSize())
	    length = getSize();
	for(unsigned int i = 0; i < length; i++)
	{
	    if(bits[i] != '0')
		set(i);
	    else
		clear(i);
	}
    }

    std::string Bitmask::toString() const
    {
	std::string str = "";
	for (unsigned int i = 0; i < getSize(); i++)
	{
	    str += get(i) ? '1' : '0';
	}
	return str;
    }

    Bitmask& Bitmask::operator=(Bitmask const& rhs)
    {
	delete [] m_pData;
	m_length = rhs.m_length;
	m_pData = new char[rhs.m_length];
	for (unsigned int i = 0; i < rhs.m_length; i++)
	    m_pData[i] = rhs.m_pData[i];
	return *this;
    }

    Bitmask& Bitmask::operator=(char const& rhs)
    {
	delete[] m_pData;
	m_length = 1;
	m_pData = new char;
	m_pData[0] = rhs;
	return *this;
    }

    Bitmask& Bitmask::operator=(int const& rhs)
    {
	delete[] m_pData;
	m_length = sizeof(int) / sizeof(char);
	m_pData = new char[m_length];
	char* ptr = (char*)&rhs;
	for (unsigned int i = 0; i < m_length; i++)
	    m_pData[i] = ptr[i];
	return *this;
    }
}
