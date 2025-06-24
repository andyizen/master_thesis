@echo off
REM Define tool paths
set "VPPATH=C:\Xilinx\Vitis\2023.2\bin\v++.bat"
set "VITISRUN=C:\Xilinx\Vitis\2023.2\bin\vitis-run.bat"

set "BIQUAD=biquad_DFI"
REM Synthesise 
call "%VPPATH%" -c ^
  --mode hls ^
  --config .\hls_components\%BIQUAD%\cfg_%BIQUAD%.cfg ^
  --work_dir .\hls_components\%BIQUAD%
REM Package 
call "%VITISRUN%" ^
  --mode hls --package ^
  --config .\hls_components\%BIQUAD%_float\cfg_%BIQUAD%_float.cfg ^
  --work_dir .\hls_components\%BIQUAD%\package

set "BIQUAD=biquad_DFII"
REM Synthesise 
call "%VPPATH%" -c ^
  --mode hls ^
  --config .\hls_components\%BIQUAD%\cfg_%BIQUAD%.cfg ^
  --work_dir .\hls_components\%BIQUAD%
REM Package 
call "%VITISRUN%" ^
  --mode hls --package ^
  --config .\hls_components\%BIQUAD%_float\cfg_%BIQUAD%_float.cfg ^
  --work_dir .\hls_components\%BIQUAD%\package

set "BIQUAD=biquad_DFI_float"
REM Synthesise 
call "%VPPATH%" -c ^
  --mode hls ^
  --config .\hls_components\%BIQUAD%\cfg_%BIQUAD%.cfg ^
  --work_dir .\hls_components\%BIQUAD%
REM Package 
call "%VITISRUN%" ^
  --mode hls --package ^
  --config .\hls_components\%BIQUAD%_float\cfg_%BIQUAD%_float.cfg ^
  --work_dir .\hls_components\%BIQUAD%\package

set "BIQUAD=biquad_DFII_float"
REM Synthesise 
call "%VPPATH%" -c ^
  --mode hls ^
  --config .\hls_components\%BIQUAD%\cfg_%BIQUAD%.cfg ^
  --work_dir .\hls_components\%BIQUAD%
REM Package 
call "%VITISRUN%" ^
  --mode hls --package ^
  --config .\hls_components\%BIQUAD%_float\cfg_%BIQUAD%_float.cfg ^
  --work_dir .\hls_components\%BIQUAD%\package


REM Create Vivado projects
call "C:\Xilinx\Vivado\2023.2\bin\vivado.bat" -mode batch -source ./vivado/build.tcl -notrace -tclargs biquad_DFII 
call "C:\Xilinx\Vivado\2023.2\bin\vivado.bat" -mode batch -source ./vivado/build.tcl -notrace -tclargs biquad_DFI 
call "C:\Xilinx\Vivado\2023.2\bin\vivado.bat" -mode batch -source ./vivado/build.tcl -notrace -tclargs biquad_DFII_float 
call "C:\Xilinx\Vivado\2023.2\bin\vivado.bat" -mode batch -source ./vivado/build.tcl -notrace -tclargs biquad_DFI_float 