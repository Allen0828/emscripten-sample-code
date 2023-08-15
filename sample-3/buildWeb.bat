set dir= build\bin
echo %dir%
if exist %dir% {
    del /s /q %dir%
    rd /s /q %dir%
}
IF NOT EXIST build (
    mkdir build
)
IF NOT EXIST build\bin (
    mkdir build\bin
)

Xcopy "src\" "build\bin\" /s /i /d

cd build
call emsdk_env.bat
call emcmake cmake .. -DCMAKE_BUILD_TYPE=DEBUG
call emmake make -j8

move "sample_video.js" "bin\" 
move "sample_video.wasm" "bin\" 

:FAILURE
@if NOT ["%errorlevel%"]==["0"] (
	pause
    @popd
    exit /b %errorlevel%
)