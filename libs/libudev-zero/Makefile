# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libudev-zero
PKG_VERSION:=1.0.5
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/illiliti/libudev-zero/tar.gz/$(PKG_VERSION)?
PKG_HASH:=bf4372f79ddbe6b0e266a3d2994ffac7018a7edf4f87632aecb5176565d96138

PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=ISC
PKG_LICENSE_FILES:=LICENSE

PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libudev-zero
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Drop-in replacement for libudev
  URL:=https://github.com/illiliti/libudev-zero
  PROVIDES:=libudev
  CONFLICTS:=libudev eudev udev
endef

define Package/libudev-zero-hotplug
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Hotplug uevent rebroadcaster for libudev-zero monitors
  URL:=https://github.com/illiliti/libudev-zero
  DEPENDS:=+libudev-zero
endef

define Package/libudev-zero-hotplug/description
 libudev-zero's udev_monitor listens on netlink group 0x4, NOT on the
 kernel's uevent group - by upstream design an external component must
 rebroadcast kernel uevents to that group (see contrib/ upstream), or every
 libudev monitor is deaf and applications only see devices present at
 startup (e.g. Kodi/libinput never noticing a Bluetooth remote that
 connects while running). This package provides upstream's contrib helper
 (env -> netlink 0x4) wired into procd via /etc/hotplug.d/ for the input
 and drm subsystems (input device hotplug + display/HDMI hotplug). The
 hotplug scripts carry a marker through the rebroadcast to stop procd from
 amplifying our own messages into an event storm (procd receives group-0x4
 messages too).
endef

MAKE_FLAGS += \
	PREFIX=/usr

# upstream builds only the library; the contrib rebroadcast helper (a
# single self-contained C file, no deps) is compiled here explicitly
define Build/Compile
	$(call Build/Compile/Default)
	$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) \
		-o $(PKG_BUILD_DIR)/contrib/uevent-rebroadcast \
		$(PKG_BUILD_DIR)/contrib/helper.c
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/libudev.h $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libudev.{a,so*} $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/libudev.pc $(1)/usr/lib/pkgconfig/
endef

define Package/libudev-zero/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libudev.so* $(1)/usr/lib/
endef

define Package/libudev-zero-hotplug/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/contrib/uevent-rebroadcast $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/hotplug.d/input
	$(INSTALL_DATA) ./files/uevent-rebroadcast.hotplug \
		$(1)/etc/hotplug.d/input/99-uevent-rebroadcast
	$(INSTALL_DIR) $(1)/etc/hotplug.d/drm
	$(INSTALL_DATA) ./files/uevent-rebroadcast.hotplug \
		$(1)/etc/hotplug.d/drm/99-uevent-rebroadcast
endef

$(eval $(call BuildPackage,libudev-zero))
$(eval $(call BuildPackage,libudev-zero-hotplug))
