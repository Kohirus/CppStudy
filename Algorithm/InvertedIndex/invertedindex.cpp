#include "invertedindex.hpp"
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

#undef UNICODE

void InvertList::addTerm(const string& docid, int loc) {
    for (auto& term : termList_) {
        if (term.docid_ == docid) {
            // docid已经创建
            term.freqs_++;
            term.locations_.emplace_back(loc);
            return;
        }
    }

    // 第一次创建docid文档的倒排索引
    termList_.emplace_back(docid, 1, loc);
}

void InvertIndex::query(const string& phrase) {
    // 先进行句子分词操作
    vector<string> wordList;
    char*          word = strtok(const_cast<char*>(phrase.c_str()), " ");
    while (word != nullptr) {
        word = trim(word);
        if (strlen(word) > 0) {
            wordList.emplace_back(word);
        }
        word = strtok(nullptr, " ");
    }

    if (wordList.empty())
        return;

    if (wordList.size() == 1) {
        auto it = invertMap_.find(wordList[0]);
        if (it == invertMap_.end()) {
            cout << "No match was found!" << endl;
            return;
        }

        for (auto& term : it->second.getInvertList()) {
            cout << "id: " << term.docid_ << "  freq: " << term.freqs_ << endl;
        }
    } else {
        // 搜索多个单词
        vector<InvertList> invertList;
        for (int i = 0; i < wordList.size(); ++i) {
            auto it = invertMap_.find(wordList[i]);
            if (it != invertMap_.end()) {
                invertList.emplace_back(it->second);
            }
        }

        // 开始遍历所有的倒排列表 求倒排项的交集
        vector<InvertTerm> v1(invertList[0].getInvertList().begin(),
            invertList[0].getInvertList().end());
        vector<InvertTerm> termShared;
        for (int i = 1; i < invertList.size(); i++) {
            vector<InvertTerm> v2(invertList[i].getInvertList().begin(),
                invertList[i].getInvertList().end());

            // 使用set_intersection时要保证数据有序
            sort(v1.begin(), v1.end());
            sort(v2.begin(), v2.end());
            set_intersection(v1.begin(), v1.end(),
                v2.begin(), v2.end(),
                back_inserter(termShared));

            v1.swap(termShared);
            termShared.clear();
        }

        for (auto& term : v1) {
            cout << "id: " << term.docid_ << "  freq: " << term.freqs_ << endl;
            /*
            cout << "locations: ";
            for (int pos : term.locations_) {
                cout << pos << " ";
            }
            cout << endl;
            */
        }
    }
}

void InvertIndex::setSearchPath(const string& path) {
    cout << "Searching local file ..." << endl;
    getAllFile(path.c_str());
    cout << "Finished!" << endl;
    cout << "========================================" << endl;
    cout << endl;

    cout << "Begin to create inverted index ..." << endl;
    createInvertedIndex();
    cout << "Finished!" << endl;
    cout << "========================================" << endl;
}

void InvertIndex::addSuffix(const string& suffix) {
    if (!isSuffixExist(suffix)) {
        suffixs_.emplace_back(suffix);
    }
}

void InvertIndex::removeSuffix(const string& suffix) {
    for (auto iter = suffixs_.begin(); iter != suffixs_.end(); ++iter) {
        if (*iter == suffix) {
            suffixs_.erase(iter);
            return;
        }
    }
}

void InvertIndex::clearSuffix() {
    suffixs_.clear();
}

bool InvertIndex::isSuffixExist(const string& suffix) {
    for (string& str : suffixs_) {
        if (suffix == str) {
            return true;
        }
    }
    return false;
}

void InvertIndex::createInvertedIndex() {
    int curidx = 1;
    for (string& filePath : fileList_) {
        cout << "Current progress: " << curidx++ << " / " << fileList_.size();
        FILE* pf = fopen(filePath.c_str(), "r");
        if (pf == nullptr) {
            cout << " [Failed to open " << filePath << "!]" << endl;
            continue;
        }

        // 按行读取文件中的内容 按照空格进行分词
        vector<string> wordList;
        int            loc             = 0;
        const int      LINE_SIZE       = 2048;
        char           line[LINE_SIZE] = { 0 };

        while (!feof(pf)) {
            // 读一行文件内容
            fgets(line, LINE_SIZE, pf);

            // 按照空格进行分词
            char* word = strtok(line, " ");
            while (word != nullptr) {
                // 过滤前后多余的空格和换行符
                word = trim(word);
                if (strlen(word) > 0) {
                    wordList.emplace_back(word);
                }
                word = strtok(nullptr, " ");
            }

            // 开始给单词创建倒排列表
            for (string& w : wordList) {
                loc++;
                auto it = invertMap_.find(w);
                if (it == invertMap_.end()) {
                    // 新建该单词的倒排列表
                    InvertList list;
                    list.addTerm(filePath, loc);
                    invertMap_.emplace(w, list);
                } else {
                    it->second.addTerm(filePath, loc);
                }
            }
        }

        fclose(pf);
        cout << endl;
    }
}

int InvertIndex::getAllFile(const char* path) {
    char            szFind[MAX_PATH];
    WIN32_FIND_DATA FindFileData;
    strcpy(szFind, path);
    strcat(szFind, "\\*.*");
    HANDLE hFind = FindFirstFile(szFind, &FindFileData);
    if (INVALID_HANDLE_VALUE == hFind)
        return -1;

    do {
        if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
                // 发现子目录，递归之
                char szFile[MAX_PATH] = { 0 };
                strcpy(szFile, path);
                strcat(szFile, "\\");
                strcat(szFile, FindFileData.cFileName);
                getAllFile(szFile);
            }
        } else {
            // 找到文件，处理之
            string fileName(FindFileData.cFileName);
            for (auto& suffix : suffixs_) {
                int pos = fileName.find(suffix); // abcd.cpp   pos:4 +4
                if (pos != string::npos && pos + suffix.size() == fileName.size()) {
                    std::cout << path << "\\" << FindFileData.cFileName << std::endl;
                    string filePath(path);
                    filePath.append("\\");
                    filePath.append(fileName);
                    fileList_.emplace_back(filePath);
                }
            }
        }
    } while (FindNextFile(hFind, &FindFileData));

    FindClose(hFind);

    return 0;
}

char* InvertIndex::trim(char* word) {
    // 去除前面多余的字符
    int i = 0;
    while (word[i] != '\0') {
        if (word[i] == ' ' || word[i] == '\t' || word[i] == '\n') {
            i++;
        } else {
            break;
        }
    }
    // 去除后面多余的字符
    int j = i;
    while (word[j] != '\0') {
        if (word[j] == ' ' || word[j] == '\t' || word[j] == '\n') {
            break;
        }
        j++;
    }

    word[j] = '\0';
    return word + i;
}