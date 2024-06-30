# Snapshot test runner (executable)
file(GLOB_RECURSE SNAPSHOT_TEST_SOURCES "*.cpp")
add_executable(EmSnapshotTestRunner ${SNAPSHOT_TEST_SOURCES})
target_link_libraries(EmSnapshotTestRunner PRIVATE Em)
