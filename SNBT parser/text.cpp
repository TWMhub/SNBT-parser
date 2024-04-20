#include "SNBT.h"

namespace depozit 
{
	text::text() {
		this->posInFile = 0;
		this->type = depozit::type::unknown;
		this->originalString = L"";
		this->translatedString = L"";
	}
	text::text(unsigned posInFile, depozit::type type, std::wstring originalString) {
		this->posInFile = posInFile;
		this->type = type;
		this->originalString = originalString;
		this->translatedString = L"";
	}
	text::text(unsigned posInFile, depozit::type type, std::wstring originalString, std::wstring translatedString) {
		this->posInFile = posInFile;
		this->type = type;
		this->originalString = originalString;
		this->translatedString = translatedString;
	}
	void text::init(unsigned posInFile, depozit::type type, std::wstring originalString) {
		this->posInFile = posInFile;
		this->type = type;
		this->originalString = originalString;
		this->translatedString = L"";
	}
	void text::init(unsigned posInFile, depozit::type type, std::wstring originalString, std::wstring translatedString) {
		this->posInFile = posInFile;
		this->type = type;
		this->originalString = originalString;
		this->translatedString = translatedString;
	}

	int text::getPosInFile() {
		return this->posInFile;
	}
	depozit::type text::getType() {
		return this->type;
	}
	std::wstring text::getTypeByWstring() {
		if (this->type == depozit::type::title)
			return L"title";
		else if (this->type == depozit::type::subtitle)
			return L"subtitle";
		else if (this->type == depozit::type::description)
			return L"description";
		else
			return L"unknown";
	}
	std::wstring text::getOriginalText() {
		return this->originalString;
	}
	std::wstring text::getTranslatedString() {
		return this->translatedString;
	}

	std::wstring text::typeToWstring(depozit::type type) {
		if (type == depozit::type::title)
			return L"title";
		else if (type == depozit::type::subtitle)
			return L"subtitle";
		else if (type == depozit::type::description)
			return L"description";
		else
			return L"unknown";
	}
	void text::clear() {
		this->posInFile = 0;
		this->type = depozit::type::unknown;
		this->originalString = L"";
		this->translatedString = L"";
	}
}