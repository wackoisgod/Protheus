#include "CBuffer.h"

/*************************************************************************
Protheus Source File.
Copyright (C), Protheus Studios, 2013-2014.
-------------------------------------------------------------------------

Description:

-------------------------------------------------------------------------
History:
- 14:07:2014: Waring J.
*************************************************************************/
#pragma once

#include "BufferBase.h" 



CBuffer::CBuffer(const CBuffer& b, bool copy) {
	init(b.data<void>(), b.size(), copy);
}


CBuffer::CBuffer(void* _data, const unsigned _size,const bool copy) {
	if (_size == 0){
		m_data = nullptr;
		m_size = 0;
		return;
	}

	if (copy){
		m_data = new char[_size];
		memcpy(m_data, _data, _size); 
	}
	else
		m_data = _data;

	wasCopied = copy;
	m_size = _size;
}

CBuffer::CBuffer(const unsigned _size)
{
	if (_size == 0)
		m_data = nullptr; 
	else
		m_data = new char[_size];
	wasCopied = false;
	m_size = _size; 
}

CBuffer::CBuffer()
{
	wasCopied = false;
	m_size = 0;
	m_data = nullptr;
}

CBuffer::CBuffer(CBuffer&& b){
	m_data = b.data();
	m_size = b.size();
	wasCopied = b.wasCopied;
	b.dereference();
}

CBuffer& CBuffer::operator=(CBuffer&& b){ 
	if (this == &b)
		return *this;  
	
	m_data = b.data();
	m_size = b.size(); 
	wasCopied = b.wasCopied;
	b.dereference();
	return *this;
}
 

CBuffer& CBuffer::operator=(const CBuffer& b){
	 
	if (this == &b)
		return *this;  

	this->init(b.data<void>(), b.size(), true);
	return *this;
}

CBuffer::~CBuffer()
{
	if(wasCopied)
		delete [] m_data;
	m_data = nullptr;
}

void CBuffer::init(const void* _data, const unsigned _size, const bool copy){
	// Check if data has been initialized
	if (m_data != nullptr)
		delete [] m_data;

	if (copy){
		m_data = new char[_size];
		memcpy(m_data, _data, _size);
	}
	else
		m_data = const_cast<void*>(_data);

	wasCopied = copy;
	m_size = _size;
}

void CBuffer::init(const unsigned _size){
	init(new char[_size], _size, false);
}

void CBuffer::dereference(){
	m_data = nullptr;
	m_size = 0;
}

void* CBuffer::data() const{
	return m_data;
}
unsigned CBuffer::size() const{
	return m_size;
}
 
bool CBuffer::isEmpty() const { 
	return (m_size == 0) ? true : false;
}

void CBuffer::resize(const unsigned size){
	const auto old_data = m_data;
	m_data = new char[size];
	
	if (m_size > size)
		// Reducing
		memcpy(m_data, old_data, size);
	else 
		// Increasing
		memcpy(m_data, old_data, m_size);

	m_size = size;
	delete [] old_data;
}

void* CBuffer::at(const unsigned pos) const {
	if (pos < m_size)
		return reinterpret_cast<char*>(m_data) + pos;
	return nullptr;
}
void* CBuffer::operator[](const unsigned pos) const{ 
	return reinterpret_cast<char*>(m_data)+pos;
}
  