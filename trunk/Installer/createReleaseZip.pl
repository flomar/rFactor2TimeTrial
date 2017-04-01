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
# properly, especially with regards to external commands such as "rm"
# or "7z".
#

use POSIX;
use File::Copy;
use File::Find;

my $WINDEPLOYQT = $ENV{'WINDEPLOYQT'} or undef;
if(not defined $WINDEPLOYQT) {
    print("Please make sure there is an environment variable 'WINDEPLOYQT' pointing to the 'windeployqt.exe' delivered with your Qt installation.\n");
    exit(0);
}

sleep(1);

# create a name for the release (depends on the current time only)
my $releaseName = "rFactor2TimeTrial" . "-" . strftime('%Y%m%d%H%M%S',localtime);

# assemble path to the release folder
my $releaseFolder = "../../releases/$releaseName";

# create the release folder structure
mkdir("$releaseFolder");
mkdir("$releaseFolder/QTimeTrial");
mkdir("$releaseFolder/QTimeTrial/win32");
mkdir("$releaseFolder/rF2TimeTrial");
mkdir("$releaseFolder/rF2TimeTrial/win32");
mkdir("$releaseFolder/rF2TimeTrial/win64");

# copy LICENSE, and INSTALLand README files
copy("../../LICENSE", "$releaseFolder");
copy("INSTALL", "$releaseFolder");
copy("README", "$releaseFolder");

# copy QTimeTrial files
copy("../QTimeTrial/build/release/release/QTimeTrial.exe", "$releaseFolder/QTimeTrial/win32");
system("$WINDEPLOYQT --qmldir ../QTimeTrial/resources/qml $releaseFolder/QTimeTrial/win32/QTimeTrial.exe");
copy("../QTimeTrial/QTimeTrial.sqlite", "$releaseFolder/QTimeTrial");
copy("QTimeTrial/QTimeTrial.bat", "$releaseFolder/QTimeTrial");

# copy rF2TimeTrial files
copy("../rF2TimeTrial/Win32/Release/rF2TimeTrial.dll", "$releaseFolder/rF2TimeTrial/win32");
copy("../rF2TimeTrial/x64/Release/rF2TimeTrial.dll", "$releaseFolder/rF2TimeTrial/win64");
copy("rF2TimeTrial/rF2TimeTrial.cfg", "$releaseFolder/rF2TimeTrial");

# compress the whole thing into a convenient ZIP archive
system("/c/Program\\ Files/7-Zip/7z.exe a ../../releases/$releaseName.zip $releaseFolder");

# remove the temporary release folder
system("rm -rf $releaseFolder");
