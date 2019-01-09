$NetBSD$

Fix building on SunOS in C99 mode.

--- hotspot/src/os/solaris/vm/os_solaris.cpp.orig	2017-08-01 09:03:05.000000000 +0000
+++ hotspot/src/os/solaris/vm/os_solaris.cpp
@@ -168,6 +168,8 @@ extern "C" {
 
   static int lwp_cond_init(cond_t *cv, int scope, void *arg){ memset(cv, 0, sizeof(cond_t)); return 0; }
   static int lwp_cond_destroy(cond_t *cv)                   { return 0; }
+  static int memcntl(caddr_t, size_t, int, caddr_t, int, int);
+  static int meminfo(const uint64_t *, int, const uint_t *, int, uint64_t *, uint_t *);
 }
 
 // "default" initializers for pthread-based synchronization
@@ -2413,7 +2415,7 @@ void os::pd_commit_memory_or_exit(char*
 
 // Uncommit the pages in a specified region.
 void os::pd_free_memory(char* addr, size_t bytes, size_t alignment_hint) {
-  if (madvise(addr, bytes, MADV_FREE) < 0) {
+  if (posix_madvise(addr, bytes, MADV_FREE) < 0) {
     debug_only(warning("MADV_FREE failed."));
     return;
   }
@@ -2442,7 +2444,7 @@ void os::pd_realign_memory(char *addr, s
 // Tell the OS to make the range local to the first-touching LWP
 void os::numa_make_local(char *addr, size_t bytes, int lgrp_hint) {
   assert((intptr_t)addr % os::vm_page_size() == 0, "Address should be page-aligned.");
-  if (madvise(addr, bytes, MADV_ACCESS_LWP) < 0) {
+  if (posix_madvise(addr, bytes, MADV_ACCESS_LWP) < 0) {
     debug_only(warning("MADV_ACCESS_LWP failed."));
   }
 }
@@ -2450,7 +2452,7 @@ void os::numa_make_local(char *addr, siz
 // Tell the OS that this range would be accessed from different LWPs.
 void os::numa_make_global(char *addr, size_t bytes) {
   assert((intptr_t)addr % os::vm_page_size() == 0, "Address should be page-aligned.");
-  if (madvise(addr, bytes, MADV_ACCESS_MANY) < 0) {
+  if (posix_madvise(addr, bytes, MADV_ACCESS_MANY) < 0) {
     debug_only(warning("MADV_ACCESS_MANY failed."));
   }
 }
