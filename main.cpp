#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <filesystem>
#include <stdlib.h>     /* srand, rand */
#include <functional>

namespace fs = std::filesystem;
struct raw_domain
{
    std::map<std::string, bool> values;
    std::string key;
};
bool raw_domain_sorter(raw_domain const& domain, raw_domain const& domain1){
    return domain.values.size() < domain1.values.size();
}
using hashKeyFunc = std::function<std::string(u_int32_t)> ;

hashKeyFunc hashKeyFuncGen(int hashValueSize){

    return  [hashValueSize](u_int32_t) mutable
    {
        return "ss";
    };
}
using byte = unsigned char;

void littleEndian(byte b[], uint32_t v){
    b[0] = byte(v);
	b[1] = byte(v >> 8);
	b[2] = byte(v >> 16);
	b[3] = byte(v >> 24);
}



int  bs(std::vector<std::string> const& v, std::string q){

	// Define f(-1) == false and f(n) == true.
	// Invariant: f(i-1) == false, f(j) == true.
	int i = 0, j = v.size();
    int h;
	while(i < j){
		h = int(i+j >> 1); // avoid overflow when computing h
		// i ≤ h < j
        
		if(!(v[h] >= q)) {
			i = h + 1;// preserves f(i-1) == false
		} else {
			j = h;// preserves f(j) == true
		}
	}
	// i == j, f(i-1) == false, and f(j) (= f(i)) == true  =>  answer is i.
	return i;
}


int main(int argc, char* argv[]) {
    // clock_t begin = clock();
    // std::vector<raw_domain> raw_domains;
    // std::map<std::string, bool> m;
    // m["test"] = true;
    // m["tst"] = true;
    // raw_domains.push_back({m, "domain1"});
    // std::map<std::string, bool> m1;
    // m1["test"] = true;
    // raw_domains.push_back({m1, "domain2"});
    // std::sort(raw_domains.begin(), raw_domains.end(), &raw_domain_sorter);
    // std::cout << raw_domains[0].key ;

    // clock_t end = clock();
    // double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    // std::cout << elapsed_secs;
    // for (const auto & entry : fs::directory_iterator(fs::u8path("."))){
    //     std::string path = entry.path().u8string();
    //     std::cout << path.substr(2) << std::endl;
    // }

    // int subsets[] {15000, 26000, 34000, 44000, 50000, 59000, 59900, 60800, 61500, 63000, 63500, 63900,
	// 	64400, 64700, 64900, 65100, 65300, 65400, 65520, 65537};
    // std::vector<int> b;
    // b.push_back(1);
    // b.push_back(3);
    // b.push_back(5);
    // b.push_back(1);
    // b.push_back(3);
    // b.push_back(5);
    // // for(int i = 0; i < std::size(subsets); i++){
    // //     std::cout << subsets[i] << "\n";
    // // }
    // std::vector<int> v{&b[0], &b[4]};
    // // for(auto a : m){
    // //     std::cout << a << "\n";
    // // }
    // srand (40);
    // int x  = rand() % 10 + 1;
    // int y  = rand() % 10 + 1;
    // for(int i =0; i < 8; i++){
    //     std::cout << rand() % 10 << "\n";
    // }
    // byte s[4];
    // uint32_t x = 12334455;
    // littleEndian(s, x);
    // std::cout << s[0] << "\n";
    // std::cout << s[1] << "\n";
    // std::cout << s[2] << "\n";
    // std::cout << s[3] << "\n";
    // std::string str(s, s + 4);
    // std::map<std::string, std::vector<std::string>> m;
    // m["hello"] = std::vector<std::string>;
    // m["hello"].push_back("test");
    // std::cout << m["hello"][0] <<"\n";
    std::vector<std::map<std::string, std::vector<std::string>>> m; 

    m.resize(5);
    m[0]["helo"].push_back("kkk");
    std::cout << "------------------->" << m.size();
}