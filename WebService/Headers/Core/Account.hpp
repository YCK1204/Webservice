#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>

using namespace std;

class Account {
private:
  string id;
  string password;

public:
  const string GetId() const;
  const string GetPassword() const;

  void SetId(const string id);
  void SetPassword(const string password);
};

#endif