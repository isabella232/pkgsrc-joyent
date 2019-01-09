$NetBSD$

Support SunOS/gcc.

--- hotspot/src/os_cpu/solaris_x86/vm/os_solaris_x86.cpp.orig	2017-08-01 09:03:05.000000000 +0000
+++ hotspot/src/os_cpu/solaris_x86/vm/os_solaris_x86.cpp
@@ -295,13 +295,27 @@ frame os::get_sender_for_C_frame(frame*
   return frame(fr->sender_sp(), fr->link(), fr->sender_pc());
 }
 
+#ifdef SPARC_WORKS
 extern "C" intptr_t *_get_current_sp();  // in .il file
+#else
+extern "C" intptr_t *_get_current_sp() {
+  register intptr_t *rsp __asm__ ("rsp");
+  return rsp;
+}
+#endif
 
 address os::current_stack_pointer() {
   return (address)_get_current_sp();
 }
 
+#ifdef SPARC_WORKS
 extern "C" intptr_t *_get_current_fp();  // in .il file
+#else
+extern "C" intptr_t *_get_current_fp() {
+  register intptr_t **rbp __asm__ ("rbp");
+  return (intptr_t*) *rbp;
+}
+#endif
 
 frame os::current_frame() {
   intptr_t* fp = _get_current_fp();  // it's inlined so want current fp
