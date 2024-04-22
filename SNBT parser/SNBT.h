#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <Windows.h>

namespace fs = std::filesystem;

namespace depozit {

	enum class type
	{
		title,
		subtitle,
		description,
		unknown
	};

	std::wstring stringToWstring(const std::string& str);
	std::string wstringToString(const std::wstring& wstr);

	class text
	{
	//functuions
	public:
		text();
		text(unsigned, type, std::wstring);
		text(unsigned, type, std::wstring, std::wstring);
		void init(unsigned, type, std::wstring);
		void init(unsigned, type, std::wstring, std::wstring);

		int getPosInFile();
		type getType();
		std::wstring getTypeByWstring();
		std::wstring getOriginalText();
		std::wstring getTranslatedString();

		std::wstring typeToWstring(depozit::type);
		void clear();

	//vars
	private:
		unsigned posInFile;
		type type;
		std::wstring originalString;
		std::wstring translatedString;
	};

	class snbt
	{
	//functuions
	public:
		snbt();
		snbt(fs::path);
		void init(fs::path);

		std::wstring getFileByWstring();
		std::wstring getTextsByWstring();
		std::vector<std::wstring> getFileByVecWstring();
		std::vector<text> getTextByVec();

		void clear();
	private:
		std::vector<std::wstring> readFileByVecWstring(fs::path);
		void parsing();
		void getTitle(unsigned, std::wstring);
		void getSubtitle(unsigned, std::wstring);
		void getDescription(unsigned, unsigned, const std::vector<std::wstring>&);
	//vars
	private:
		std::wstring fullFile;
		std::vector<std::wstring> fileByLine;
		std::vector<text> arrayTexts;
	};

}