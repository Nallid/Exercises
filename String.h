#pragma once
#include <iostream>
#include <exception>

constexpr auto OUT_OF_RANGE = -1;
constexpr auto NULL_POINTER = 0;
constexpr auto MEM_LEAK = 1;

class String {
private:
	char* m_buffer;
	unsigned int m_size;

	void terminate() { //adds terminator character, got sick of writing this one liner a lot, so I made it into a function.

		m_buffer[m_size] = 0;

	}

public:
	String(const char* buffer) {

		m_size = strlen(buffer);
		m_buffer = new char[m_size + 1];

		memcpy(m_buffer, buffer, m_size);
		terminate();

	}

	~String() {

		delete[] m_buffer;

	}

	String(const String& copy) {

		m_size = copy.m_size;
		m_buffer = new char[m_size + 1];
		memcpy(m_buffer, copy.m_buffer, m_size);
		terminate();
		
		std::cout << "Copied" << std::endl;

	}

	char at(unsigned int index) {

		return m_buffer[index];

	}

	char front() {
		if (m_size != 0)
			return at(0);
	}

	char back() {

		if (m_size != 0)
			return at(strlen(m_buffer + 1));

	}

	void append(const char* string) {

		m_size += strlen(string);

		operator+(string);

	}

	void prepend(const char* string) {

		m_size += strlen(string);
		char* t_buffer = m_buffer;
		m_buffer = new char[m_size + 1];

		m_buffer = (char*)string;
		operator+(t_buffer);

	}

	bool is_empty() {

		return m_size > 0;

	}

	String& operator+(const String& rhs) {

		m_size = m_size + rhs.m_size;
		char* t_buffer = m_buffer;
		m_buffer = new char[m_size + 1];
		
		strcpy(m_buffer, t_buffer);
		strcat(m_buffer, rhs.m_buffer);
		terminate();
		
		return *this;

	}

	String& operator+=(const String& rhs) {

		return operator+(rhs);

	}

	bool operator==(const String& string) {

		return *this == string;

	}

	bool operator==(unsigned int number) {

		return number == 0 && m_size == 0;

	}

	char& operator[](unsigned int index) throw (int) {

		char res;

		try {

			if (index > -1 || index < m_size)
				res = m_buffer[index];
			else
				throw OUT_OF_RANGE;

			if (m_buffer[index] == NULL)
				throw NULL_POINTER;

			if (m_buffer == nullptr)
				throw MEM_LEAK;

		}
		catch (int e) {

			std::cerr << "[INVALID INDEX]: ERROR " << e;
			res = (char&)e;

		}

		return res;
	}

	String& operator=(const String& string) {

			return *this = String(string);

	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string); //Function can access String's private members with friend
};

std::ostream& operator<<(std::ostream& stream, const String& string) {

	stream << string.m_buffer;
	return stream;

}