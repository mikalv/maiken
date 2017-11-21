

#include "kul/cli.hpp"
#include "kul/log.hpp"
#include "kul/map.hpp"
#include "kul/string.hpp"

int main(int argc, char *argv[]){

  uint8_t ret = 0;

  try {
    if(argc > 2) KEXIT(1, "argument required");

    std::unordered_map<std::string, std::string> cli;

    for (const auto& p : kul::String::ESC_SPLIT(argv[1], ',')) {
      if(p.find("=") == std::string::npos)
        KEXIT(1, "invalid, = missing");
      std::vector<std::string> ps = kul::String::ESC_SPLIT(p, '=');
      if (ps.size() > 2)
        KEXIT(1, "invalid, escape extra \"=\"");
      cli.insert(std::make_pair(ps[0], ps[1]));
    }

    for(const auto& p : cli)
      KLOG(INF) << p.first << " : " << p.second;

  } catch (const kul::Exit& e) {
    if (e.code() != 0) KERR << kul::os::EOL() << "ERROR: " << e;
    ret = e.code();
  } catch (const kul::Exception& e) {
    KERR << e.stack();
    ret = 2;
  } catch (const std::exception& e) {
    KERR << e.what();
    ret = 3;
  }


  return ret;
}