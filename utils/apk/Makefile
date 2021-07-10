include $(TOPDIR)/rules.mk

PKG_NAME:=apk
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://git.alpinelinux.org/apk-tools.git
PKG_SOURCE_DATE:=2021-07-16
PKG_SOURCE_VERSION:=d909ebc25b23c0ccd698f161ab624c3cdc890e35
PKG_MIRROR_HASH:=ae0e504e393647bd30443fe6b8cc5b73da42a9fd47606c23e23461696fa7c2d4

PKG_MAINTAINER:=Paul Spooren <mail@aparcar.org>
PKG_LICENSE:=GPL-2.0-only
PKG_LICENSE_FILES:=LICENSE

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

HOST_BUILD_DEPENDS:=lua/host lua-lzlib/host meson/host
PKG_BUILD_DEPENDS:=$(HOST_BUILD_DEPENDS)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk
include ../../devel/meson/meson.mk

MESON_HOST_ARGS += -Dlua_version=5.1 -Dlua=disabled -Ddocs=disabled -Dhelp=enabled
MESON_ARGS += -Dlua_version=5.1 -Dlua=disabled -Ddocs=disabled -Dhelp=enabled
HOST_LDFLAGS += -liconv -Wl,-rpath,$(STAGING_DIR_HOSTPKG)/lib

define Package/apk
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=apk package manager
  DEPENDS:=+zlib +libopenssl +libpthread @!arc
  URL:=$(PKG_SOURCE_URL)
endef

define Package/alpine-keys
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Alpine apk public signing keys
  DEPENDS:=apk
endef

define Package/alpine-repositories
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Official Alpine repositories
  DEPENDS:=apk
endef

HOST_CFLAGS += -I$(STAGING_DIR_HOSTPKG)/lib/
HOST_LDFLAGS += -pthread

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libapk* $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/include/apk
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/include/apk/* $(1)/usr/include/apk

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/apk.pc \
		$(1)/usr/lib/pkgconfig/
endef

define Package/apk/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/apk $(1)/usr/bin

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libapk.so.* $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/etc/apk/
	echo $(ARCH) > $(1)/etc/apk/arch
	touch $(1)/etc/apk/world

	$(INSTALL_DIR) $(1)/lib/apk/db
endef

define Package/alpine-keys/install
	$(INSTALL_DIR) $(1)/etc/apk/keys
	$(INSTALL_DATA) ./files/alpine-keys/* $(1)/etc/apk/keys
endef

define Package/alpine-repositories/install
	$(INSTALL_DIR) $(1)/etc/apk/keys
	$(INSTALL_DATA) ./files/alpine-repositories $(1)/etc/apk/repositories
endef

$(eval $(call BuildPackage,apk))
$(eval $(call BuildPackage,alpine-keys))
$(eval $(call BuildPackage,alpine-repositories))
$(eval $(call HostBuild))
