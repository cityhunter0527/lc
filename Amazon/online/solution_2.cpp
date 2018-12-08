/*
 * Get recommendated course list for an Amazon user.
Each amazon user has several direct friends, and so on. 
Social network means 2 level friends. 3rd level friends won't be considered.
For example: Jon's social network will be: Ann, Lee, Mary, Tom and Jerry.  Joey is not Jon's social network.

Jon ------ Ann ---------Tom --------- Joey
  |         |
  |         |  
 Lee ----- Mary  ------ Jerry

Every user will learn serval couses and you will be given below two helper functions to return 
direct user list and course list.

For any given user, pls recommend him/her the course list that his/her social network is also 
taken and sort with popularity (e.g. the couse that most friends have taken should be recommended firstly).
The course that this user has already taken should not be recommended.
 * */


vector<string> getDirectFriends(string user);
vector<string> getCourseList(string user)

vector<string> getRemendedCourseList (string user) {
}
