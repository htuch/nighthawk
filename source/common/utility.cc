
#include "absl/strings/match.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"

#include "common/http/utility.h"
#include "common/network/utility.h"

#include "common/utility.h"

namespace Nighthawk {

namespace PlatformUtils {

// returns 0 on failure. returns the number of HW CPU's
// that the current thread has affinity with.
// TODO(oschaaf): mull over what to do w/regard to hyperthreading.
uint32_t determineCpuCoresWithAffinity() {
  const pthread_t thread = pthread_self();
  cpu_set_t cpuset;
  int i;

  CPU_ZERO(&cpuset);
  i = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
  if (i == 0) {
    return CPU_COUNT(&cpuset);
  }
  return 0;
}

} // namespace PlatformUtils

std::map<std::string, uint64_t>
Utility::mapCountersFromStore(const Envoy::Stats::Store& store,
                              const StoreCounterFilter& filter) const {
  std::map<std::string, uint64_t> results;

  for (const auto& stat : store.counters()) {
    if (filter(stat->name(), stat->value())) {
      results[stat->name()] = stat->value();
    }
  }

  return results;
}

size_t Utility::findPortSeparator(absl::string_view hostname) {
  if (hostname.size() > 0 && hostname[0] == '[') {
    return hostname.find(":", hostname.find(']'));
  }
  return hostname.rfind(":");
}

Envoy::Network::DnsLookupFamily Utility::parseAddressFamilyOptionString(absl::string_view family) {
  const std::string lowercase_family = absl::AsciiStrToLower(family);
  if (lowercase_family == "v6") {
    return Envoy::Network::DnsLookupFamily::V6Only;
  } else if (lowercase_family == "v4") {
    return Envoy::Network::DnsLookupFamily::V4Only;
  } else if (lowercase_family == "auto") {
    return Envoy::Network::DnsLookupFamily::Auto;
  }
  throw NighthawkException("Invalid argument");
}

} // namespace Nighthawk