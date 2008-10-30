#!/usr/bin/perl

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
	@ret;

	foreach $file (@_)
	{
		#print "Opening: $file\n";
		open IN, "<$file" or die $!;
		my $linen = 0;
		while(my $line = <IN>)
		{
			$linen++;
			chomp $line;
			if (index($line,$REQ_CODE)>-1)
			{
				my $coln = index($line,$REQ_CODE);
				my $req = substr($line, index($line, $REQ_CODE)+length($REQ_CODE)+1);
				my @req = split(/ /,$req);
				#print "File: $file - Line: $linen - Col: $coln - Req: @req[0]\n";
				my @el = ($file, @req[0], $linen, $coln);
				push(@ret,\@el);
			}
		}
		close IN;
	}

	return @ret;
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

@chfiles = getAllCHFiles("");
@reqs = getReq(@chfiles);

open IN, "<OpenSEK/doc/OpenSEK.req" or die $!;
open OUT, ">out/req/OpenSEK_Req.doc" or die $!;


my $req;

while ($line = <IN>)
{
	chomp $line;
	my $copy_flag = 1;

	if(index($line, $REQ_DEFINITION)>-1)
	{
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
		print OUT " * - \\b Source \\b Tracing \\b Information:\n";
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
		print OUT " * - \\b Test \\b Tracing \\b Information:\n";
		$copy_flag = 0;
	}

	if ($copy_flag == 1)
	{
		print OUT $line . "\n";
	}
}

close IN;
close OUT;
