#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=gcompat
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://git.adelielinux.org/adelie/gcompat.git
PKG_SOURCE_DATE:=2026-04-21
PKG_SOURCE_VERSION:=06600632096b14e03e32b234ec0b02a9d4d045e9
PKG_MIRROR_HASH:=37493c27e45a961732208de67c3a907d161ed2e5f13eaf131aa1f833479119ad

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=NCSA
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

GCOMPAT_MUSL_LDSO:=$(notdir $(firstword $(wildcard $(TOOLCHAIN_DIR)/lib/ld-musl-*.so.1)))

GCOMPAT_LDSO_aarch64:=ld-linux-aarch64.so.1
GCOMPAT_LDSO_arm:=$(if $(CONFIG_SOFT_FLOAT),ld-linux.so.3,ld-linux-armhf.so.3)
GCOMPAT_LDSO_i386:=ld-linux.so.2
GCOMPAT_LDSO_loongarch64:=ld-linux-loongarch-lp64d.so.1
GCOMPAT_LDSO_riscv64:=ld-linux-riscv64-lp64d.so.1
GCOMPAT_LDSO_x86_64:=ld-linux-x86-64.so.2
GCOMPAT_LDSO:=$(GCOMPAT_LDSO_$(ARCH))

GCOMPAT_LSE_OBJ:=$(if $(filter aarch64,$(ARCH)),$(PKG_BUILD_DIR)/aarch64-lse.o)

define Package/gcompat
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=glibc ABI compatibility layer for musl
  URL:=https://git.adelielinux.org/adelie/gcompat
  DEPENDS:=@USE_MUSL @(aarch64||arm||i386||loongarch64||riscv64||x86_64) \
	+aarch64:libatomic
endef

define Package/gcompat/description
  gcompat provides the glibc-only symbols musl does not implement, so that
  shared objects built against glibc load into a musl program: a browser
  plugin or a content decryption module, for example.

  The glibc interpreter name is a symlink to the library, which is how such
  an object pulls it in, since every one of them carries the interpreter in
  its dependency list. Upstream installs a loader stub there instead, which
  additionally lets whole glibc executables run; that stub needs a static
  PIE and musl's static library is not built as position-independent code.
endef

MAKE_FLAGS += \
	CFLAGS="$(TARGET_CFLAGS)" \
	CPPFLAGS="$(TARGET_CPPFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS) $(GCOMPAT_LSE_OBJ) $(if $(GCOMPAT_LSE_OBJ),-latomic)" \
	LINKER_PATH="/lib/$(GCOMPAT_MUSL_LDSO)" \
	LOADER_NAME="$(GCOMPAT_LDSO)" \
	WITH_OBSTACK=no

define Build/Compile
	$(if $(GCOMPAT_LSE_OBJ),$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_CPPFLAGS) \
		-mno-outline-atomics -fPIC -c -o $(GCOMPAT_LSE_OBJ) ./files/aarch64-lse.c)
	$(call Build/Compile/Default,libgcompat.so.0)
endef

define Package/gcompat/install
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libgcompat.so.0 $(1)/lib/
	$(LN) libgcompat.so.0 $(1)/lib/$(GCOMPAT_LDSO)
endef

$(eval $(call BuildPackage,gcompat))
