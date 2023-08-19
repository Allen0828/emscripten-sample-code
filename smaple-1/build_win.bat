mkdir build
cd build
call emsdk_env.bat
call emcmake cmake .. -DCMAKE_BUILD_TYPE=DEBUG
call emmake make -j8

:FAILURE
@if NOT ["%errorlevel%"]==["0"] (
	pause
    @popd
    exit /b %errorlevel%
)