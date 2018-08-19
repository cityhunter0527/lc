#include "ConsistHash.hpp"
#include <map>
using namespace std;

int main() {
    ConsistHash h;
    h.init();
    vector<string> nodes = {
        "10.1.1.11",
        "10.1.1.12",
        "10.1.1.13",
        "10.1.1.14",
        "10.1.1.15",
        "10.1.1.16"};
    vector<string> vobjects;
    vector<string> objects = {
        "www.baidu.com",
        "www.google.com",
        "www.sina.com.cn",
        "www.youtube.com",
        "www.dell.com",
        "www.emc.com",
        "www.codeproject.com",
        "www.codeguru.com",
        "www.apple.com",
        "www.cisco.com",
        "www.newsmth.net",
        "www.cnn.net",
        "www.yahoo.com",
        "www.taobao.com",
        "www.tmall.com",
        "www.tianya.com",
        "www.medium.com",
        "www.leetcode.com",
        "www.chiphell.com",
        "www.solidot.com",
        "map.baidu.com",
        "www.amap.com",
        "www.autohome.com",
        "www.quora.com",
        "www.zhihu.com",
        "www.hupu.com",
        "www.facebook.com",
        "www.twitter.com",
        "www.snapchat.com",
        "www.snapchat001.com",
        "www.snapchat002.com",
        "www.snapchat003.com",
        "www.snapchat004.com",
        "www.snapchat005.com",
        "www.snapchat006.com",
        "www.snapchat007.com",
        "www.snapchat008.com",
        "www.snapchat009.com",
        "www.snapchat010.com"};
    
    for (auto x:nodes) {
        h.addNode(x, 8);
    }

    map<string, int> m;
    for (int i = 0; i < 100; i++) {
        string x = "www.facebook00" + to_string(i) + ".com";
        ConsistHash::Node* pNode = h.lookup(x);
        //cout << pNode->iden << " : " << x << endl;
        m[pNode->iden]++;
    }

    for (auto x:m)
        cout << x.first << ": " << x.second << endl;

    return 0;
}
