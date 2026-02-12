import sys, os
from shutil import copyfile, rmtree
from distutils.dir_util import copy_tree
print(sys.argv)

out_dir = os.getcwd()

os.makedirs(out_dir, exist_ok=True)
os.chdir(out_dir)
os.makedirs("tmp/Library/MobileSubstrate/DynamicLibraries/", exist_ok=True)
os.makedirs("tmp/Applications/", exist_ok=True)
os.makedirs("tmp/DEBIAN/", exist_ok=True)

open("tmp/DEBIAN/control", "w").write("""Name: Noahh Launcher
Architecture: iphoneos-arm
Depends: com.cokepokes.libnotifications (>= 0.2-2)
Description: Modding suite for Geometry Dash (test package!!)
Maintainer: camila314
Package: com.camila314.noahh-test
Priority: optional
Section: Tweaks
Version: 0.1.0
""")

copy_tree("Noahh Helper.app/", "tmp/Applications/Noahh Helper.app/")
copyfile("/Users/jakrillis/tmp/noahh/loader/loader_ios/build/Noahh.dylib", "bin/ios/Noahh.dylib")
os.system("ldid -S NoahhLauncher.dylib")
os.system("ldid -S bin/ios/Noahh.dylib")
copyfile("NoahhLauncher.dylib", "tmp/Library/MobileSubstrate/DynamicLibraries/NoahhLauncher.dylib")
copyfile("bin/ios/Noahh.dylib", "tmp/Library/MobileSubstrate/DynamicLibraries/Noahh.dylib")

open("tmp/Library/MobileSubstrate/DynamicLibraries/NoahhLauncher.plist", "w").write("""{ Filter = { Bundles = ( "com.robtop.geometryjump" ); }; }""")
os.system("dpkg-deb --build tmp noahhloader-test-arm64.deb")
rmtree("tmp")