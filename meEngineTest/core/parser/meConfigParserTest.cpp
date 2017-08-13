#include "gtest/gtest.h"

#include "../../util.h"

#include "core/parser/meConfigParser.h"
#include "core/meError.h"

using namespace meEngine;
using namespace meEngine::meParser;


TEST(meConfigParser, read)
{
	meConfigParser test;
	meConfig conf;

	// Only test if everything gets parsed.
	EXPECT_EQ(test.read(L"core\\parser\\test.config", conf), 0);
}

TEST(meConfigParser, write)
{
	meConfigParser test;
	meConfig conf;
	
	ASSERT_EQ(test.read(L"core\\parser\\test.config", conf), 0);

	EXPECT_EQ(test.write(L"core\\parser\\test2.config", conf), 0);

	EXPECT_EQ(getFileSize("core\\parser\\test.config"), getFileSize("core\\parser\\test2.config"));

	std::remove("core\\parser\\test2.config");
}

TEST(meConfigParser, writeempty)
{
	meConfigParser test;
	meConfig conf;
	EXPECT_EQ(test.write(L"core\\parser\\test2.config", conf), 0);

	EXPECT_EQ(getFileSize("core\\parser\\test2.config"), 0) << "TODO";

	std::remove("core\\parser\\test2.config");
}
