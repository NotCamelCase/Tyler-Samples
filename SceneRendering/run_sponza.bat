@echo off

echo "RUNNING..."

call bin\Release\SceneRendering.exe -obj_name assets\sponza.obj -run_benchmark -num_frames 200 > sponza_log.txt

echo "DONE!"

pause