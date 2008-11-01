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

$REQ_DEFINITION = "\\reqd";
$REQ_CODE = "\\req";
$REQ_TEST = "\\reqt";
$REQ_COPYSOURCE = "\\copyreqs";
$REQ_COPYTEST = "\\copyreqt";

sub getAllCHFiles
{
	my $indent = @_[0];
	opendir(MD, "./");
	my @ret;

	foreach my $file (sort readdir MD)
	{
		unless($file =~ m/^\./)
		{		
			if (-d $file)
			{
				chdir $file;
				push(@ret,getAllCHFiles("$indent/$file"));
				chdir "../";
			}
			elsif ( (index($file,".c") == length($file)-2)||
					  (index($file,".h") == length($file)-2))
			{
				push(@ret,substr("$indent/$file",1));
			}
		}
	}

	closedir(MD);
	return @ret
}

sub getReq
{
	my @rets;
	my @rett;

	foreach $file (@_)
	{
		#print "Opening: $file\n";
		open IN, "<$file" or die $!;
		my $linen = 0;
		while(my $line = <IN>)
		{
			$linen++;
			chomp $line;
			if (index($line,$REQ_CODE . " ")>-1)
			{
				my $coln = index($line,$REQ_CODE);
				my $req = substr($line, index($line, $REQ_CODE)+length($REQ_CODE)+1);
				my @req = split(/ /,$req);
				#print "Code File: $file - Line: $linen - Col: $coln - Req: @req[0]\n";
				my @el = ($file, @req[0], $linen, $coln);
				push(@rets,\@el);
			}

			if (index($line,$REQ_TEST . " ")>-1)
			{
				my $coln = index($line,$REQ_TEST);
				my $req = substr($line, index($line, $REQ_TEST)+length($REQ_TEST)+1);
				my @req = split(/ /,$req);
				#print "Test File: $file - Line: $linen - Col: $coln - Req: @req[0]\n";
				my @el = ($file, @req[0], $linen, $coln);
				push(@rett,\@el);
			}
		}
		close IN;
	}

	return (\@rets, \@rett);
}

sub getRelatedReq
{
	my $reqs = @_[0];
	my $sreq = @_[1];
	my @reqs = @$reqs;
	my @ret;

	#print "gerRelatedReq: $sreq - @_[1]\n";
	foreach my $req (@reqs)
	{
		my @req = @$req;
		if ( (index(@req[1], $sreq . "-")>-1) ||
			  ( @req[1] eq $sreq ) )
		{
			#print "Found: @req[1] - @req[0] - @req[2] - @req[3]\n";
			push(@ret,\@req);
		}
	}

	return @ret
}

sub info
{
	print "INFO: " . @_[0] . "\n";
}

# PROGRAM START

print "OpenSEK Requiremnet Tracing Tool - Copyright 2008, Mariano Cerdeiro - http://www.openosek.com.ar\n\n";
info("------ LICENSE START ------");
info("OpenSEK Generator is part of OpenOSEK.");
info("");
info("OpenSEK is free software: you can redistribute it and/or modify");
info("it under the terms of the GNU General Public License as published by");
info("the Free Software Foundation, either version 3 of the License, or");
info("(at your option) any later version.");
info("");
info("OpenSEK is distributed in the hope that it will be useful,");
info("but WITHOUT ANY WARRANTY; without even the implied warranty of");
info("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the");
info("GNU General Public License for more details.");
info("You should have received a copy of the GNU General Public License");
info("along with OpenSEK. If not, see <http://www.gnu.org/licenses/>.");
info("------- LICENSE END -------");


@chfiles = getAllCHFiles("");
info("Total of parsed header and source files.: " . scalar(@chfiles) );
($reqs, $reqt) = getReq(@chfiles);

@reqs = @$reqs;
@reqt = @$reqt;

info("Total of implemented requirements.......: " . scalar(@reqs));
info("Total of tested requirements............: " . scalar(@reqt));

open IN, "<OpenSEK/doc/OpenSEK.req" or die $!;
open OUT, ">out/gen/doc/OpenSEK_Req.doc" or die $!;

my $req;
my $reqcount=0;

while ($line = <IN>)
{
	chomp $line;
	my $copy_flag = 1;

	if(index($line, $REQ_DEFINITION . " ")>-1)
	{
		$reqcount++;
		$req = substr($line, index($line, $REQ_DEFINITION)+length($REQ_DEFINITION)+1);
		my @req = split(/ /,$req);
		$req = @req[0];
		#print "Processing Requirement: " . $req . "\n";

		print OUT " * \\b ";
		foreach $el (@req)
		{
			print OUT $el . " ";
		}
		print OUT "\n";

		$copy_flag = 0;
	}
	if(index($line, $REQ_COPYSOURCE)>-1)
	{
		print OUT " * - \\b Implemented:\n";
		#print "Searching for req.: $req\n";
		my @reqsrcs = getRelatedReq(\@reqs,$req);
		foreach $reqsrc (@reqsrcs)
		{
			@reqsrc = @$reqsrc;
			print OUT " *  - \\b @reqsrc[1] - @reqsrc[0] : @reqsrc[2] : @reqsrc[3]\n";
		}
		$copy_flag = 0;
	}
	if(index($line, $REQ_COPYTEST)>-1)
	{
		print OUT " * - \\b Tested:\n";
		my @reqtsts = getRelatedReq(\@reqt,$req);
		foreach $reqtst (@reqtsts)
      {
         @reqtst = @$reqtst;
         print OUT " *  - \\b @reqtst[1] - @reqtst[0] : @reqtst[2] : @reqtst[3]\n";
      }
      $copy_flag = 0;
		$copy_flag = 0;
	}

	if ($copy_flag == 1)
	{
		print OUT $line . "\n";
	}
}
info("Total of defined requirements...........: " . $reqcount);

close IN;
close OUT;
