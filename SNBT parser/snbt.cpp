#include "SNBT.h"

namespace depozit 
{
	//public
	snbt::snbt() {
		this->fullFile=L"";
	};
	snbt::snbt(fs::path pathToSnbtFile) {
		this->fileByLine = readFileByVecWstring(pathToSnbtFile);
		parsing();
	}
	void snbt::init(fs::path pathToSnbtFile) {
		this->fileByLine = readFileByVecWstring(pathToSnbtFile);
		parsing();
	}

	std::wstring snbt::getFileByWstring() {
		return this->fullFile;
	}
	std::wstring snbt::getTextsByWstring() {
		std::wstring out = L"";
		for (int i = 0; i < this->arrayTexts.size(); i++) {
			if (this->arrayTexts[i].getType() != depozit::type::unknown) {
				out += std::to_wstring(this->arrayTexts[i].getPosInFile()) + L":";
				out += this->arrayTexts[i].getTypeByWstring() + L":";
				out += this->arrayTexts[i].getOriginalText() + L":";
				out += this->arrayTexts[i].getTranslatedString() + L"\n";
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
		if(file.is_open()){
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
	}
	void snbt::parsing() {
		if(this->fullFile.find(L"quests") != std::wstring::npos){
			int startLine = 0;
			for (int i = 0; i < fileByLine.size(); i++) {
				if (fileByLine[i].find(L"quests") != std::wstring::npos) {
					startLine = i;
					break;
				}
			}
			for (int i = startLine; i < this->fileByLine.size(); i++) {
				if (fileByLine[i].find(L"subtitle") != std::wstring::npos) {
					getSubtitle(i, fileByLine[i]);
				}
				else if (fileByLine[i].find(L"title") != std::wstring::npos) {
					getTitle(i, fileByLine[i]);
				}
				else if (fileByLine[i].find(L"description") != std::wstring::npos) {
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
	}
	void snbt::getTitle(unsigned i, std::wstring line) {
		if (line.find(L"{") == std::wstring::npos) {
			depozit::text out(i, type::title, line.substr(line.find_first_of(L"\"") + 1,
				line.find_last_of(L"\"") - line.find_first_of(L"\"") - 1));
			if(out.getOriginalText().length() > 0)
				this->arrayTexts.push_back(out);
		}
	}
	void snbt::getSubtitle(unsigned i, std::wstring line) {
		if (line.find(L"{") == std::wstring::npos) {
			depozit::text out(i, type::subtitle, line.substr(line.find_first_of(L"\"") + 1, 
			line.find_last_of(L"\"") - line.find_first_of(L"\"") - 1));
			if(out.getOriginalText().length() > 0)
				this->arrayTexts.push_back(out);
		}
	}
	void snbt::getDescription(unsigned i, unsigned j, const std::vector<std::wstring>& fileByLine){
		size_t start;
		size_t end;
		depozit::text out;
		if (i == j) {
			start = fileByLine[i].find_first_of(L"\"");
			end = fileByLine[i].find_last_of(L"\"");
			out.init(i, type::description, fileByLine[i].substr(start + 1, end - start - 1));
			if (out.getOriginalText().length() > 0 && out.getOriginalText().find(L"{") == std::wstring::npos)
				this->arrayTexts.push_back(out);
			out.clear();
		}
		else {
			for (i; i <= j; i++) {
				if (fileByLine[i].find(L"\"") != std::wstring::npos) {
					start = fileByLine[i].find_first_of(L"\"");
					end = fileByLine[i].find_last_of(L"\"");
					out.init(i, type::description, fileByLine[i].substr(start + 1, end - start - 1));
					if (out.getOriginalText().length() > 0 && out.getOriginalText().find(L"{") == std::wstring::npos)
						this->arrayTexts.push_back(out);
					out.clear();
				}
			}
		}
	}
}