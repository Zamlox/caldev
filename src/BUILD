load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_import")

cc_binary(
    name = "rebosdk",
    deps = [
        "//external/glfw:glfw",
    ]
    visibility = ["//visibility:public"],
    linkopts = ["-ldl", "-lpthread", "-lGL"],
    linkshared = True,
)