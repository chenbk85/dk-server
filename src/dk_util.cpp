
/**
 * author:lijian2@ucweb.com
 * date:2012-03-08
 */

#include "dk_util.h"
#include "dk_log.h"

using namespace std;

bool DKGetHostByName(const string &host, string &ip) {
  struct hostent hent, *ent;
  char buf[2048];
  int err;
  struct in_addr addr;

  /* Libevent evget_addrinfo has a bug */
  if (gethostbyname_r(host.c_str(), &hent, buf, sizeof(buf), &ent, &err) ||
    ent == NULL) {
    DK_DEBUG("[error] %s: gethostbyname_r %s\n", __func__, host.c_str()); 
    ip = host;
    return false;
  }
  
  for (int i = 0; ent->h_addr_list[i]; ++i) {
    memcpy(&addr, ent->h_addr_list[i], ent->h_length);
    ip = inet_ntoa(addr);
    break;
  }

  return true;
}

bool DKGetHostName(std::string &host) {
  char buf[NI_MAXHOST];
  if (gethostname(buf, sizeof(buf)) == 0) {
    host.assign(buf, strlen(buf));
    return true;
  }
  return false;
}

bool DKGetHostIp(std::string &ip) {
  string host;
  DKGetHostName(host);
  return DKGetHostByName(host, ip);
}
