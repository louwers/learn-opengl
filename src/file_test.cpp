#include <gmock/gmock.h>

#include "file.h"

#include <algorithm>
#include <filesystem>

using namespace std;

TEST(GetFileContents, GetsFileContents) {
  auto simpleFile = filesystem::path("./test/simple.txt");
  EXPECT_TRUE(filesystem::exists(simpleFile));
  auto fileContents = getFileContents(simpleFile);
  EXPECT_EQ(fileContents, "hello world\n");
}

TEST(GetFileContents, ThrowsWhenNotRegularFile) {
  EXPECT_THROW(
      {
        try {
          static_cast<void>(getFileContents("./test"));
        } catch (const std::exception &e) {
          EXPECT_THAT(e.what(), ::testing::EndsWith("is not a regular file"));
          throw;
        }
      },
      std::runtime_error);
}
