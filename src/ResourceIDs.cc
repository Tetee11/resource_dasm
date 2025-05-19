#include "ResourceIDs.hh"

#include <limits.h>

#include <phosg/Strings.hh>

namespace ResourceDASM {

void ResourceIDs::print(FILE* file, bool new_line) const {
  auto print_id = [&, first = true](const char* prefix, int16_t res_id) mutable {
    const char* effective_prefix = prefix
        ? prefix
        : first ? ""
                : ", ";
    phosg::fwrite_fmt(file, "{}{}", effective_prefix, res_id);
    first = false;
  };

  for (int res_id = MIN_RES_ID, start = INT_MAX; res_id <= MAX_RES_ID; ++res_id) {
    if ((*this)[res_id]) {
      if (start != INT_MAX) {
        // End of range?
        if (res_id == MAX_RES_ID || !(*this)[res_id + 1]) {
          print_id("..", res_id);
        }
      } else {
        // Possibly start of range
        start = res_id;
        print_id(nullptr, res_id);
      }
    } else {
      start = INT_MAX;
    }
  }
  if (new_line) {
    fputc('\n', file);
  }
}

} // namespace ResourceDASM
