#Owned by DairyMan@Whirlpool
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-rooter-lite-no-wifi
PKG_VERSION:=1.000
PKG_RELEASE:=1
PKG_MAINTAINER:=Created by DM/makefile by Cobia@whirlpool
include $(INCLUDE_DIR)/package.mk

define Package/ext-rooter-lite-no-wifi
 SECTION:=utils
 CATEGORY:=ROOter
 DEPENDS:=+luci +ext-rooter-basic +ext-extra \
		+luci-app-ddns +ddns-scripts \
		+luci-app-rootervpn +ext-wireguard \
		+bwmon +464xlat +iperf \
		+ext-theme +luci-theme-materialgrey +ext-login \
		+ca-bundle +ca-certificates +libustream-wolfssl \
		+luci-app-ksmbd +usb-storage +kmod-mtd-rw \
		+ext-p910nd +luci-app-sqm \
		+kmod-sched-cake +luci-app-nft-qos \
		+ext-command +luci-app-shadowsocks-libev +simple-obfs \
		+usbmuxd +libusbmuxd-utils \
		+libimobiledevice-utils +kmod-usb-net-ipheth \
		+qlog +luci-ssl +usbutils \
		+openssl-util \
		+nano +picocom +webconsole \
		+wget +qfirehose +luci-app-vpnbypass 
  TITLE:=ROOter support w/o WiFi routers
  PKGARCH:=all
endef

define Package/ext-rooter-lite-no-wifi/description
  Helper scripts to enable ROOter w/o WiFi routers
endef

define Build/Compile
endef

$(eval $(call BuildPackage,ext-rooter-lite-no-wifi))
