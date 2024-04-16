const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // const c_options = .{ "-Wall", "-Wextra", "-Werror", "-pedantic", "-Isrc" };
    const c_options = .{"-Isrc"};

    const exe = b.addExecutable(.{
        .name = "social-network",
        .target = target,
        .optimize = optimize,
    });
    exe.addCSourceFiles(&.{ "src/social_network.cpp", "src/user.cpp", "src/network.cpp" }, &c_options);
    exe.linkLibCpp();

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);

    run_cmd.step.dependOn(b.getInstallStep());

    // This allows the user to pass arguments to the application in the build
    // command itself, like this: `zig build run -- arg1 arg2 etc`
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const runs = b.step("run", "Run the app");
    runs.dependOn(&run_cmd.step);

    const tests = b.step("test", "Run unit tests");

    const TestDerivation = struct {
        src: []const u8,
        name: []const u8,
    };

    // const cli_test = b.addSystemCommand(&.{ "python", "tests.py" });
    // tests.dependOn(&cli_test.step);

    const test_derivation = [_]TestDerivation{
        // .{ .src = "tests/test_user_1.cpp", .name = "test-user-1" },
        // .{ .src = "tests/test_user_2.cpp", .name = "test-user-2" },
        // .{ .src = "tests/1/test_user_3.cpp", .name = "test-user-3" },
        // .{ .src = "tests/1/test_user_4.cpp", .name = "test-user-4" },

        // just build "./src/tests/test_user_add_friend.cpp ./src/user.cpp" "test-user-add"
        // .{ .src = "tests/1/test_user_add_duplicate_friend.cpp", .name = "test-user-add-duplicate" },
        // just build "./src/tests/test_user_delete_friend.cpp ./src/user.cpp" "test-user-delete"
        // just build "./src/tests/test_user_get_friend_reference.cpp ./src/user.cpp" "test-user-get"

        // .{ .src = "tests/1/test_network_.cpp", .name = "test-network-simple" },
        // .{ .src = "tests/1/test_network_add_user.cpp", .name = "test-network-add-user" },
        // .{ .src = "tests/1/test_network_add_connection.cpp", .name = "test-network-add-con" },
        // .{ .src = "tests/1/test_network_add_duplicate_connection.cpp", .name = "test-network-add-dup" },
        // .{ .src = "tests/1/test_network_add_invalid_connection.cpp", .name = "test-network-add-invalid" },
        // .{ .src = "tests/1/test_network_delete_connection.cpp", .name = "test-network-delete-con" },
        // .{ .src = "tests/1/test_network_delete_invalid_connection.cpp", .name = "test-network-delete-bad" },

        // .{ .src = "./tests/1/test_network_get_id.cpp", .name = "test-network-get-id" },
        // .{ .src = "./tests/1/test_network_get_user.cpp", .name = "test-network-get-user" },
        // .{ .src = "tests/1/test_network_get_user_nullptr.cpp", .name = "test-network-get-user-null" },
        // .{ .src = "tests/1/test_network_read_user.cpp", .name = "test-network-read-user1" },
        // .{ .src = "tests/1/test_network_read_user2.cpp", .name = "test-network-read-user2" },

        .{ .src = "./tests/2/test_distance_user_1.cpp", .name = "test-distance-1" },
        // .{ .src = "./tests/2/test_distance_user_2.cpp", .name = "test-distance-2" },
        // .{ .src = "./tests/2/test_distance_user_3.cpp", .name = "test-distance-3" },
        // .{ .src = "./tests/2/test_groups_1.cpp", .name = "test-groups-1" },
        // .{ .src = "./tests/2/test_groups_2.cpp", .name = "test-groups-2" },
        // .{ .src = "./tests/2/test_shortest_path_1.cpp", .name = "test-short-path-1" },
        // .{ .src = "./tests/2/test_shortest_path_2.cpp", .name = "test-short-path-2" },
        // .{ .src = "./tests/2/test_shortest_path_3.cpp", .name = "test-short-path-3" },
        // .{ .src = "./tests/2/test_shortest_path_none.cpp", .name = "test-short-path-0" },
        // .{ .src = "./tests/2/test_suggest_friends_1.cpp", .name = "test-suggest-friend-1" },
        // .{ .src = "./tests/2/test_suggest_friends_2.cpp", .name = "test-suggest-friend-2" },
        // .{ .src = "./tests/2/test_suggest_friends_3.cpp", .name = "test-suggest-friend-3" },
        // .{ .src = "./tests/2/test_suggest_friends_none.cpp", .name = "test-suggest-friend-none" },
    };

    for (test_derivation) |t| {
        const tester = b.addExecutable(.{
            .name = t.name,
            .target = target,
            .optimize = optimize,
        });
        tester.addCSourceFile(.{ .file = .{ .path = t.src }, .flags = &c_options });
        tester.addCSourceFiles(&.{ "src/user.cpp", "src/network.cpp" }, &c_options);
        tester.linkLibCpp();

        const unit_test = b.addRunArtifact(tester);
        tests.dependOn(&unit_test.step);
    }
}
