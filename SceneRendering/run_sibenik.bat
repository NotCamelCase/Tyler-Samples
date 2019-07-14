@echo off

echo "RUNNING..."

call bin\Release\SceneRendering.exe -obj_name assets\sibenik.obj -run_benchmark -num_frames 200 > sibenik_log.txt

echo "DONE!"

pause