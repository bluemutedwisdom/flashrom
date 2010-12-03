/*
 * This file is part of the flashrom project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2009 Carl-Daniel Hailfinger
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "flash.h"
#include "flashchips.h"
#include "programmer.h"

static const char * const wiki_header = "= Supported devices =\n\n\
<div style=\"margin-top:0.5em; padding:0.5em 0.5em 0.5em 0.5em; \
background-color:#eeeeee; align:right; border:1px solid #aabbcc;\"><small>\n\
Please do '''not''' edit these tables in the wiki directly, they are \
generated by pasting '''flashrom -z''' output.<br />\
'''Last update:''' %s(generated by flashrom %s)\n</small></div>\n";

#if CONFIG_INTERNAL == 1
static const char * const chipset_th = "{| border=\"0\" style=\"font-size: smaller\"\n\
|- bgcolor=\"#6699dd\"\n! align=\"left\" | Vendor\n\
! align=\"left\" | Southbridge\n! align=\"left\" | PCI IDs\n\
! align=\"left\" | Status\n\n";

static const char * const board_th = "{| border=\"0\" style=\"font-size: smaller\" \
valign=\"top\"\n|- bgcolor=\"#6699dd\"\n! align=\"left\" | Vendor\n\
! align=\"left\" | Mainboard\n! align=\"left\" | Required option\n! align=\"left\" | Status\n\n";

static const char * const board_intro = "\
\n== Supported mainboards ==\n\n\
In general, it is very likely that flashrom works out of the box even if your \
mainboard is not listed below.\n\nThis is a list of mainboards where we have \
verified that they either do or do not need any special initialization to \
make flashrom work (given flashrom supports the respective chipset and flash \
chip), or that they do not yet work at all. If they do not work, support may \
or may not be added later.\n\n\
Mainboards which don't appear in the list may or may not work (we don't \
know, someone has to give it a try). Please report any further verified \
mainboards on the [[Mailinglist|mailing list]].\n";
#endif

static const char * const chip_th = "{| border=\"0\" style=\"font-size: smaller\" \
valign=\"top\"\n|- bgcolor=\"#6699dd\"\n! align=\"left\" | Vendor\n\
! align=\"left\" | Device\n! align=\"left\" | Size / KB\n\
! align=\"left\" | Type\n! align=\"left\" colspan=\"4\" | Status\n\n\
|- bgcolor=\"#6699ff\"\n| colspan=\"4\" | &nbsp;\n\
| Probe\n| Read\n| Erase\n| Write\n\n";

static const char * const programmer_section = "\
\n== Supported programmers ==\n\nThis is a list \
of supported PCI devices flashrom can use as programmer:\n\n{| border=\"0\" \
valign=\"top\"\n| valign=\"top\"|\n\n{| border=\"0\" style=\"font-size: \
smaller\" valign=\"top\"\n|- bgcolor=\"#6699dd\"\n! align=\"left\" | Vendor\n\
! align=\"left\" | Device\n! align=\"left\" | PCI IDs\n\
! align=\"left\" | Status\n\n";

#if CONFIG_INTERNAL == 1
static const char * const laptop_intro = "\n== Supported laptops/notebooks ==\n\n\
In general, flashing laptops is more difficult because laptops\n\n\
* often use the flash chip for stuff besides the BIOS,\n\
* often have special protection stuff which has to be handled by flashrom,\n\
* often use flash translation circuits which need drivers in flashrom.\n\n\
<div style=\"margin-top:0.5em; padding:0.5em 0.5em 0.5em 0.5em; \
background-color:#ff6666; align:right; border:1px solid #000000;\">\n\
'''IMPORTANT:''' At this point we recommend to '''not''' use flashrom on \
untested laptops unless you have a means to recover from a flashing that goes \
wrong (a working backup flash chip and/or good soldering skills).\n</div>\n";

static void print_supported_chipsets_wiki(int cols)
{
	int i, j, enablescount = 0, color = 1;
	const struct penable *e;

	for (e = chipset_enables; e->vendor_name != NULL; e++)
		enablescount++;

	printf("\n== Supported chipsets ==\n\nTotal amount of supported "
	       "chipsets: '''%d'''\n\n{| border=\"0\" valign=\"top\"\n| "
	       "valign=\"top\"|\n\n%s", enablescount, chipset_th);

	e = chipset_enables;
	for (i = 0, j = 0; e[i].vendor_name != NULL; i++, j++) {
		/* Alternate colors if the vendor changes. */
		if (i > 0 && strcmp(e[i].vendor_name, e[i - 1].vendor_name))
			color = !color;

		printf("|- bgcolor=\"#%s\"\n| %s || %s "
		       "|| %04x:%04x || %s\n", (color) ? "eeeeee" : "dddddd",
		       e[i].vendor_name, e[i].device_name,
		       e[i].vendor_id, e[i].device_id,
		       (e[i].status == OK) ? "{{OK}}" : "{{?3}}");

		/* Split table in 'cols' columns. */
		if (j >= (enablescount / cols + 1)) {
			printf("\n|}\n\n| valign=\"top\"|\n\n%s", chipset_th);
			j = 0;
		}
	}

	printf("\n|}\n\n|}\n");
}

static void wiki_helper(const char *devicetype, int cols,
			const struct board_info boards[])
{
	int i, j, k = 0, boardcount_good = 0, boardcount_bad = 0, color = 1;
	int num_notes = 0;
	char *notes = calloc(1, 1);
	char tmp[900 + 1];
	const struct board_pciid_enable *b = board_pciid_enables;

	for (i = 0; boards[i].vendor != NULL; i++) {
		if (boards[i].working)
			boardcount_good++;
		else
			boardcount_bad++;
	}

	printf("\n\nTotal amount of supported %s: '''%d'''. "
	       "Not yet supported (i.e., known-bad): '''%d'''.\n\n"
	       "{| border=\"0\" valign=\"top\"\n| valign=\"top\"|\n\n%s",
	       devicetype, boardcount_good, boardcount_bad, board_th);

	for (i = 0, j = 0; boards[i].vendor != NULL; i++, j++) {

		/* Alternate colors if the vendor changes. */
		if (i > 0 && strcmp(boards[i].vendor, boards[i - 1].vendor))
			color = !color;

		k = 0;
		while ((b[k].vendor_name != NULL) &&
			(strcmp(b[k].vendor_name, boards[i].vendor) ||
			 strcmp(b[k].board_name, boards[i].name))) {
			k++;
		}

		printf("|- bgcolor=\"#%s\"\n| %s || %s%s %s%s || %s%s%s%s "
		       "|| {{%s}}", (color) ? "eeeeee" : "dddddd",
		       boards[i].vendor,
		       boards[i].url ? "[" : "",
		       boards[i].url ? boards[i].url : "",
		       boards[i].name,
		       boards[i].url ? "]" : "",
		       b[k].lb_vendor ? "-m " : "&mdash;",
		       b[k].lb_vendor ? b[k].lb_vendor : "",
		       b[k].lb_vendor ? ":" : "",
		       b[k].lb_vendor ? b[k].lb_part : "",
		       (boards[i].working) ? "OK" : "No");

		if (boards[i].note) {
			printf("<sup>%d</sup>\n", num_notes + 1);
			snprintf((char *)&tmp, 900, "<sup>%d</sup> %s<br />\n",
				 1 + num_notes++, boards[i].note);
			notes = strcat_realloc(notes, (char *)&tmp);
		} else {
			printf("\n");
		}

		/* Split table in 'cols' columns. */
		if (j >= ((boardcount_good + boardcount_bad) / cols + 1)) {
			printf("\n|}\n\n| valign=\"top\"|\n\n%s", board_th);
			j = 0;
		}
	}

	printf("\n|}\n\n|}\n");

	if (num_notes > 0)
		printf("\n<small>\n%s</small>\n", notes);
	free(notes);
}

static void print_supported_boards_wiki(void)
{
	printf("%s", board_intro);
	wiki_helper("boards", 2, boards_known);

	printf("%s", laptop_intro);
	wiki_helper("laptops", 1, laptops_known);
}
#endif

static void print_supported_chips_wiki(int cols)
{
	int i = 0, c = 1, chipcount = 0;
	struct flashchip *f, *old = NULL;
	uint32_t t;

	for (f = flashchips; f->name != NULL; f++)
		chipcount++;

	printf("\n== Supported chips ==\n\nTotal amount of supported "
	       "chips: '''%d'''\n\n{| border=\"0\" valign=\"top\"\n"
		"| valign=\"top\"|\n\n%s", chipcount, chip_th);

	for (f = flashchips; f->name != NULL; f++, i++) {
		/* Don't print "unknown XXXX SPI chip" entries. */
		if (!strncmp(f->name, "unknown", 7))
			continue;

		/* Alternate colors if the vendor changes. */
		if (old != NULL && strcmp(old->vendor, f->vendor))
			c = !c;

		t = f->tested;
		printf("|- bgcolor=\"#%s\"\n| %s || %s || %d "
		       "|| %s || {{%s}} || {{%s}} || {{%s}} || {{%s}}\n",
		       (c == 1) ? "eeeeee" : "dddddd", f->vendor, f->name,
		       f->total_size, flashbuses_to_text(f->bustype),
		       (t & TEST_OK_PROBE) ? "OK" :
		       (t & TEST_BAD_PROBE) ? "No" : "?3",
		       (t & TEST_OK_READ) ? "OK" :
		       (t & TEST_BAD_READ) ? "No" : "?3",
		       (t & TEST_OK_ERASE) ? "OK" :
		       (t & TEST_BAD_ERASE) ? "No" : "?3",
		       (t & TEST_OK_WRITE) ? "OK" :
		       (t & TEST_BAD_WRITE) ? "No" : "?3");

		/* Split table into 'cols' columns. */
		if (i >= (chipcount / cols + 1)) {
			printf("\n|}\n\n| valign=\"top\"|\n\n%s", chip_th);
			i = 0;
		}

		old = f;
	}

	printf("\n|}\n\n|}\n");
}

static void print_supported_pcidevs_wiki(const struct pcidev_status *devs)
{
	int i = 0;
	static int c = 0;

	/* Alternate colors if the vendor changes. */
	c = !c;

	for (i = 0; devs[i].vendor_name != NULL; i++) {
		printf("|- bgcolor=\"#%s\"\n| %s || %s || "
		       "%04x:%04x || {{%s}}\n", (c) ? "eeeeee" : "dddddd",
		       devs[i].vendor_name, devs[i].device_name,
		       devs[i].vendor_id, devs[i].device_id,
		       (devs[i].status == NT) ? "?3" : "OK");
	}
}

void print_supported_wiki(void)
{
	time_t t = time(NULL);

	printf(wiki_header, ctime(&t), flashrom_version);
	print_supported_chips_wiki(2);
#if CONFIG_INTERNAL == 1
	print_supported_chipsets_wiki(3);
	print_supported_boards_wiki();
#endif
	printf("%s", programmer_section);
#if CONFIG_NIC3COM == 1
	print_supported_pcidevs_wiki(nics_3com);
#endif
#if CONFIG_NICREALTEK == 1
	print_supported_pcidevs_wiki(nics_realtek);
	print_supported_pcidevs_wiki(nics_realteksmc1211);
#endif
#if CONFIG_NICNATSEMI == 1
	print_supported_pcidevs_wiki(nics_natsemi);
#endif
#if CONFIG_GFXNVIDIA == 1
	print_supported_pcidevs_wiki(gfx_nvidia);
#endif
#if CONFIG_DRKAISER == 1
	print_supported_pcidevs_wiki(drkaiser_pcidev);
#endif
#if CONFIG_SATASII == 1
	print_supported_pcidevs_wiki(satas_sii);
#endif
#if CONFIG_ATAHPT == 1
	print_supported_pcidevs_wiki(ata_hpt);
#endif
#if CONFIG_NICINTEL_SPI == 1
	print_supported_pcidevs_wiki(nics_intel_spi);
#endif
#if CONFIG_OGP_SPI == 1
	print_supported_pcidevs_wiki(ogp_spi);
#endif
	printf("\n|}\n");
}

