#pragma once
class StringClass
{
	public:
		StringClass(const char* string);
		~StringClass();
		StringClass(const StringClass& other);

	private:
		const char* charArray;

	public:
		const char* getCharArray() const;
		int getLength() const;
		void append(const char* string);
		void empty();
};

