README

Please run the package in Microsoft Visual Studio 2017, and follow the procedures below to link libCurl library to Visual Studio.

1. Go to Properties of Project->Configuration->All Configuration

Configuration Properties->General->Use of MFC->Use MFC in a Static Library

2.Configuration Properties->Linker->Input-> Normaliz.lib;Ws2_32.lib;Wldap32.lib;Crypt32.lib;advapi32.lib

The program should compile correctly if there are no linking issues.


Reference:
http://develop.itarimusic.com/how-to-add-libcurl-to-Visual-Studio-2017/