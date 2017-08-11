#include "gtest/gtest.h"

#include <fstream>

#include "core/parser/meCSVParser.h"
#include "core/meError.h"
#include "PIL/meIO.h"

/* Helper Function ...*/
int getFileSize(const std::string &fileName)
{
	std::ifstream file(fileName.c_str(), std::ifstream::in | std::ifstream::binary);
	if (!file.is_open())
	{
		return -1;
	}
	file.seekg(0, std::ios::end);
	int fileSize = (int)file.tellg();
	file.close();
	return fileSize;
}

using namespace meEngine;
using namespace meEngine::meParser;

TEST(meCSVParser, openclose)
{
	meIO::meFile* testfile;
	meCSVParser test;
	EXPECT_EQ(test._open(&testfile, L"core\\parser\\test.csv", L"r"), 0);
	EXPECT_EQ(test._close(&testfile), 0);
	EXPECT_EQ(test._close(&testfile), meFileClosedError);
}

TEST(meCSVParser, read)
{
	meCSVParser test;

	// Only test if everything gets parsed.
	EXPECT_EQ(test.read(L"core\\parser\\test.csv"), 0);
}

TEST(meCSVParser, write)
{
	meCSVParser test(L"core\\parser\\test.csv");
	EXPECT_EQ(test.write(L"core\\parser\\test2.csv"), 0);

	EXPECT_EQ(getFileSize("core\\parser\\test.csv"), getFileSize("core\\parser\\test2.csv"));

	std::remove("core\\parser\\test2.csv");
}

TEST(meCSVParser, columns)
{
	meCSVParser test(L"core\\parser\\test.csv");

	meUInt64 ncols;
	EXPECT_EQ(test.columns(ncols), 0);
	EXPECT_EQ(ncols, 3);

	meCSVParser test2;
	EXPECT_EQ(test2.columns(ncols), 0);
	EXPECT_EQ(ncols, 0);
}

TEST(meCSVParser, rows)
{
	meCSVParser test(L"core\\parser\\test.csv");

	meUInt64 nrows;
	EXPECT_EQ(test.rows(nrows), 0);
	EXPECT_EQ(nrows, 3);

	meCSVParser test2;
	EXPECT_EQ(test2.rows(nrows), 0);
	EXPECT_EQ(nrows, 0);

}

TEST(meCSVParser, addHeader)
{
	meCSVParser test;

	meUInt64 ncols;

	EXPECT_EQ(test.addHeader(L"test1"), 0);
	EXPECT_EQ(test.columns(ncols), 0);
	EXPECT_EQ(ncols, 1);

	EXPECT_EQ(test.addHeader(L"test2"), 0);
	EXPECT_EQ(test.columns(ncols), 0);
	EXPECT_EQ(ncols, 2);
}

TEST(meCSVParser, addRow)
{
	meCSVParser test;
	ASSERT_EQ(test.addHeader(L"test1"), 0);
	ASSERT_EQ(test.addHeader(L"test2"), 0);
	ASSERT_EQ(test.addHeader(L"test3"), 0);

	meUInt64 nrows;

	EXPECT_EQ(test.addRow(meVector<meString>({ L"a", L"b", L"c" })), 0);
	EXPECT_EQ(test.rows(nrows), 0);
	EXPECT_EQ(nrows, 1);

	EXPECT_EQ(test.addRow(meVector<meString>({ L"d", L"e", L"f" })), 0);
	EXPECT_EQ(test.rows(nrows), 0);
	EXPECT_EQ(nrows, 2);

	EXPECT_EQ(test.addRow(meVector<meString>({ L"d", L"e" })), 0);
	EXPECT_EQ(test.rows(nrows), 0);
	EXPECT_EQ(nrows, 3);

	EXPECT_EQ(test.addRow(meVector<meString>({ L"d", L"e", L"g", L"h" })), meToManyRowsError);
	EXPECT_EQ(test.rows(nrows), 0);
	EXPECT_EQ(nrows, 3);
}

TEST(meCSVParser, getHeader)
{
	meCSVParser test;
	ASSERT_EQ(test.addHeader(L"test1"), 0);
	ASSERT_EQ(test.addHeader(L"test2"), 0);
	ASSERT_EQ(test.addHeader(L"test3"), 0);

	meString h;

	EXPECT_EQ(test.getHeader(0, h), 0);
	EXPECT_EQ(h, L"test1");

	EXPECT_EQ(test.getHeader(1, h), 0);
	EXPECT_EQ(h, L"test2");

	EXPECT_EQ(test.getHeader(2, h), 0);
	EXPECT_EQ(h, L"test3");
}

TEST(meCSVParser, getHeaders)
{
	meCSVParser test;
	ASSERT_EQ(test.addHeader(L"test1"), 0);
	ASSERT_EQ(test.addHeader(L"test2"), 0);
	ASSERT_EQ(test.addHeader(L"test3"), 0);

	meVector<meString> hs;

	EXPECT_EQ(test.getHeaders(hs), 0);
	ASSERT_EQ(hs.size(), 3);
	EXPECT_EQ(hs[0], L"test1");
	EXPECT_EQ(hs[1], L"test2");
	EXPECT_EQ(hs[2], L"test3");
}

TEST(meCSVParser, getRow)
{
	meCSVParser test;
	ASSERT_EQ(test.addHeader(L"test1"), 0);
	ASSERT_EQ(test.addHeader(L"test2"), 0);
	ASSERT_EQ(test.addHeader(L"test3"), 0);
	ASSERT_EQ(test.addRow(meVector<meString>({ L"a", L"b", L"c" })), 0);
	ASSERT_EQ(test.addRow(meVector<meString>({ L"d", L"e", L"f" })), 0);
	ASSERT_EQ(test.addRow(meVector<meString>({ L"d", L"e" })), 0);

	meVector<meString> data;

	ASSERT_EQ(test.getRow(0, data), 0);
	ASSERT_EQ(data.size(), 3);
	EXPECT_EQ(data[0], L"a");
	EXPECT_EQ(data[1], L"b");
	EXPECT_EQ(data[2], L"c");

	ASSERT_EQ(test.getRow(1, data), 0);
	ASSERT_EQ(data.size(), 3);
	EXPECT_EQ(data[0], L"d");
	EXPECT_EQ(data[1], L"e");
	EXPECT_EQ(data[2], L"f");

	ASSERT_EQ(test.getRow(2, data), 0);
	ASSERT_EQ(data.size(), 3);
	EXPECT_EQ(data[0], L"d");
	EXPECT_EQ(data[1], L"e");
	EXPECT_EQ(data[2], L"");
}
