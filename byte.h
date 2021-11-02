#pragma once

// ����� ������� �������� ������ �������������� ���� � int ��� ���, ��� �������� char, ��� ��������� �������� �������������
// ��������� ����� � ���� int ����� �������. ��������� 1 �������� ��� int
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