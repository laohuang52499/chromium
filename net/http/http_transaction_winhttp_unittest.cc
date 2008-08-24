// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/http/http_transaction_winhttp.h"
#include "net/http/http_transaction_unittest.h"
#include "testing/gtest/include/gtest/gtest.h"

TEST(HttpTransactionWinHttp, CreateAndDestroy) {
  net::HttpTransactionWinHttp::Factory factory;

  net::HttpTransaction* trans = factory.CreateTransaction();
  trans->Destroy();
}

TEST(HttpTransactionWinHttp, Suspend) {
  net::HttpTransactionWinHttp::Factory factory;

  net::HttpTransaction* trans = factory.CreateTransaction();
  trans->Destroy();

  factory.Suspend(true);

  trans = factory.CreateTransaction();
  ASSERT_TRUE(trans == NULL);

  factory.Suspend(false);

  trans = factory.CreateTransaction();
  trans->Destroy();
}

TEST(HttpTransactionWinHttp, GoogleGET) {
  net::HttpTransactionWinHttp::Factory factory;
  TestCompletionCallback callback;

  net::HttpTransaction* trans = factory.CreateTransaction();

  net::HttpRequestInfo request_info;
  request_info.url = GURL("http://www.google.com/");
  request_info.method = "GET";
  request_info.user_agent = "Foo/1.0";
  request_info.load_flags = net::LOAD_NORMAL;

  int rv = trans->Start(&request_info, &callback);
  if (rv == net::ERR_IO_PENDING)
    rv = callback.WaitForResult();
  EXPECT_EQ(net::OK, rv);

  std::string contents;
  rv = ReadTransaction(trans, &contents);
  EXPECT_EQ(net::OK, rv);

  trans->Destroy();
}

