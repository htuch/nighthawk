load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
)

licenses(["notice"])  # Apache 2

envoy_cc_library(
    name = "nighthawk_common_lib",
    srcs = [
        "rate_limiter_impl.cc",
        "sequencer_impl.cc",
        "statistic_impl.cc",
        "uri_impl.cc",
        "utility.cc",
        "worker_impl.cc",
    ],
    hdrs = [
        "frequency.h",
        "platform_util_impl.h",
        "rate_limiter_impl.h",
        "sequencer_impl.h",
        "ssl.h",
        "statistic_impl.h",
        "uri_impl.h",
        "utility.h",
        "worker_impl.h",
    ],
    repository = "@envoy",
    visibility = ["//visibility:public"],
    deps = [
        "//api/client:benchmark_options_cc",
        "//include/nighthawk/client:client_includes",
        "//include/nighthawk/common:base_includes",
        "@dep_hdrhistogram_c//:hdrhistogram_c",
        "@envoy//source/common/common:compiler_requirements_lib",
        "@envoy//source/common/common:minimal_logger_lib",
        "@envoy//source/common/common:thread_impl_lib_posix",
        "@envoy//source/common/stats:stats_lib",
        "@envoy//source/exe:envoy_common_lib",
        "@envoy//source/server/config_validation:server_lib",
    ],
)
