# OpenWrt package: PipeWire (minimal embedded, reproducible Meson options; no 'auto')

include $(TOPDIR)/rules.mk

PKG_NAME:=pipewire
PKG_VERSION:=1.6.8
PKG_RELEASE:=3

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://gitlab.freedesktop.org/pipewire/pipewire.git
PKG_SOURCE_VERSION:=refs/tags/$(PKG_VERSION)
PKG_MIRROR_HASH:=skip

PKG_MAINTAINER:=Mirko Vogt <mirko-openwrt@nanl.de>
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=COPYING
PKG_CPE_ID:=cpe:/a:pipewire:pipewire

PKG_FIXUP:=libtool
PKG_BUILD_PARALLEL:=1

# Optional features are individually selectable (see Package/pipewire/config).
# Listing the symbols here reconfigures and rebuilds the package whenever any of
# them is toggled.
PKG_CONFIG_DEPENDS:= \
	CONFIG_PIPEWIRE_ALSA \
	CONFIG_PIPEWIRE_PULSE \
	CONFIG_PIPEWIRE_PULSE_TUNNEL \
	CONFIG_PIPEWIRE_UDEV \
	CONFIG_PIPEWIRE_DBUS \
	CONFIG_PIPEWIRE_BLUETOOTH \
	CONFIG_PIPEWIRE_BLUETOOTH_AAC \
	CONFIG_PIPEWIRE_BLUETOOTH_LDAC \
	CONFIG_PIPEWIRE_BLUETOOTH_APTX \
	CONFIG_PIPEWIRE_BLUETOOTH_OPUS \
	CONFIG_PIPEWIRE_RAOP \
	CONFIG_PIPEWIRE_AVAHI \
	CONFIG_PIPEWIRE_V4L2 \
	CONFIG_PIPEWIRE_FFMPEG \
	CONFIG_PIPEWIRE_SNDFILE

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk

define Package/pipewire
  SECTION:=sound
  CATEGORY:=Sound
  TITLE:=PipeWire multimedia server (minimal)
  URL:=https://pipewire.org
  # Base deps are always needed; every optional feature adds its dep only when
  # the matching config symbol (Package/pipewire/config) is set.
  DEPENDS:= \
	+libatomic \
	+libstdcpp \
	+glib2 \
	+PIPEWIRE_ALSA:alsa-lib \
	+PIPEWIRE_PULSE_TUNNEL:libpulse \
	+PIPEWIRE_UDEV:libudev-zero \
	+PIPEWIRE_DBUS:libdbus \
	+PIPEWIRE_BLUETOOTH:bluez-libs \
	+PIPEWIRE_BLUETOOTH:libusb-1.0 \
	+PIPEWIRE_BLUETOOTH:sbc \
	+PIPEWIRE_BLUETOOTH_AAC:fdk-aac \
	+PIPEWIRE_BLUETOOTH_LDAC:libldac \
	+PIPEWIRE_BLUETOOTH_APTX:libfreeaptx \
	+PIPEWIRE_BLUETOOTH_OPUS:libopus \
	+PIPEWIRE_RAOP:libopenssl \
	+PIPEWIRE_AVAHI:libavahi-client \
	+PIPEWIRE_FFMPEG:ffmpeg \
	+PIPEWIRE_SNDFILE:libsndfile
  USERID:=pipewire:pipewire
endef

define Package/pipewire/description
 Minimal PipeWire multimedia server for embedded OpenWrt, running system-wide
 (procd, dedicated pipewire user). Optional features - PulseAudio-compat server,
 Bluetooth, udev, D-Bus, RAOP, Avahi, V4L2, FFmpeg, libsndfile - are individually
 selectable (toggles nested under the package entry); the default is a minimal
 ALSA + PulseAudio box. No session manager in-tree (session-managers=[]): install
 pipewire-media-session or wireplumber. No systemd/JACK/GStreamer. All meson
 options are pinned explicitly (no auto) for reproducible builds.
endef

define Package/pipewire/conffiles
/etc/pipewire/pipewire.conf.d/10-openwrt-system.conf
/etc/pipewire/pipewire.conf.d/30-openwrt-rt.conf
/etc/pipewire/client.conf.d/30-openwrt-rt.conf
endef

# Only dependency-bearing feature switches are exposed here; every other upstream
# meson option stays pinned explicitly in MESON_ARGS (no 'auto', for reproducible
# builds). Symbols are FREE-STANDING (no 'depends on PACKAGE_pipewire') and grouped
# in a menu. Reason: several deps carry an '@CONFIG' dependency (alsa-lib ->
# @AUDIO_SUPPORT, bluez-daemon -> @USB_SUPPORT, ...) which the generator folds onto
# PACKAGE_pipewire as 'depends on !(SYM) || CONFIG'; gating SYM on PACKAGE_pipewire
# would then close a Kconfig recursion. Defaults = minimal ALSA + PulseAudio box.
define Package/pipewire/config
	menu "PipeWire feature selection"

config PIPEWIRE_ALSA
	bool "ALSA backend + pipewire-alsa plugin"
	default y
	help
		Native ALSA capture/playback and the pipewire-alsa
		plugin. Pulls alsa-lib. The whole point of an audio
		box; leave on unless you only bridge other transports.

config PIPEWIRE_PULSE
	bool "PulseAudio-compatible server (pipewire-pulse)"
	default y
	help
		Install and run the pipewire-pulse server so PulseAudio
		clients (snapcast, Home Assistant, mpd, ...) work
		unmodified. module-protocol-pulse is always built and
		needs no extra dependency; this switch only controls
		installing its binary + init script.

config PIPEWIRE_PULSE_TUNNEL
	bool "PulseAudio tunnel module (bridge to a remote PA server)"
	default n
	help
		module-pulse-tunnel: connect this pipewire instance as a
		client to a REMOTE PulseAudio / pipewire-pulse server.
		This is the ONLY pulse feature that links the real
		libpulse client library (-Dlibpulse), which in turn pulls
		libsndfile (and thus lame/mpg123). Leave off unless you
		specifically tunnel to another PA server.

config PIPEWIRE_UDEV
	bool "udev device hotplug detection"
	default y
	help
		Auto-detect ALSA cards via udev. Pulls libudev-zero.

config PIPEWIRE_DBUS
	bool "D-Bus support (rtkit / device reservation)"
	default n
	help
		D-Bus client support. Required by Bluetooth; also used
		for rtkit realtime scheduling and device reservation.
		Pulls libdbus. Needs a running dbus daemon at runtime.

config PIPEWIRE_BLUETOOTH
	bool "Bluetooth audio (bluez5: A2DP/HSP/HFP)"
	default n
	select PIPEWIRE_DBUS
	help
		Bluetooth audio via the bluez5 SPA plugin (SBC codec
		always included). Forces D-Bus on and pulls bluez-libs,
		libusb-1.0 and sbc. Needs bluez-daemon + dbus running,
		and a session manager with its bluez monitor enabled.

config PIPEWIRE_BLUETOOTH_AAC
	bool "Bluetooth AAC codec"
	depends on PIPEWIRE_BLUETOOTH
	# fdk-aac itself is gated on @BUILD_PATENTED (no patent rights in
	# the FDK license, no upstream free build mode, Debian non-free) -
	# that gate is the enforcement, inherited by every consumer. This
	# line only mirrors it for menuconfig UX: without it, enabling AAC
	# on a non-BUILD_PATENTED config would hide the whole pipewire
	# package (folded guard) instead of hiding this option. libldac and
	# libfreeaptx are in Debian main and carry no gate.
	depends on BUILD_PATENTED
	default y
	help
		MPEG-2/4 AAC codec for A2DP. Pulls fdk-aac (whose license
		grants no patent rights; AAC licensing may apply).

config PIPEWIRE_BLUETOOTH_LDAC
	bool "Bluetooth LDAC codec (encode)"
	depends on PIPEWIRE_BLUETOOTH
	default n
	help
		Sony LDAC codec for high-quality A2DP (up to 990 kbps)
		to LDAC-capable speakers/headphones. Pulls libldac
		(encoder + ABR; encode-only - no open-source decoder
		exists).

config PIPEWIRE_BLUETOOTH_APTX
	bool "Bluetooth aptX / aptX HD codec"
	depends on PIPEWIRE_BLUETOOTH
	# No BUILD_PATENTED gate: Debian ships libfreeaptx in main (unlike
	# fdk-aac); the foundational aptX patents are expired. Note Fedora
	# disagrees (RPM Fusion only), and "aptX" remains a Qualcomm
	# trademark - do not use the name in product marketing.
	default n
	help
		Qualcomm aptX and aptX HD codecs for A2DP (and aptX-LL
		via the faststream framing). Pulls libfreeaptx.

config PIPEWIRE_BLUETOOTH_OPUS
	bool "Bluetooth Opus codec"
	depends on PIPEWIRE_BLUETOOTH
	default y
	help
		Opus codec for A2DP Bluetooth. Pulls libopus.
		Note: this also flips pipewire's general '-Dopus'
		support (not Bluetooth-specific) on/off - harmless,
		since nothing outside the Bluetooth codec uses Opus
		in this build.

config PIPEWIRE_RAOP
	bool "RAOP / AirPlay sink"
	default n
	help
		Stream to AirPlay receivers. Pulls libopenssl.

config PIPEWIRE_AVAHI
	bool "Avahi / zeroconf discovery"
	default n
	help
		Announce/discover network audio over mDNS. Pulls
		libavahi-client.

config PIPEWIRE_V4L2
	bool "Video4Linux2 capture"
	default n
	help
		V4L2 SPA plugin and pipewire-v4l2 shim. Uses the kernel
		V4L2 API; no extra userspace dependency.

config PIPEWIRE_FFMPEG
	bool "FFmpeg SPA plugin"
	default n
	help
		Extra codecs/formats via FFmpeg. Pulls ffmpeg (large).

config PIPEWIRE_SNDFILE
	bool "libsndfile support (pw-cat, filter-chain file I/O)"
	default n
	help
		Enables sound-file I/O for pw-cat and module-filter-chain.
		Pulls libsndfile.
	endmenu
endef

# Match enabled components + typical pipewire binary deps; extend if you re-enable features.

PKG_BUILD_DEPENDS:= \
	meson/host \
	ninja/host

MESON_ARGS += \
	-Ddocs=disabled \
	-Dman=disabled \
	-Dexamples=disabled \
	-Dtests=disabled \
	-Dinstalled_tests=disabled \
	-Dgstreamer=disabled \
	-Dgstreamer-device-provider=disabled \
	-Dlibsystemd=disabled \
	-Dlogind=disabled \
	-Dlogind-provider=libsystemd \
	-Dsystemd-system-service=disabled \
	-Dsystemd-user-service=disabled \
	-Dselinux=disabled \
	-Dpipewire-alsa=$(if $(CONFIG_PIPEWIRE_ALSA),enabled,disabled) \
	-Dpipewire-jack=disabled \
	-Dpipewire-v4l2=$(if $(CONFIG_PIPEWIRE_V4L2),enabled,disabled) \
	-Djack-devel=false \
	-Dlibjack-path='' \
	-Dlibv4l2-path='' \
	-Dspa-plugins=enabled \
	-Dalsa=$(if $(CONFIG_PIPEWIRE_ALSA),enabled,disabled) \
	-Daudiomixer=enabled \
	-Daudioconvert=enabled \
	-Dbluez5=$(if $(CONFIG_PIPEWIRE_BLUETOOTH),enabled,disabled) \
	-Dbluez5-backend-hsp-native=$(if $(CONFIG_PIPEWIRE_BLUETOOTH),enabled,disabled) \
	-Dbluez5-backend-hfp-native=$(if $(CONFIG_PIPEWIRE_BLUETOOTH),enabled,disabled) \
	-Dbluez5-backend-native-mm=disabled \
	-Dbluez5-backend-ofono=disabled \
	-Dbluez5-backend-hsphfpd=disabled \
	-Dbluez5-codec-aptx=$(if $(CONFIG_PIPEWIRE_BLUETOOTH_APTX),enabled,disabled) \
	-Dbluez5-codec-ldac=$(if $(CONFIG_PIPEWIRE_BLUETOOTH_LDAC),enabled,disabled) \
	-Dbluez5-codec-ldac-dec=disabled \
	-Dbluez5-codec-aac=$(if $(CONFIG_PIPEWIRE_BLUETOOTH_AAC),enabled,disabled) \
	-Dbluez5-codec-lc3plus=disabled \
	-Dbluez5-codec-opus=$(if $(CONFIG_PIPEWIRE_BLUETOOTH_OPUS),enabled,disabled) \
	-Dbluez5-codec-lc3=disabled \
	-Dbluez5-codec-g722=disabled \
	-Dbluez5-plc-spandsp=disabled \
	-Dcontrol=enabled \
	-Daudiotestsrc=disabled \
	-Dffmpeg=$(if $(CONFIG_PIPEWIRE_FFMPEG),enabled,disabled) \
	-Djack=disabled \
	-Dsupport=enabled \
	-Devl=disabled \
	-Dtest=disabled \
	-Dv4l2=$(if $(CONFIG_PIPEWIRE_V4L2),enabled,disabled) \
	-Ddbus=$(if $(CONFIG_PIPEWIRE_DBUS),enabled,disabled) \
	-Dlibcamera=disabled \
	-Dvideoconvert=disabled \
	-Dvideotestsrc=disabled \
	-Dvolume=disabled \
	-Dvulkan=disabled \
	-Dpw-cat=$(if $(CONFIG_PIPEWIRE_SNDFILE),enabled,disabled) \
	-Dpw-cat-ffmpeg=disabled \
	-Dudev=$(if $(CONFIG_PIPEWIRE_UDEV),enabled,disabled) \
	-Dsdl2=disabled \
	-Dsndfile=$(if $(CONFIG_PIPEWIRE_SNDFILE),enabled,disabled) \
	-Dlibmysofa=disabled \
	-Dlibpulse=$(if $(CONFIG_PIPEWIRE_PULSE_TUNNEL),enabled,disabled) \
	-Droc=disabled \
	-Davahi=$(if $(CONFIG_PIPEWIRE_AVAHI),enabled,disabled) \
	-Decho-cancel-webrtc=disabled \
	-Dlibusb=$(if $(CONFIG_PIPEWIRE_BLUETOOTH),enabled,disabled) \
	-Dsession-managers='[]' \
	-Draop=$(if $(CONFIG_PIPEWIRE_RAOP),enabled,disabled) \
	-Dlv2=disabled \
	-Dx11=disabled \
	-Dx11-xfixes=disabled \
	-Dlibcanberra=disabled \
	-Dlegacy-rtkit=false \
	-Davb=disabled \
	-Dflatpak=disabled \
	-Dreadline=disabled \
	-Dgsettings=disabled \
	-Dcompress-offload=disabled \
	-Dpam-defaults-install=false \
	-Dpam-memlock-default=8192 \
	-Drlimits-install=false \
	-Drlimits-match='@pipewire' \
	-Drtprio-server=88 \
	-Drtprio-client=83 \
	-Drlimits-rtprio=95 \
	-Drlimits-memlock=4194304 \
	-Drlimits-nice=-19 \
	-Dopus=$(if $(CONFIG_PIPEWIRE_BLUETOOTH_OPUS),enabled,disabled) \
	-Dlibffado=disabled \
	-Dgsettings-pulse-schema=disabled \
	-Dsnap=disabled \
	-Debur128=disabled \
	-Dfftw=disabled \
	-Donnxruntime=disabled

# Remaining meson_options.txt entries, pinned so EVERY option is explicit (no
# reliance on upstream defaults). resampler-precomp-tuples keeps upstream's
# precomputed coefficients incl. 44100<->48000 - relevant when resampling
# sources into the 48k SPDIF sink. The rest are install-path / doc-display
# strings pinned to their upstream defaults; inert in this build (docs and
# systemd are disabled) but fixed for full reproducibility.
MESON_ARGS += \
	-Dresampler-precomp-tuples="['32000,44100','32000,48000','48000,44100','44100,48000']" \
	-Ddocdir=/usr/share/doc/pipewire \
	-Ddoc-prefix-value='' \
	-Ddoc-sysconfdir-value='' \
	-Dudevrulesdir=/lib/udev/rules.d \
	-Dsystemd-system-unit-dir=/usr/lib/systemd/system \
	-Dsystemd-user-unit-dir=/usr/lib/systemd/user

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/pipewire-0.3 $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/include/spa-0.2 $(1)/usr/include/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib*.so* $(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/lib*.pc $(1)/usr/lib/pkgconfig/
endef

define Package/pipewire/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/pipewire $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pipewire-0.3 $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/spa-0.2 $(1)/usr/lib/
	# pipewire-alsa plugin dir only exists when the ALSA backend is built
	$(if $(CONFIG_PIPEWIRE_ALSA),$(CP) $(PKG_INSTALL_DIR)/usr/lib/alsa-lib $(1)/usr/lib/)

	# ALSA card-profile (ACP) data: mixer paths + profile-sets. Required for
	# udev/session-manager card management (WirePlumber) to build card
	# profiles - including the IEC958 (S/PDIF) AC3/DTS passthrough profiles
	# and HDMI passthrough. Without this dir acp_card_new() has no profile
	# data and digital-passthrough sinks never appear.
	$(if $(CONFIG_PIPEWIRE_ALSA),$(INSTALL_DIR) $(1)/usr/share/alsa-card-profile)
	$(if $(CONFIG_PIPEWIRE_ALSA),$(CP) $(PKG_INSTALL_DIR)/usr/share/alsa-card-profile/* $(1)/usr/share/alsa-card-profile/)

	$(INSTALL_DIR) $(1)/usr/share/pipewire
	$(CP) $(PKG_INSTALL_DIR)/usr/share/pipewire/* $(1)/usr/share/pipewire/

	#$(INSTALL_DIR) $(1)/lib/udev/rules.d
	#$(CP) $(PKG_INSTALL_DIR)/lib/udev/rules.d/* $(1)/lib/udev/rules.d/

	$(INSTALL_DIR) $(1)/etc/pipewire/pipewire.conf.d
	# system-mode drop-in: run as a single central daemon with a fixed socket name,
	# layered on top of the stock /usr/share/pipewire/pipewire.conf
	$(INSTALL_DATA) ./files/10-openwrt-system.conf $(1)/etc/pipewire/pipewire.conf.d/10-openwrt-system.conf
	# no-RTKit realtime: force module-rt onto the direct sched_setscheduler
	# path (no RTKit service on OpenWrt). Installed for the daemon AND for
	# every libpipewire client (client.conf.d) - clients run module-rt too.
	$(INSTALL_DATA) ./files/30-openwrt-rt.conf $(1)/etc/pipewire/pipewire.conf.d/30-openwrt-rt.conf
	$(INSTALL_DIR) $(1)/etc/pipewire/client.conf.d
	$(INSTALL_DATA) ./files/30-openwrt-rt.conf $(1)/etc/pipewire/client.conf.d/30-openwrt-rt.conf

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/pipewire.init $(1)/etc/init.d/pipewire

	# hotplug hook: restart the stack when a sound card comes/goes (the
	# udev-less ALSA setup only creates static nodes at startup)
	$(INSTALL_DIR) $(1)/etc/hotplug.d/sound
	$(INSTALL_DATA) ./files/pipewire-hotplug $(1)/etc/hotplug.d/sound/20-pipewire

	# pipewire-pulse (PulseAudio-compatible server) is optional
	$(if $(CONFIG_PIPEWIRE_PULSE),$(CP) $(PKG_INSTALL_DIR)/usr/bin/pipewire-pulse $(1)/usr/bin/)
	$(if $(CONFIG_PIPEWIRE_PULSE),$(INSTALL_DIR) $(1)/etc/pipewire/pipewire-pulse.conf.d)
	$(if $(CONFIG_PIPEWIRE_PULSE),$(INSTALL_DATA) ./files/30-openwrt-rt.conf $(1)/etc/pipewire/pipewire-pulse.conf.d/30-openwrt-rt.conf)
	$(if $(CONFIG_PIPEWIRE_PULSE),$(INSTALL_BIN) ./files/pipewire-pulse.init $(1)/etc/init.d/pipewire-pulse)

	# D-Bus system policy letting the unprivileged pipewire user drive BlueZ
	# (register media endpoints + reply to bluetoothd callbacks). Only needed
	# when Bluetooth is built in; without it A2DP fails with "Resource busy".
	$(if $(CONFIG_PIPEWIRE_BLUETOOTH),$(INSTALL_DIR) $(1)/etc/dbus-1/system.d)
	$(if $(CONFIG_PIPEWIRE_BLUETOOTH),$(INSTALL_DATA) ./files/pipewire-bluez.conf $(1)/etc/dbus-1/system.d/pipewire-bluez.conf)
endef

define Package/pipewire-tools
  SECTION:=sound
  CATEGORY:=Sound
  TITLE:=PipeWire command-line tools (pw-*)
  URL:=https://pipewire.org
  # They link libpipewire from the main package; pw-top additionally links
  # ncurses (libncursesw.so) for its terminal UI.
  DEPENDS:=+pipewire +libncurses
endef

define Package/pipewire-tools/description
 The PipeWire command-line utilities: pw-cli, pw-dump, pw-mon, pw-top, pw-link,
 pw-metadata, pw-loopback, pw-config, pw-dot, pw-profiler, ... - and the
 pw-cat family (pw-cat/pw-play/pw-record/pw-midi*), which is only present when
 the pipewire package is built with libsndfile support (PIPEWIRE_SNDFILE).
 Built anyway by the pipewire package but shipped separately so they can be
 left out of minimal images. Handy for inspecting/debugging the graph on-device.
endef

define Package/pipewire-tools/install
	$(INSTALL_DIR) $(1)/usr/bin
	# All built pw-* utilities; $(CP) preserves the pw-play/pw-record -> pw-cat
	# symlinks. The glob simply installs whatever tools this build produced.
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/pw-* $(1)/usr/bin/
endef

$(eval $(call BuildPackage,pipewire))
$(eval $(call BuildPackage,pipewire-tools))
