#!/usr/bin/perl

$REQ_DEFINITION = "\\reqd";
$REQ_COPYSOURCE = "\\copyreqs";
$REQ_COPYTEST = "\\copyreqt";

open IN, "<OpenSEK/doc/OpenSEK.req" or die $!;
open OUT, ">out/req/OpenSEK_Req.doc" or die $!;

while ($line = <IN>)
{
	chomp $line;
	my $copy_flag = 1;

	if(index($line, $REQ_DEFINITION)>-1)
	{
		my $req = substr($line, index($line, $REQ_DEFINITION)+length($REQ_DEFINITION)+1);
		my @req = split(/ /,$req);
		$req = @req[0];
		print "Processing Requirement: " . $req . "\n";

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
		print OUT " * \\b Source \\b Tracing \\b Information:\n";
		$copy_flag = 0;
	}
	if(index($line, $REQ_COPYTEST)>-1)
	{
		print OUT " * \\b Test \\b Tracing \\b Information:\n";
		$copy_flag = 0;
	}

	if ($copy_flag == 1)
	{
		print OUT $line . "\n";
	}
}

close IN;
close OUT;
