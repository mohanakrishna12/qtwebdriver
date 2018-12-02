// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/process_util.h"

namespace base {

#if defined(OS_POSIX)
ProcessEntry::ProcessEntry() : pid_(0), ppid_(0), gid_(0) {}
ProcessEntry::~ProcessEntry() {}
#endif

int GetProcessCount(const FilePath::StringType& executable_name,
                    const ProcessFilter* filter) {
  int count = 0;
  NamedProcessIterator iter(executable_name, filter);
  while (iter.NextProcessEntry())
    ++count;
  return count;
}

bool KillProcesses(const FilePath::StringType& executable_name, int exit_code,
                   const ProcessFilter* filter) {
  bool result = true;
  NamedProcessIterator iter(executable_name, filter);
  while (const ProcessEntry* entry = iter.NextProcessEntry()) {
#if defined(OS_WIN)
    result &= KillProcessById(entry->pid(), exit_code, true);
#else
    result &= KillProcess(entry->pid(), exit_code, true);
#endif
  }
  return result;
}

const ProcessEntry* ProcessIterator::NextProcessEntry() {
  bool result = false;
  do {
    result = CheckForNextProcess();
  } while (result && !IncludeEntry());
  if (result)
    return &entry_;
  return NULL;
}

ProcessIterator::ProcessEntries ProcessIterator::Snapshot() {
  ProcessEntries found;
  while (const ProcessEntry* process_entry = NextProcessEntry()) {
    found.push_back(*process_entry);
  }
  return found;
}

bool ProcessIterator::IncludeEntry() {
  return !filter_ || filter_->Includes(entry_);
}

ProcessIterator::ProcessIterator(const ProcessFilter* filter)
{

}

ProcessIterator::~ProcessIterator()
{}
bool ProcessIterator::CheckForNextProcess()
{
    return false;
}

NamedProcessIterator::NamedProcessIterator(
    const FilePath::StringType& executable_name,
    const ProcessFilter* filter) : ProcessIterator(filter),
                                   executable_name_(executable_name) {
#if defined(OS_ANDROID)
  // On Android, the process name contains only the last 15 characters, which
  // is in file /proc/<pid>/stat, the string between open parenthesis and close
  // parenthesis. Please See ProcessIterator::CheckForNextProcess for details.
  // Now if the length of input process name is greater than 15, only save the
  // last 15 characters.
  if (executable_name_.size() > 15) {
    executable_name_ = FilePath::StringType(executable_name_,
                                            executable_name_.size() - 15, 15);
  }
#endif
}

bool NamedProcessIterator::IncludeEntry() {
    return false;
}

NamedProcessIterator::~NamedProcessIterator() {
}

bool KillProcessById(ProcessId process_id, int exit_code, bool wait)
{
    return false;
}

}  // namespace base
