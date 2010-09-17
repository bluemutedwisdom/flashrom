sbin_PROGRAMS = flashrom

man_MANS = flashrom.8

DEFS += -DDMIDECODE_PATH=\"@DMIDECODE@\"

if HAVE_INTERNAL
internal_SOURCES = \
	board_enable.c \
	cbtable.c \
	chipset_enable.c \
	dmi.c \
	internal.c \
	processor_enable.c
if HAVE_X86_ONLY_INTERNAL
internal_x86_only_SOURCES = \
	ichspi.c \
	it85spi.c \
	it87spi.c \
	mcp6x_spi.c \
	sb600spi.c \
	wbsio_spi.c
endif
DEFS += -DCONFIG_INTERNAL=1
endif

if HAVE_SERPROG
serprog_SOURCES = serprog.c
DEFS += -DCONFIG_SERPROG=1
endif

if HAVE_RAYER_SPI
rayer_spi_SOURCES = rayer_spi.c
DEFS += -DCONFIG_RAYER_SPI=1
endif

if HAVE_BITBANG_SPI
bitbang_spi_SOURCES = bitbang_spi.c
DEFS += -DCONFIG_BITBANG_SPI=1
endif

if HAVE_NIC3COM
nic3com_SOURCES = nic3com.c
DEFS += -DCONFIG_NIC3COM=1
endif

if HAVE_GFXNVIDIA
gfxnvidia_SOURCES = gfxnvidia.c
DEFS += -DCONFIG_GFXNVIDIA=1
endif

if HAVE_SATASII
satasii_SOURCES = satasii.c
DEFS += -DCONFIG_SATASII=1
endif

if HAVE_ATAHPT
atahpt_SOURCES = atahpt.c
DEFS += -DCONFIG_ATAHPT=1
endif

if HAVE_FT2232_SPI
ft_2232_spi_SOURCES = ft2232_spi.c
DEFS += -DCONFIG_FT2232_SPI=1
endif

if HAVE_DUMMY
dummy_SOURCES= dummyflasher.c
DEFS += -DCONFIG_DUMMY=1
endif

if HAVE_DRKAISER
drkaiser_SOURCES = drkaiser.c
DEFS += -DCONFIG_DRKAISER=1
endif

if HAVE_NICREALTEK
nicrealtek_SOURCES = nicrealtek.c
DEFS += -DCONFIG_NICREALTEK=1
endif

if HAVE_NICNATSEMI
nicnatsemi_SOURCES = nicnatsemi.c
DEFS += -DCONFIG_NICNATSEMI=1
endif

if HAVE_NICINTEL
nicintel_SOURCES = nicintel.c
DEFS += -DCONFIG_NICINTEL=1
endif

if HAVE_NICINTEL_SPI
nicintel_spi_SOURCES = nicintel_spi.c
DEFS += -DCONFIG_NICINTEL_SPI=1
endif

if HAVE_GFXOGP
gfxogp_SOURCES = ogp_spi.c
DEFS += -DCONFIG_OGP_SPI=1
endif

if HAVE_BUSPIRATE_SPI
buspirate_SOURCES = buspirate_spi.c
DEFS += -DCONFIG_BUSPIRATE_SPI=1
endif

if HAVE_DEDIPROG
dediprog_SOURCES = dediprog.c
DEFS += -DCONFIG_DEDIPROG=1
endif

if HAVE_SATAMV
satamv_SOURCES = satamv.c
DEFS += -DCONFIG_SATAMV=1
endif

if HAVE_SERIAL
serial_SOURCES = serial.c
endif

if HAVE_PRINT_WIKI
print_wiki_SOURCES = print_wiki.c
DEFS += -DCONFIG_PRINT_WIKI=1
endif

if HAVE_PCI
pci_SOURCES = pcidev.c \
	      physmap.c \
	      hwaccess.c
endif

chip_SOURCES = 82802ab.c \
	       a25.c \
	       at25.c \
	       flashchips.c \
	       jedec.c \
	       m29f400bt.c \
	       pm49fl00x.c \
	       sharplhf00l04.c \
	       spi.c \
	       spi25.c \
	       sst_fwhub.c \
	       sst28sf040.c \
	       sst49lfxxxc.c \
	       stm50flw0x0x.c \
	       w29ee011.c \
	       w39.c

cli_SOURCES = \
	flashrom.c \
	cli_classic.c \
	cli_output.c \
	print.c

lib_SOURCES = layout.c

# Unknown purpose
# sharplhf00l04.c

flashrom_SOURCES = \
	programmer.c \
	udelay.c \
	$(internal_SOURCES) \
	$(internal_x86_only_SOURCES) \
	$(serprog_SOURCES) \
	$(rayer_spi_SOURCES) \
	$(bitbang_spi_SOURCES) \
	$(nic3com_SOURCES) \
	$(gfxnvidia_SOURCES) \
	$(satasii_SOURCES) \
	$(atahpt_SOURCES) \
	$(ft_2232_spi_SOURCES) \
	$(dummy_SOURCES) \
	$(drkaiser_SOURCES) \
	$(nicrealtek_SOURCES) \
	$(nicnatsemi_SOURCES) \
	$(nicintel_SOURCES) \
	$(nicintel_spi_SOURCES) \
	$(gfxogp_SOURCES) \
	$(buspirate_SOURCES) \
	$(dediprog_SOURCES) \
	$(satamv_SOURCES) \
	$(serial_SOURCES) \
	$(print_wiki_SOURCES) \
	$(pci_SOURCES) \
	$(chip_SOURCES) \
	$(cli_SOURCES) \
	$(lib_SOURCES)
