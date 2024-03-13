#include "../../Headers/Core/Account.hpp"

const string Account::GetId() const { return id; }
const string Account::GetPassword() const { return password; }

void Account::SetId(const string id) { this->id = id; }
void Account::SetPassword(const string password) { this->password = password; }