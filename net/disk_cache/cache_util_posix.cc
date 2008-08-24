// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/disk_cache/cache_util.h"

#include "base/file_util.h"
#include "base/logging.h"
#include "base/notimplemented.h"

namespace disk_cache {

int64 GetFreeDiskSpace(const std::wstring& path) {
  DLOG(WARNING) << "Not Implemented";
  return -1;
}

int64 GetSystemMemory() {
  // TODO(pinkerton): figure this out for mac/linux
  return -1;
}

bool MoveCache(const std::wstring& from_path, const std::wstring& to_path) {
  // Just use the version from base.
  return file_util::Move(from_path.c_str(), to_path.c_str());
}

void DeleteCache(const std::wstring& path, bool remove_folder) {
  if (remove_folder) {
    file_util::Delete(path, false);
  } else {
    std::wstring name(path);
    file_util::AppendToPath(&name, L"*");
    file_util::Delete(name, false);
  }
}

bool DeleteCacheFile(const std::wstring& name) {
  return file_util::Delete(name, false);
}

void WaitForPendingIO(int* num_pending_io) {
  if (*num_pending_io) {
    NOTIMPLEMENTED();
  }
}

}  // namespace disk_cache

