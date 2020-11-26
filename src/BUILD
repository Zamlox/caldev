load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "rebosdk",
    deps = [
        "//extern/glfw:glfw",
        "//extern/imgui:imgui",
    ],
    visibility = ["//visibility:public"],
    linkopts = select({
        "@bazel_tools//src/conditions:windows": [
            "user32.lib", "gdi32.lib", "shell32.lib"
        ],
        "//conditions:default": [
            "-ldl", "-lpthread", "-lGL"
        ]
    }),
    linkshared = True,
)