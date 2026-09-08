#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=fstrcmp
PKG_VERSION:=0.7
PKG_UPSTREAM_VERSION:=0.7.D001
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_UPSTREAM_VERSION).tar.gz
PKG_SOURCE_URL:=@SF/fstrcmp
PKG_HASH:=e4018e850f80700acee8da296e56e15b1eef711ab15157e542e7d7e1237c3476
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_UPSTREAM_VERSION)

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=GPL-3.0-or-later
PKG_LICENSE_FILES:=LICENSE

PKG_BUILD_PARALLEL:=1
PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libfstrcmp
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Fuzzy string comparison library
  URL:=https://fstrcmp.sourceforge.net/
endef

define Package/libfstrcmp/description
  The fstrcmp library makes fuzzy comparisons of strings and byte
  arrays, including multi-byte character strings.
endef

CONFIGURE_ARGS += --prefix=/usr

# Build/install only program+library artifacts: the doc targets render
# PDFs via groff/ps2pdf, which the build host need not provide.
define Build/Compile
	$(call Build/Compile/Default,all-bin)
endef

define Build/Install
	$(call Build/Install/Default,install-bin install-include install-libdir)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/fstrcmp.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libfstrcmp.{a,so*} $(1)/usr/lib/
	# packages looking fstrcmp up via pkg-config need the .pc;
	# rewrite the absolute paths relative to ${prefix} so OpenWrt's
	# pkg-config wrapper resolves them inside the staging dir
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/fstrcmp.pc $(1)/usr/lib/pkgconfig/
	$(SED) 's,^libdir=.*,libdir=$$$${exec_prefix}/lib,; s,^includedir=.*,includedir=$$$${prefix}/include,' \
		$(1)/usr/lib/pkgconfig/fstrcmp.pc
endef

define Package/libfstrcmp/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libfstrcmp.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libfstrcmp))
