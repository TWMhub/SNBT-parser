#include "SNBT.h"

namespace depozit 
{
	//public
	snbt::snbt() {};
	snbt::snbt(fs::path pathToSnbtFile) {
		this->fileByLine = readFileByVecWstring(pathToSnbtFile);
		this->arrayTexts = parsing();
	}
	void snbt::init(fs::path pathToSnbtFile) {
		this->fileByLine = readFileByVecWstring(pathToSnbtFile);
		this->arrayTexts = parsing();
	}

	std::wstring snbt::getFileByWstring() {
		std::wstring out = L"";
		for (int i = 0; i < this->fileByLine.size(); i++) {
			out += fileByLine[i];
		}
		return out;
	}
	std::wstring snbt::getTextsByWstring() {
		std::wstring out = L"";
		for (int i = 0; i < this->arrayTexts.size(); i++) {
			if (this->arrayTexts[i].getType() != depozit::type::unknown) {
				out += std::to_wstring(this->arrayTexts[i].getPosInFile()) + L":";
				out += this->arrayTexts[i].getTypeByWstring() + L":";
				out += this->arrayTexts[i].getOriginalText() + L":";
				out += this->arrayTexts[i].getTranslatedString();
			}
		}
		return out;
	}
	std::vector<std::wstring> snbt::getFileByVecWstring() {
		return this->fileByLine;
	}
	std::vector<text> snbt::getTextByVec() {
		return this->arrayTexts;
	}

	void snbt::clear() {
		this->arrayTexts.clear();
		this->fileByLine.clear();
	}

	//private
	std::vector<std::wstring> snbt::readFileByVecWstring(fs::path path) {
		std::wifstream file(path);
		std::vector<std::wstring> fileByLine;
		std::wstring line;
		std::wstring fullFile;
		while (std::getline(file, line)) {
			fileByLine.push_back(line);
			fullFile += line + L"\n";
		}
		this->fullFile = fullFile;
		return fileByLine;
	}
	std::vector<text> snbt::parsing() {
		std::vector<text> text;
		if(this->fullFile.find(L"quests") != std::wstring::npos){
			for (int i = fullFile.find(L"quests"); i < this->fileByLine.size(); i++) {
				//дописать
				if (fileByLine[i].find(L"subtitle") != std::wstring::npos) {
					getSubtitle(i, fileByLine[i]);
				}
				else if (fileByLine[i].find(L"title") != std::wstring::npos) {
					getTitle(i, fileByLine[i]);
				}
				else if (fileByLine[i].find(L"description") != std::wstring::npos) {
					//this->arrayTexts.push_back(getDescription(fileByLine[i], i));
					//тут должна быть обработка строк, а не строки
					for (int j = i; j < this->fileByLine.size(); j++) {
						if (this->fileByLine[j].find(L"]") != std::wstring::npos) {
							getDescription(i, j, fileByLine);
							i = j;
							break;
						}
					}
				}
			}
		}
		else {
			std::cerr << "for unknown reasons, \"quests\" is missing from the file\n";
		}
		return text;
	}
	void snbt::getTitle(unsigned i, std::wstring line) {
		if (line.find(L"{") == std::wstring::npos) {
			depozit::text out(i, type::title, line.substr(line.find_first_of(L"\"") + 1, line.find_last_of(L"\"") - 1));
			this->arrayTexts.push_back(out);
		}
	}
	void snbt::getSubtitle(unsigned i, std::wstring line) {
		if (line.find(L"{") == std::wstring::npos) {
			depozit::text out(i, type::subtitle, line.substr(line.find_first_of(L"\"") + 1, line.find_last_of(L"\"") - 1));
			this->arrayTexts.push_back(out);
		}
	}

}