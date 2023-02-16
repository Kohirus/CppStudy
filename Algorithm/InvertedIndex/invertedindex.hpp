#ifndef __INVERT_INDEX_HPP__
#define __INVERT_INDEX_HPP__

#include <string>
#include <list>
#include <vector>
#include <unordered_map>
using namespace std;

// 倒排项
struct InvertTerm {
    InvertTerm(const string& docid, int freqs, int loc)
        : docid_(docid)
        , freqs_(freqs) {
        locations_.emplace_back(loc);
    }

    bool operator==(const InvertTerm& term) const {
        return docid_ == term.docid_;
    }

    bool operator<(const InvertTerm& term) const {
        return docid_ < term.docid_;
    }

    string    docid_;     // 单词所在的文档
    int       freqs_;     // 单词出现的次数
    list<int> locations_; // 单词出现的位置
};

// 倒排列表
class InvertList {
public:
    InvertList()  = default;
    ~InvertList() = default;

public:
    // 添加倒排项
    void addTerm(const string& docid, int loc);

    // 获取倒排列表内容
    const list<InvertTerm>& getInvertList() const {
        return termList_;
    }

private:
    list<InvertTerm> termList_; // 存储当前倒排列表所有的倒排项
};

// 倒排索引
class InvertIndex {
public:
    // 查询接口
    void query(const string& phrase);
    // 设置本地搜索路径
    void setSearchPath(const string& path);
    // 添加文件后缀
    void addSuffix(const string& suffix);
    // 删除文件后缀
    void removeSuffix(const string& suffix);
    // 清空文件后缀
    void clearSuffix();
    // 后缀是否已经存在
    bool isSuffixExist(const string& suffix);

private:
    // 创建倒排索引结构
    void createInvertedIndex();
    // 递归扫描路径下的所有文件
    int getAllFile(const char* path);
    // 去掉单词前后多余的字符
    char* trim(char* word);

private:
    vector<string>                    suffixs_;   // 过滤文档后缀
    list<string>                      fileList_;  // 存储所有需要建立倒排索引的文件
    unordered_map<string, InvertList> invertMap_; // 词典+倒排列表
};

#endif // !__INVERT_INDEX_HPP__