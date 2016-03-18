echo on
rmdir /q /s build
mkdir build
cd build

set QTDIR='F:\Qt\5.5\msvc2013'
set XSDDIR='F:\CodeSynthesis XSD 4.0\bin'
set PATH=%QTDIR%\bin;%XSDDIR%;%PATH%
set CMAKE_PREFIX_PATH=%QTDIR%;%CMAKE_PREFIX_PATH%

cmake -G "Visual Studio 14 2015" -DQt5_DIR='F:\Qt\5.5\msvc2013\lib\cmake\Qt5' -Dbmc_USE_PYTHON=OFF -DBOOST_ROOT=f:\boost_1_60_0\boost_1_60_0  DBOOST_INCLUDEDIR=f:\boost_1_60_0\boost_1_60_0  -DBOOST_LIBRARYDIR=f:\boost_1_60_0\boost_1_60_0\stage\lib -DBoost_PROGRAM_OPTIONS_LIBRARY_DEBUG=f:\boost_1_60_0\boost_1_60_0\stage\lib\libboost_program_options-vc140-mt-gd-1_59.lib -DBoost_PROGRAM_OPTIONS_LIBRARY_RELEASE=f:\boost_1_60_0\boost_1_60_0\stage\lib\libboost_program_options-vc140-mt-1_59.lib -DXercesC_INCLUDE_DIR="f:\CodeSynthesis XSD 4.0\include" -DXercesC_LIBRARY_DEBUG="f:\CodeSynthesis XSD 4.0\lib\vc-12.0\xerces-c_3D.lib" -DXercesC_LIBRARY_RELEASE="f:\CodeSynthesis XSD 4.0\lib\vc-12.0\xerces-c_3.lib" -DXSDCXX_EXECUTABLE="f:\CodeSynthesis XSD 4.0\bin\xsd.exe" -DXSDCXX_INCLUDE_DIR="f:\CodeSynthesis XSD 4.0\include" ..
