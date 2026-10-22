# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2025 OpenWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=glycin
PKG_VERSION:=2.1.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=https://download.gnome.org/sources/glycin/$(basename $(PKG_VERSION))/
PKG_HASH:=8e8e92e312b14d2c5f3a047bdc5305adcb9931ef0150cf74bf526a3741e6fb32

PKG_MAINTAINER:=
PKG_LICENSE:=MPL-2.0 LGPL-2.1-or-later
PKG_LICENSE_FILES:=LICENSE LICENSE-LGPL-2.1 LICENSE-MPL-2.0

# PKG_BUILD_DEPENDS:=rust/host
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk
include ../../lang/rust/rust-values.mk

MESON_VARS += $(CARGO_PKG_CONFIG_VARS)

define Package/libglycin
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Sandboxed image loading library (C API)
  URL:=https://gnome.pages.gitlab.gnome.org/glycin/
  DEPENDS:=$(RUST_ARCH_DEPENDS) +fontconfig +glib2 +libseccomp +liblcms2
endef

define Package/libglycin/description
  Glycin provides a sandboxed image decoding library for safely loading
  and rendering images of various formats. This package contains the C
  API bindings (libglycin).
endef

define Package/glycin-loaders
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Glycin image format loaders
  URL:=https://gnome.pages.gitlab.gnome.org/glycin/
  DEPENDS:=$(RUST_ARCH_DEPENDS) +libglycin +libseccomp
endef

define Package/glycin-loaders/description
  Glycin image format loaders built with the Rust image crate. Supports
  BMP, DDS, GIF, HDR, ICO, JPEG, PNG, PNM, QOI, TGA, TIFF, and WebP.
endef

MESON_ARGS += \
	-Dlibglycin=true \
	-Dlibglycin-gtk4=false \
	-Dglycin-loaders=true \
	-Dloaders=glycin-image-rs \
	-Dglycin-thumbnailer=false \
	-Dtests=false \
	-Dintrospection=false \
	-Dvapi=false \
	-Dcapi_docs=false \
	-Dpython_tests=false \
	-Dlto=false

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/glycin-2
	$(CP) $(PKG_INSTALL_DIR)/usr/include/glycin-2/glycin.h \
		$(1)/usr/include/glycin-2/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libglycin-2.so* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/glycin-2.pc \
		$(1)/usr/lib/pkgconfig/
endef

define Package/libglycin/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libglycin-2.so.* $(1)/usr/lib/
endef

define Package/glycin-loaders/install
	$(INSTALL_DIR) $(1)/usr/libexec/glycin-loaders/2+
	$(CP) $(PKG_INSTALL_DIR)/usr/libexec/glycin-loaders/2+/glycin-image-rs \
		$(1)/usr/libexec/glycin-loaders/2+/
	$(INSTALL_DIR) $(1)/usr/share/glycin-loaders/2+/conf.d
	$(CP) $(PKG_INSTALL_DIR)/usr/share/glycin-loaders/2+/conf.d/glycin-image-rs.conf \
		$(1)/usr/share/glycin-loaders/2+/conf.d/
endef

$(eval $(call BuildPackage,libglycin))
$(eval $(call BuildPackage,glycin-loaders))
