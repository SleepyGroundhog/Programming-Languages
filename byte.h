#pragma once

// Класс который способен неявно конвертировать себя в int при том, что является char, что похволяет избегать необходимости
// приводить число к типу int перед выводом. Реализует 1 байтовый тип int
class byte{
	char m_byte = 0;
public:
	operator int() const { return (int)m_byte; }
	byte(): m_byte(0) {}
	byte(const byte& b) {
		if (this != &b)
			m_byte = int(b);
	}

	byte& operator=(int integer) {
		m_byte = integer;
		return *this;
	}
};