#!/usr/bin/perl

# Copyright 2008, 2009, Mariano Cerdeiro
#
# This file is part of OpenSEK.
#
# OpenSEK is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#             
# Linking OpenSEK statically or dynamically with other modules is making a
# combined work based on OpenSEK. Thus, the terms and conditions of the GNU
# General Public License cover the whole combination.
#
# In addition, as a special exception, the copyright holders of OpenSEK give
# you permission to combine OpenSEK program with free software programs or
# libraries that are released under the GNU LGPL and with independent modules
# that communicate with OpenSEK solely through the OpenSEK defined interface. 
# You may copy and distribute such a system following the terms of the GNU GPL
# for OpenSEK and the licenses of the other code concerned, provided that you
# include the source code of that other code when and as the GNU GPL requires
# distribution of source code.
#
# Note that people who make modified versions of OpenSEK are not obligated to
# grant this special exception for their modified versions; it is their choice
# whether to do so. The GNU General Public License gives permission to release
# a modified version without this exception; this exception also makes it
# possible to release a modified version which carries forward this exception.
# 
# OpenSEK is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with OpenSEK. If not, see <http://www.gnu.org/licenses/>.
#

use Cwd;
use Switch;

sub info
{
   print "INFO: " . @_[0] . "\n";
}

sub wf_start
{
	print OUT "/********************************************************\n";
	print OUT "* DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*\n";
	print OUT "********************************************************/\n\n";
	print OUT "/* Copyright 2008, Mariano Cerdeiro\n";
	print OUT " *\n";
	print OUT " * This file is part of OpenSEK.\n";
	print OUT " *\n";
	print OUT " * OpenSEK is free software: you can redistribute it and/or modify\n";
	print OUT " * it under the terms of the GNU General Public License as published by\n";
	print OUT " * the Free Software Foundation, either version 3 of the License, or\n";
	print OUT " * (at your option) any later version.\n";
	print OUT " * Linking OpenSEK statically or dynamically with other modules is making a\n";
	print OUT " * combined work based on OpenSEK. Thus, the terms and conditions of the GNU\n";
	print OUT " * General Public License cover the whole combination.\n";
	print OUT " *\n";
	print OUT " * In addition, as a special exception, the copyright holders of OpenSEK give\n";
	print OUT " * you permission to combine OpenSEK program with free software programs or\n";
	print OUT " * libraries that are released under the GNU LGPL and with independent modules\n";
	print OUT " * that communicate with OpenSEK solely through the OpenSEK defined interface.\n";
	print OUT " * You may copy and distribute such a system following the terms of the GNU GPL\n";
	print OUT " * for OpenSEK and the licenses of the other code concerned, provided that you\n";
	print OUT " * include the source code of that other code when and as the GNU GPL requires\n";
	print OUT " * distribution of source code.\n";
	print OUT " *\n";
	print OUT " * Note that people who make modified versions of OpenSEK are not obligated to\n";
	print OUT " * grant this special exception for their modified versions; it is their choice\n";
	print OUT " * whether to do so. The GNU General Public License gives permission to release\n";
	print OUT " * a modified version without this exception; this exception also makes it\n";
	print OUT " * possible to release a modified version which carries forward this exception.\n";
	print OUT " *\n";
	print OUT " * OpenSEK is distributed in the hope that it will be useful,\n";
	print OUT " * but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
	print OUT " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n";
	print OUT " * GNU General Public License for more details.\n";
	print OUT " *\n";
	print OUT " * You should have received a copy of the GNU General Public License\n";
	print OUT " * along with OpenSEK. If not, see <http://www.gnu.org/licenses/>.\n";
	print OUT " *\n";
	print OUT " */\n\n";
	print OUT "/** \\page OpenSEK_Size Project ROM/RAM Memory Consumption\n";
	wf();
}

sub wf_end
{
	print OUT " */\n";
}

sub wf
{
	print OUT " * @_[0]\n";
}

sub getSections
{
	my @sections;

	foreach $sym (@_)
	{
		my @el = @$sym;
		my $found = 0;

		foreach $section (@sections)
		{
			if($section eq @el[3])
			{
				$found = 1;
			}
		}
		if ($found == 0)
      {
			push (@sections, $el[3]);
			#print "$el[0], $el[1], $el[2], $el[3], $el[4], $el[5], $el[6]\n";
		}
	}

	return @sections;
}

sub createSectionSize
{
	my @ret;

	foreach my $sec (@_)
	{
		my @el;
		@el[0] = $sec;
		@el[1] = 0;

		push(@ret,\@el);
	}

	return @ret;
}

sub addSectionSize
{
	my @ret;
	my $secsize = @_[0];
	my $sec = @_[1];
	my $size = @_[2];

	my @secsize = @$secsize;

	foreach $secs (@secsize)
	{
		my @el = @$secs;
		if ($sec eq @el[0])
		{
			@el[1] += $size;
		}
		push (@ret, \@el);
	}

	return @ret;
}

sub orderSymbols
{
	sub alp_com
	{
		my @a1 = @$a;
		my @a2 = @$b;

		@b1[5] cmp @a1[5];
	}

	my @ret;
	my $ord = @_[0];
	my $symbols = @_[1];
	my @symbols = @$symbols;
	switch ($ord)
	{
		case "alp"
		{
			@ret = sort alp_com @symbols;
		}
	}

	return @ret;
}

sub getSymbols
{
	my @ret;
	my $mod = @_[0];
	my $symbols = @_[1];
	my @symbols = @$symbols;

	#print "sym\n";
	foreach my $sym (@symbols)
	{
		@el = @$sym;
		#print "actul: @el[4]\n";
		if ($mod eq @el[4])
		{
			push(@ret,$sym);
			#print "yes: $el[0], $el[1], $el[2], $el[3], $el[4], $el[5], $el[6]\n";
		}
	}

	return @ret;
}

sub getModules
{
	my @modules;
	foreach $els (@_)
	{
		my @el = @$els;
		my $found=0;
		foreach $mod (@modules)
		{
			if($mod eq @el[4])
			{
				$found = 1;
			}
		}
		if ($found == 0)
		{
			push (@modules, $el[4]);
			#print "$el[0], $el[1], $el[2], $el[3], $el[4], $el[5], $el[6]\n";
		}
	}

	return @modules;
}

# PROGRAM START

print "OpenSEK Size Tool - Copyright 2008, Mariano Cerdeiro - http://www.openosek.com.ar\n\n";
info("------ LICENSE START ------");
info("OpenSEK Generator is part of OpenOSEK.");
info("");
info("OpenSEK is free software: you can redistribute it and/or modify");
info("it under the terms of the GNU General Public License as published by");
info("the Free Software Foundation, either version 3 of the License, or");
info("(at your option) any later version.");
info("");
info("Linking OpenSEK statically or dynamically with other modules is making a");
info("combined work based on OpenSEK. Thus, the terms and conditions of the GNU");
info("General Public License cover the whole combination.");
info("");
info("In addition, as a special exception, the copyright holders of OpenSEK give");
info("you permission to combine OpenSEK program with free software programs or");
info("libraries that are released under the GNU LGPL and with independent modules");
info("that communicate with OpenSEK solely through the OpenSEK defined interface.");
info("You may copy and distribute such a system following the terms of the GNU GPL");
info("for OpenSEK and the licenses of the other code concerned, provided that you");
info("include the source code of that other code when and as the GNU GPL requires");
info("distribution of source code.");
info("");
info("Note that people who make modified versions of OpenSEK are not obligated to");
info("grant this special exception for their modified versions; it is their choice");
info("whether to do so. The GNU General Public License gives permission to release");
info("a modified version without this exception; this exception also makes it");
info("possible to release a modified version which carries forward this exception.");
info("");
info("OpenSEK is distributed in the hope that it will be useful,");
info("but WITHOUT ANY WARRANTY; without even the implied warranty of");
info("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the");
info("GNU General Public License for more details.");
info("You should have received a copy of the GNU General Public License");
info("along with OpenSEK. If not, see <http://www.gnu.org/licenses/>.");
info("------- LICENSE END -------");

open OUT, ">out/gen/doc/SizeInformation.doc" or die $!;
open IN, "<out/gen/doc/nm.out" or die $!;

my $linen = 0;
my $pwd = getcwd;
my @symbols;

while ($line = <IN>)
{
	$linen++;
	if ($linen > 6)
	{
		chomp($line);
		my @el = split(/\|/,$line);
		my $sym = @el[0]; $sym =~ s/^\s+//; $sym =~ s/\s+$//; # remove leading and trailing spaces
		my $add = @el[1]; $add =~ s/^\s+//; $add =~ s/\s+$//; # remove leading and trailing spaces
		my $size = @el[4]; $size =~ s/^\s+//; $size =~ s/\s+$//; # remove leading and trailing spaces
		my $type = substr(@el[6],0,index(@el[6],"\t"));
		my $file = substr(@el[6],index(@el[6],"\t")+1,index(@el[6],":")-index(@el[6],"\t")-1);
		my $file = substr($file,length($pwd)+1);
		my $module = substr($file,0,index($file,"/"));
		my $file = substr($file,index($file,"/")+1);
		my $line = substr(@el[6],index(@el[6],":")+1);

		@el = ($sym, $add, $size, $type, $module, $file, $line);

		push(@symbols, \@el);
	}
}

my @modules = getModules(@symbols);

wf_start();

foreach my $mod (@modules)
{
	wf(" - \\ref OpenSEK_Size_$mod");
	wf("  - \\ref OpenSEK_Size_$mod" . "_Summary");
}
wf(" - \\ref OpenSEK_Size_Total");
wf();

my @sizetotal = createSectionSize(getSections(@symbols));

foreach my $mod (@modules)
{
	#print "Mod: $mod\n";
	my @symmod = getSymbols($mod,\@symbols);
	@symmod = orderSymbols("alp", \@symmod);

	my @sizemodule = createSectionSize(getSections(@symmod));

	wf("\\section OpenSEK_Size_$mod Size Section $mod");
	wf();
	
	foreach my $sym (@symmod)
	{
		my @el = @$sym;
		@el[2] = hex(@el[2]);

		# do not print symbols with size 0
		if (@el[2] > 0)
		{
			wf("\\b @el[0] in \\b @el[3] use \\b @el[2] bytes (file: @el[5]:@el[6])<br>");
		}

		@sizemodule = addSectionSize(\@sizemodule, @el[3], @el[2]);

	}

	wf();
	wf("\\subsection OpenSEK_Size_$mod" . "_Summary Summary for this module");
	wf();

	my $secn = 0;
	foreach my $sm (@sizemodule)
	{
		my @sm = @$sm;

		wf("Total Size \\b @sm[0]: \\b @sm[1] bytes<br>");

		@sizetotal = addSectionSize(\@sizetotal, @sm[0], @sm[1]);
	}

	wf();
}

wf("\\section OpenSEK_Size_Total Total RAM/ROM Consumption");
wf();

foreach my $st (@sizetotal)
{
	my @st = @$st;
	wf("Total section \\b @st[0] use \\b @st[1] bytes<br>");
}

wf_end();

close IN;
close OUT;
