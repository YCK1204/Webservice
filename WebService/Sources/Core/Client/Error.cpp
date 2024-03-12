#include "../../../Headers/Core/Client.hpp"
#include "../../../Headers/Managers/Manager.hpp"
#include "../../../Headers/Utils/Util.hpp"

void Client::UpdateError() { Manager::Client.OnDisConnect(data.fd); }