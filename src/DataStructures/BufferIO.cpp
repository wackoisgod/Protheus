#include "BufferIO.h"

using namespace Pro;
using namespace Util;

// sets the position of the writer
void BufferIO::setPosition(const unsigned position){
	m_head = position;
}
// returns the position of the writer
unsigned BufferIO::getPosition() const{
	return m_head;
}
// skips over the current writing position
void BufferIO::skip(const int position){
	m_head += position;
}
// get's the internal buffers size
unsigned BufferIO::getBufferSize() const{
	return m_buffer->size();
}
unsigned BufferIO::find(const char deliminator) const{
	register auto buf = (char*)m_buffer->at(m_head);
	while (*buf != deliminator)
		++buf;
	// include the deliminator
	++buf;
	return buf - (char*)m_buffer->at(m_head);
}
 