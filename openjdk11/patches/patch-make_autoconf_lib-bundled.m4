$NetBSD$

Ensure the correct zlib can be found.

--- make/autoconf/lib-bundled.m4.orig	2020-09-22 15:30:20.000000000 +0000
+++ make/autoconf/lib-bundled.m4
@@ -214,7 +214,7 @@ AC_DEFUN_ONCE([LIB_SETUP_ZLIB],
   if test "x$USE_EXTERNAL_LIBZ" = "xfalse"; then
     LIBZ_CFLAGS="$LIBZ_CFLAGS -I$TOPDIR/src/java.base/share/native/libzip/zlib"
   else
-    LIBZ_LIBS="-lz"
+    LIBZ_LIBS="@COMPILER_RPATH_FLAG@@BUILDLINK_PREFIX.zlib@/lib -L@BUILDLINK_PREFIX.zlib@/lib -lz"
   fi
 
   AC_SUBST(USE_EXTERNAL_LIBZ)
