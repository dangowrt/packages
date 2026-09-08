include $(TOPDIR)/rules.mk

PKG_NAME:=wireplumber
PKG_VERSION:=0.5.13
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://gitlab.freedesktop.org/pipewire/$(PKG_NAME).git
PKG_SOURCE_VERSION:=refs/tags/$(PKG_VERSION)
PKG_MIRROR_HASH:=skip

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Mirko Vogt <mirko-openwrt@nanl.de>
PKG_BUILD_PARALLEL:=1

PKG_CONFIG_DEPENDS:= \
	CONFIG_WIREPLUMBER_TOOLS \
	CONFIG_WIREPLUMBER_INTROSPECTION \
	CONFIG_WIREPLUMBER_BLUETOOTH

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk

define Package/wireplumber
  SECTION:=sound
  CATEGORY:=Sound
  TITLE:=WirePlumber session manager (minimal)
  URL:=https://pipewire.pages.freedesktop.org/wireplumber/
  DEPENDS:=+pipewire +glib2 +libstdcpp +libpthread \
	+WIREPLUMBER_BLUETOOTH:bluez-daemon
  # WirePlumber and pipewire-media-session are interchangeable, mutually
  # exclusive session managers for pipewire: provide the same virtual role
  # and conflict so at most one is installed.
  PROVIDES:=pipewire-session-manager
  CONFLICTS:=pipewire-media-session
endef

define Package/wireplumber/description
 Minimal WirePlumber build for OpenWrt system-mode PipeWire deployments.
 WirePlumber is the recommended session/policy manager for PipeWire and the
 upstream-preferred replacement for pipewire-media-session.
endef

# WirePlumber has no per-monitor build option (monitors are runtime/config), so
# Bluetooth here only installs the monitor-enabling drop-in + pulls bluez-daemon;
# it defaults to pipewire's Bluetooth setting to keep the stack coherent.
define Package/wireplumber/config
	menu "WirePlumber feature selection"

config WIREPLUMBER_TOOLS
	bool "Install CLI tools (wpctl, wpexec)"
	default y
	help
		Command-line tools for inspecting/controlling the
		graph (wpctl status, wpctl set-default, ...).

config WIREPLUMBER_INTROSPECTION
	bool "GObject-introspection data"
	default n
	help
		Build GObject-introspection typelibs. Only needed
		for language bindings; off for a headless box.

config WIREPLUMBER_BLUETOOTH
	bool "Bluetooth monitor"
	default PIPEWIRE_BLUETOOTH
	help
		Install a drop-in that enables WirePlumber's bluez
		monitor so it discovers and routes Bluetooth audio
		devices. Only useful when pipewire was built with
		Bluetooth support. Pulls bluez-daemon (runtime).
	endmenu
endef

define Package/wireplumber/conffiles
/etc/wireplumber/wireplumber.conf.d/10-openwrt-system.conf
/etc/wireplumber/wireplumber.conf.d/20-openwrt-no-dbus.conf
/etc/wireplumber/wireplumber.conf.d/30-openwrt-bluez.conf
/etc/wireplumber/wireplumber.conf.d/35-openwrt-bluez-quality.conf
/etc/wireplumber/wireplumber.conf.d/40-openwrt-static-stream-targets.conf
/etc/wireplumber/wireplumber.conf.d/50-openwrt-rt.conf
endef

# All options from upstream meson_options.txt are explicit; defaults overridden for minimal build.
MESON_ARGS += \
	-Dintrospection=$(if $(CONFIG_WIREPLUMBER_INTROSPECTION),enabled,disabled) \
	-Ddoc=disabled \
	-Dmodules=true \
	-Ddaemon=true \
	-Dtools=$(if $(CONFIG_WIREPLUMBER_TOOLS),true,false) \
	-Dsystem-lua=false \
	-Dsystem-lua-version=5.3 \
	-Delogind=disabled \
	-Dsystemd=disabled \
	-Dsystemd-system-service=false \
	-Dsystemd-user-service=false \
	-Dglib-supp='' \
	-Dtests=false \
	-Ddbus-tests=false \
	-Dsystemd-system-unit-dir=/usr/lib/systemd/system \
	-Dsystemd-user-unit-dir=/usr/lib/systemd/user

define Package/wireplumber/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/wireplumber $(1)/usr/bin/
	# wpctl/wpexec only exist when tools are built (brace-expansion avoided:
	# the comma would be parsed as a make $(if) argument separator)
	$(if $(CONFIG_WIREPLUMBER_TOOLS),$(CP) $(PKG_INSTALL_DIR)/usr/bin/wpctl $(PKG_INSTALL_DIR)/usr/bin/wpexec $(1)/usr/bin/)

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.{so*,a} $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/wireplumber-0.5 $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/share/wireplumber
	$(CP) $(PKG_INSTALL_DIR)/usr/share/wireplumber/* $(1)/usr/share/wireplumber/

	# system-mode drop-ins: single instance; base profile is alsa-only. The bluez
	# monitor (30-) is layered on only when Bluetooth is enabled, mirroring pipewire.
	$(INSTALL_DIR) $(1)/etc/wireplumber/wireplumber.conf.d
	$(INSTALL_DATA) ./files/10-openwrt-system.conf $(1)/etc/wireplumber/wireplumber.conf.d/10-openwrt-system.conf
	$(INSTALL_DATA) ./files/20-openwrt-no-dbus.conf $(1)/etc/wireplumber/wireplumber.conf.d/20-openwrt-no-dbus.conf
	$(if $(CONFIG_WIREPLUMBER_BLUETOOTH),$(INSTALL_DATA) ./files/30-openwrt-bluez.conf $(1)/etc/wireplumber/wireplumber.conf.d/30-openwrt-bluez.conf)
	$(if $(CONFIG_WIREPLUMBER_BLUETOOTH),$(INSTALL_DATA) ./files/35-openwrt-bluez-quality.conf $(1)/etc/wireplumber/wireplumber.conf.d/35-openwrt-bluez-quality.conf)
	$(INSTALL_DATA) ./files/40-openwrt-static-stream-targets.conf $(1)/etc/wireplumber/wireplumber.conf.d/40-openwrt-static-stream-targets.conf
	$(INSTALL_DATA) ./files/50-openwrt-rt.conf $(1)/etc/wireplumber/wireplumber.conf.d/50-openwrt-rt.conf

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/wireplumber.init $(1)/etc/init.d/wireplumber
endef

$(eval $(call BuildPackage,wireplumber))
