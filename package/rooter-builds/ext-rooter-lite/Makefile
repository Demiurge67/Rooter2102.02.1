#Owned by DairyMan@Whirlpool
#
#Copyright GNU act.
include $(TOPDIR)/rules.mk

PKG_NAME:=ext-rooter-lite
PKG_VERSION:=1.000
PKG_RELEASE:=1

PKG_MAINTAINER:=Created by DM/makefile by Cobia@whirlpool
include $(INCLUDE_DIR)/package.mk

define Package/ext-rooter-lite
 SECTION:=utils
 CATEGORY:=ROOter
 DEPENDS:=+luci +ext-rooter-basic \
		+luci-app-ddns +ddns-scripts \
		+luci-app-rootervpn +ext-wireguard \
		+bwmon +464xlat \
		+ext-theme +luci-theme-argon \
		+ext-login \
		+ca-bundle +ca-certificates +libustream-wolfssl \
		+luci-app-ksmbd +usb-storage +kmod-mtd-rw \
		+luci-app-sqm \
		+kmod-sched-cake +luci-app-nft-qos \
		+ext-command +luci-app-shadowsocks-libev +simple-obfs \
		+ext-extra +luci-app-hotspot \
		+luci-app-wol \
		+usbmuxd +libusbmuxd-utils \
		+libimobiledevice-utils +kmod-usb-net-ipheth \
		+qlog +luci-ssl +usbutils \
		+openssl-util +irqbalance \
		+nano +picocom +webconsole +iperf \
		+wget +qfirehose +luci-app-vpnbypass 
  TITLE:=ROOter support w/o MWan3 for 16+MB routers
  PKGARCH:=all
endef

define Package/ext-rooter-lite/description
  Helper scripts to enable ROOter support w/o MWan3 for 16+MB routers
endef

define Build/Compile
endef

$(eval $(call BuildPackage,ext-rooter-lite))
