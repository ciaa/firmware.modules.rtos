#!/usr/bin/perl

# Copyright 2008, Mariano Cerdeiro
#
# This file is part of OpenSEK.
#
# OpenSEK is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# OpenSEK is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with OpenSEK. If not, see <http://www.gnu.org/licenses/>.

use Cwd;
use Switch;


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

foreach my $mod (@modules)
{
	print "Mod: $mod\n";
	my @symmod = getSymbols($mod,\@symbols);
	@symmod = orderSymbols("alp", \@symmod);
	foreach my $sym (@symmod)
	{
		my @el = @$sym;

		print "YES: $el[0], $el[1], $el[2], $el[3], $el[4], $el[5], $el[6]\n";
	}
}

close IN;
close OUT;
