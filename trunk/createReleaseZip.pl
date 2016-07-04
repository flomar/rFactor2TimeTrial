# createReleaseZip.pl

#!/usr/bin/perl

#
# This file is part of the rFactor2TimeTrial project.
#
# https://github.com/flomar/rFactor2TimeTrial
#
# This script assumes both sub projects, QTimeTrial and rF2TimeTrial, have
# been built successfully before being invoked. Depending on your local
# environment, a few tweaks might be necessary for the script to run
# properly.
#
# Any questions? Drop me an email at florian(at)marchal(dot)de.
#
# flomar, July 2016
#

use POSIX;
use File::Copy;
use File::Find;

sleep(1);

# create a name for the release (depends on the current time only)
my $releaseName = "rFactor2TimeTrial" . "-" . strftime('%Y%m%d%H%M%S',localtime);

# assemble path to the release folder
my $releaseFolder = "../releases/$releaseName";

# create the release folder structure
mkdir("$releaseFolder");
mkdir("$releaseFolder/QTimeTrial");
mkdir("$releaseFolder/QTimeTrial/win32");
mkdir("$releaseFolder/rF2TimeTrial");
mkdir("$releaseFolder/rF2TimeTrial/win32");
mkdir("$releaseFolder/rF2TimeTrial/win64");

# copy LICENSE and INSTALL files
copy("../LICENSE", "$releaseFolder");
copy("INSTALL", "$releaseFolder");

# copy QTimeTrial files
my @dllFiles = ();
find(\&findDllFile, "QTimeTrial/bin");
sub findDllFile {
    my $dllFile = $_;
    if($dllFile =~ m/.+\.dll/) {
        push(@dllFiles, $dllFile);
    }
}
foreach my $dllFile (@dllFiles) {
    copy("QTimeTrial/bin/$dllFile", "$releaseFolder/QTimeTrial/win32");
}
copy("QTimeTrial/build/release/release/QTimeTrial.exe", "$releaseFolder/QTimeTrial/win32");
copy("QTimeTrial/QTimeTrial.sqlite", "$releaseFolder/QTimeTrial");
copy("QTimeTrial/QTimeTrial.bat", "$releaseFolder/QTimeTrial");

# copy rF2TimeTrial files
copy("rF2TimeTrial/Win32/Release/rF2TimeTrial.dll", "$releaseFolder/rF2TimeTrial/win32");
copy("rF2TimeTrial/x64/Release/rF2TimeTrial.dll", "$releaseFolder/rF2TimeTrial/win64");
copy("rF2TimeTrial/rF2TimeTrial.cfg", "$releaseFolder/rF2TimeTrial");

# compress the whole thing into a convenient ZIP archive
system("/c/Program\\ Files/7-Zip/7z.exe a ../releases/$releaseName.zip $releaseFolder");

# remove the temporary release folder
system("rm -rf $releaseFolder");
