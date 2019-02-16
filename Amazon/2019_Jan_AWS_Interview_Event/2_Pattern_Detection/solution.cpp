/*
 * Pattern Detection:
 *
 * Input:
 * - String Patter: "a*b*c.", 
 *   * : 0 or any times of occurrence of previous character
 *   . : 1 of any character
 *
 * - Reference String S: "abcc"
 * 
 * Output:
 * - True if S matches with patter P;
 * - False if not;
 *
 * Example:
 * P: "a*b*c."
 * S: "abbcc"
 * return true;
 *
 * P: "a*b*c."
 * S: "abbc"
 *
 * return false, because there must be 1 character after 'c'
 *
 * P: "a*b*c."
 * S: "bbcc"
 * return true, there could be 0 occruence of a;
 * */

class solution {
public:
    bool patter_detect(std::string p, std::string s) {
    
    }
};

int mai() {
    return 1;
}
